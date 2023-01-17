#include "BE.h"

VOID WINAPI DrawGrid(_In_ HWND hWnd)
{
	HDC hDC = GetDC(hWnd);
	INT i, i2;
	RECT r;
	HBRUSH hBr;
	GetClientRect(hWnd, &r);
	for (i = CELLSIZE; i <= (GRIDSIZE * CELLSIZE) - CELLSIZE; i += CELLSIZE)
	{
		MoveToEx(hDC, i, 0, NULL);
		LineTo(hDC, i, r.bottom);
		MoveToEx(hDC, 0, i, NULL);
		LineTo(hDC, r.right, i);
	}
	for (i = 0; i < GRIDSIZE; i++)
	{
		for (i2 = 0; i2 < GRIDSIZE; i2++)
		{
			if (g_nCells[i][i2])
			{
				hBr = CreateSolidBrush(RGB(0, 0x6D, 0xA5));
				SelectObject(hDC, hBr);
				Rectangle(hDC, i * CELLSIZE, i2 * CELLSIZE, i * CELLSIZE + CELLSIZE, i2 * CELLSIZE + CELLSIZE);
				hBr = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
				SelectObject(hDC, hBr);
			}
			else
			{
				Rectangle(hDC, i * CELLSIZE, i2 * CELLSIZE, i * CELLSIZE + CELLSIZE, i2 * CELLSIZE + CELLSIZE);
			}
		}
	}
}