#include "CGOL.h"

BOOL WINAPI LoadGridFile(_In_reads_or_z_(MAX_PATH) WCHAR *wszFileName, _In_ HWND hWnd) // 2nd param for GetClientRect call
{
	CONST HANDLE hHeap = GetProcessHeap();
	DWORD dwError = ULONG_MAX, dwRead;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	BOARDFILEHEADER bfh;
	BOARDCOORDS *pCoords = NULL;
	SIZE_T cbAlloc;
	LARGE_INTEGER liSize;
	WORD i;
	RECT rect;

	hFile = CreateFileW(wszFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		dwError = GetLastError();
		goto cleanup;
	}
	
	GetFileSizeEx(hFile, &liSize);
	if (liSize.HighPart || (liSize.LowPart & 0xFFF00000))
	{
		dwError = ERROR_FILE_TOO_LARGE;
		goto cleanup;
	}

	if (liSize.LowPart < sizeof(BOARDFILEHEADER)) // FIle too small to hold a file header of this type is obviosly not valid
	{
		dwError = ERROR_INVALID_DATA; 
		goto cleanup;
	}

	if (!ReadFile(hFile, &bfh, sizeof(BOARDFILEHEADER), &dwRead, NULL))
	{
		dwError = GetLastError();
		goto cleanup;
	}

	if (bfh.wSig != MAKEWORD(0x07, 0x02))
	{
		dwError = ERROR_INVALID_DATA;
		goto cleanup;
	}

	if (bfh.wVersion != 0x0001 || bfh.bGridSize != GRIDSIZE)
	{
		dwError = ERROR_INVALID_DATA;
		goto cleanup;
	}

	cbAlloc = sizeof(BOARDCOORDS) * bfh.wNumberCells;
	if (liSize.LowPart - sizeof(BOARDFILEHEADER) < cbAlloc) // this file is smaller than the number of coordinates it claims to contain
	{
		dwError = ERROR_INVALID_DATA;
		goto cleanup;
	}

	pCoords = (BOARDCOORDS *) HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbAlloc);
	if (NULL == pCoords)
	{
		dwError = ERROR_OUTOFMEMORY;
		goto cleanup;
	}

	if (!ReadFile(hFile, pCoords, cbAlloc, &dwRead, NULL))
	{
		dwError = GetLastError();
		goto cleanup;
	}

	ZeroMemory(g_aUpdate, sizeof(INT) * GRIDSIZE * GRIDSIZE);
	for (i = 0; i < bfh.wNumberCells; i++)
	{
		g_aUpdate[pCoords[i].bX][pCoords[i].bY] = 1;
	}

	GetClientRect(hWnd, &rect);
	RedrawWindow(hWnd, &rect, NULL, RDW_INVALIDATE);
	SetTimer(hWnd, IDT_TIMER1, 100, TimerProc);
	dwError = ERROR_SUCCESS;

cleanup:
	if (pCoords != NULL)
	{
		HeapFree(hHeap, 0, pCoords);
		pCoords = NULL;
	}
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}

	SetLastError(dwError);
	return ERROR_SUCCESS == dwError;
}