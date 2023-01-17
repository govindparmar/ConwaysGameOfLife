#include "CGOL.h"

HDC g_hDC;
BOOL g_fGameRunning = FALSE;

VOID CALLBACK TimerProc(
	_In_ HWND hWnd, 
	_In_ UINT uMsg, 
	_In_ UINT_PTR idEvent, 
	_In_ DWORD dwTime
)
{
	INT x, y, nAdj = 0;
	if (g_fGameRunning)
	{
		if (g_pMenuItems != NULL)
		{
			CONST HANDLE hHeap = GetProcessHeap();
			HeapFree(hHeap, 0, g_pMenuItems);
			g_pMenuItems = NULL;
		}


		SelectObject(g_hDC, g_hbrBackground);
		Rectangle(g_hDC, 0, 0, GRIDSIZE * CELLSIZE, GRIDSIZE * CELLSIZE);
		SelectObject(g_hDC, g_hbrCell);
		for (y = 0; y < GRIDSIZE; y++)
		{
			for (x = 0; x < GRIDSIZE; x++)
			{
				if (g_aUpdate[y][x] == 1)
				{
					Rectangle(g_hDC, x * CELLSIZE, y * CELLSIZE, x * CELLSIZE + CELLSIZE, y * CELLSIZE + CELLSIZE);
				}
			}
		}

		for (y = 0; y < GRIDSIZE; y++)
		{
			for (x = 0; x < GRIDSIZE; x++)
			{
				g_aGrid[y][x] = g_aUpdate[y][x];
			}
		}


		for (y = 1; y < GRIDSIZE - 1; y++)
		{
			for (x = 1; x < GRIDSIZE - 1; x++)
			{
				if (g_aGrid[y][x - 1] == 1)
					nAdj++;
				if (g_aGrid[y - 1][x - 1] == 1)
					nAdj++;
				if (g_aGrid[y - 1][x] == 1)
					nAdj++;
				if (g_aGrid[y - 1][x + 1] == 1)
					nAdj++;
				if (g_aGrid[y][x + 1] == 1)
					nAdj++;
				if (g_aGrid[y + 1][x + 1] == 1)
					nAdj++;
				if (g_aGrid[y + 1][x] == 1)
					nAdj++;
				if (g_aGrid[y + 1][x - 1] == 1)
					nAdj++;
				if (g_aGrid[y][x] == 0 && nAdj == 3)
					g_aUpdate[y][x] = 1;
				if (g_aGrid[y][x] == 1)
				{
					if (nAdj > 3 || nAdj < 2)
						g_aUpdate[y][x] = 0;
				}
				nAdj = 0;
			}
		}
		nAdj = 0;

		// EDGES
		// LEFT VERTICAL EDGE
		for (y = 1; y < GRIDSIZE - 1; y++)
		{
			nAdj = 0;
			if (g_aGrid[y + 1][0] == 1)
				nAdj++;
			if (g_aGrid[y][1] == 1)
				nAdj++;
			if (g_aGrid[y - 1][0] == 1)
				nAdj++;
			if (g_aGrid[y + 1][1] == 1)
				nAdj++;
			if (g_aGrid[y - 1][1] == 1)
				nAdj++;
			if (nAdj > 3 || nAdj < 2)
				g_aUpdate[y][0] = 0;
			if (g_aGrid[y][0] == 0 && nAdj == 3)
				g_aUpdate[y][0] = 1;

		}
		// RIGHT VERTICAL EDGE
		for (y = 1; y < GRIDSIZE - 1; y++)
		{
			nAdj = 0;
			if (g_aGrid[y + 1][GRIDSIZE - 1] == 1)
				nAdj++;
			if (g_aGrid[y][GRIDSIZE - 2] == 1)
				nAdj++;
			if (g_aGrid[y - 1][GRIDSIZE - 1] == 1)
				nAdj++;
			if (g_aGrid[y + 1][GRIDSIZE - 2] == 1)
				nAdj++;
			if (g_aGrid[y - 1][GRIDSIZE - 2] == 1)
				nAdj++;
			if (nAdj > 3 || nAdj < 2)
				g_aUpdate[y][GRIDSIZE - 1] = 0;
			if (g_aGrid[y][GRIDSIZE - 1] == 0 && nAdj == 3)
				g_aUpdate[y][GRIDSIZE - 1] = 1;

		}

		// TOP HORIZONTAL EDGE
		for (x = 1; x < GRIDSIZE - 1; x++)
		{
			nAdj = 0;
			if (g_aGrid[0][x + 1] == 1)
				nAdj++;
			if (g_aGrid[1][x] == 1)
				nAdj++;
			if (g_aGrid[0][x - 1] == 1)
				nAdj++;
			if (g_aGrid[1][x + 1] == 1)
				nAdj++;
			if (g_aGrid[1][x - 1] == 1)
				nAdj++;
			if (nAdj > 3 || nAdj < 2)
				g_aUpdate[0][x] = 0;
			if (g_aGrid[0][x] == 0 && nAdj == 3)
				g_aUpdate[0][x] = 1;
		}

		// BOTTOM HORIZONTAL EDGE
		for (x = 1; x < GRIDSIZE - 1; x++)
		{
			nAdj = 0;
			if (g_aGrid[GRIDSIZE - 1][x + 1] == 1)
				nAdj++;
			if (g_aGrid[GRIDSIZE - 2][x] == 1)
				nAdj++;
			if (g_aGrid[GRIDSIZE - 1][x - 1] == 1)
				nAdj++;
			if (g_aGrid[GRIDSIZE - 2][x + 1] == 1)
				nAdj++;
			if (g_aGrid[GRIDSIZE - 2][x - 1] == 1)
				nAdj++;
			if (nAdj > 3 || nAdj < 2)
				g_aUpdate[GRIDSIZE - 1][x] = 0;
			if (g_aGrid[GRIDSIZE - 1][x] == 0 && nAdj == 3)
				g_aUpdate[GRIDSIZE - 1][x] = 1;
		}

		nAdj = 0;

		// CORNERS
		if (g_aGrid[0][0] == 1)
		{
			if (g_aGrid[0][1] == 1)
				nAdj++;
			if (g_aGrid[1][0] == 1)
				nAdj++;
			if (g_aGrid[1][1] == 1)
				nAdj++;
			if (nAdj < 2)
				g_aUpdate[0][0] = 0;
		}
		nAdj = 0;

		if (g_aGrid[0][GRIDSIZE - 1] == 1)
		{
			if (g_aGrid[1][GRIDSIZE - 1] == 1)
				nAdj++;
			if (g_aGrid[0][GRIDSIZE - 2] == 1)
				nAdj++;
			if (g_aGrid[1][GRIDSIZE - 2] == 1)
				nAdj++;
			if (nAdj < 2)
				g_aUpdate[0][GRIDSIZE - 1] = 0;
		}
		nAdj = 0;

		if (g_aGrid[GRIDSIZE - 1][0] == 1)
		{
			if (g_aGrid[GRIDSIZE - 1][1] == 1)
				nAdj++;
			if (g_aGrid[GRIDSIZE - 2][0] == 1)
				nAdj++;
			if (g_aGrid[GRIDSIZE - 2][1] == 1)
				nAdj++;
			if (nAdj < 2)
				g_aUpdate[GRIDSIZE - 1][0] = 0;
		}
		nAdj = 0;

		if (g_aGrid[GRIDSIZE - 1][GRIDSIZE - 1] == 1)
		{
			if (g_aUpdate[GRIDSIZE - 1][GRIDSIZE - 2] == 1)
				nAdj++;
			if (g_aUpdate[GRIDSIZE - 2][GRIDSIZE - 1] == 1)
				nAdj++;
			if (g_aUpdate[GRIDSIZE - 2][GRIDSIZE - 2] == 1)
				nAdj++;
			if (nAdj < 2)
				g_aUpdate[GRIDSIZE - 1][GRIDSIZE - 1] = 0;
		}

		nAdj = 0;
	}
}
