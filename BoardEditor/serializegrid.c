#include "BE.h"

DWORD WINAPI SerializeGrid(_In_reads_or_z_(MAX_PATH) WCHAR *wszFileName)
{
	CONST HANDLE hHeap = GetProcessHeap();
	HANDLE hFile = INVALID_HANDLE_VALUE;
	SIZE_T i, i2, i3 = 0;
	WORD coordCount = 0;
	BOARDFILEHEADER bfh;
	BOARDCOORDS *pCoords = NULL;
	DWORD dwError = ULONG_MAX, dwWritten = 0;

	bfh.wSig = MAKEWORD(0x07, 0x02);
	bfh.wVersion = 0x0001;
	bfh.bGridSize = GRIDSIZE;

	for (i = 0; i < GRIDSIZE; i++)
	{
		for (i2 = 0; i2 < GRIDSIZE; i2++)
		{
			if (g_nCells[i][i2])
			{
				coordCount++;
			}
		}
	}

	bfh.wNumberCells = coordCount;

	if (coordCount > 0)
	{
		pCoords = (BOARDCOORDS *) HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(BOARDCOORDS) * coordCount);
		if (NULL == pCoords)
		{
			dwError = ERROR_OUTOFMEMORY;
			goto cleanup;
		}

		for (i = 0; i < GRIDSIZE; i++)
		{
			for (i2 = 0; i2 < GRIDSIZE; i2++)
			{
				if (g_nCells[i][i2])
				{
					pCoords[i3].bX = (uint8_t)i;
					pCoords[i3].bY = (uint8_t)i2;
					i3++;
				}
			}
		}
	}

	hFile = CreateFileW(wszFileName, GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		dwError = GetLastError();
		//if(ERROR_FILE_NOT_FOUND)
		goto cleanup;
	}

	WriteFile(hFile, &bfh, sizeof(BOARDFILEHEADER), &dwWritten, NULL);
	for (i = 0; i < coordCount; i++)
	{
		WriteFile(hFile, &pCoords[i], sizeof(BOARDCOORDS), &dwWritten, NULL);
	}

	dwError = ERROR_SUCCESS;

cleanup:
	if (pCoords != NULL)
	{
		HeapFree(hHeap, 0, pCoords);
		pCoords = NULL;
	}
	if (hFile != INVALID_HANDLE_VALUE)
	{
		FlushFileBuffers(hFile);
		CloseHandle(hFile);
	}

	return dwError;
}
