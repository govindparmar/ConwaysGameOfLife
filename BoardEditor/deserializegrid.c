#include "BE.h"

DWORD WINAPI DeserializeGrid(_In_ HWND hWnd, _In_reads_or_z_(MAX_PATH) WCHAR *wszFileName)
{
	CONST HANDLE hHeap = GetProcessHeap();
	HANDLE hFile = INVALID_HANDLE_VALUE;
	LARGE_INTEGER liSize;
	SIZE_T cbAlloc, cbRemaining;
	BOARDFILEHEADER bfh;
	BOARDCOORDS *pCoords = NULL;
	DWORD dwRead, dwError = ULONG_MAX;
	WORD i;
	RECT rect;

	hFile = CreateFileW(wszFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		dwError = GetLastError();
		goto cleanup;
	}

	GetFileSizeEx(hFile, &liSize);
	if (liSize.HighPart || (liSize.LowPart & 0xFFF00000)) // WAAAY too large to be a valid grid file
	{
		dwError = ERROR_INVALID_DATA;
		goto cleanup;
	}

	if (liSize.LowPart < sizeof(BOARDFILEHEADER)) // Too small to contain a file header - too small to be a valid file
	{
		dwError = ERROR_INVALID_DATA;
		goto cleanup;
	}

	if (!ReadFile(hFile, &bfh, sizeof(BOARDFILEHEADER), &dwRead, NULL))
	{
		dwError = GetLastError();
		goto cleanup;
	}

	if (MAKEWORD(0x07, 0x02) != bfh.wSig) // Does not start with file signature for grid files
	{
		dwError = ERROR_INVALID_DATA;
		goto cleanup;
	}

	if (bfh.bGridSize != GRIDSIZE) // File is for a different grid size than the current GRIDSIZE define
	{
		dwError = ERROR_INVALID_DATA;
		goto cleanup;
	}

	if (bfh.wVersion > 1) // File is for a later version than this version of the board viewer
	{
		dwError = ERROR_INVALID_DATA;
		goto cleanup;
	}

	cbRemaining = (liSize.LowPart - sizeof(BOARDFILEHEADER));
	if ((cbRemaining / sizeof(BOARDCOORDS)) < bfh.wNumberCells) // File does not have enough space to store the number of cells it claims it has in the header
	{
		dwError = ERROR_INVALID_DATA;
		goto cleanup;
	}

	cbAlloc = (bfh.wNumberCells * sizeof(BOARDCOORDS));
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

	ZeroMemory(g_nCells, sizeof(INT) * GRIDSIZE * GRIDSIZE);
	for (i = 0; i < bfh.wNumberCells; i++)
	{
		g_nCells[pCoords[i].bX][pCoords[i].bY] = 1;
	}
	GetClientRect(hWnd, &rect);
	RedrawWindow(hWnd, &rect, NULL, RDW_INVALIDATE);
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
	return dwError;
}
