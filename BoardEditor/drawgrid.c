#include "BE.h"

HBRUSH g_hbrFilled = NULL;
HBRUSH g_hbrEmpty = NULL;
HBRUSH g_hbrEmptyAlternate = NULL;

VOID WINAPI DrawGrid(_In_ HWND hWnd)
{
	HDC hDC = GetDC(hWnd);
	INT i, i2;
	RECT r;

	if (NULL == g_hbrFilled)
	{
		g_hbrFilled = CreateSolidBrush(RGB(0x00, 0x6D, 0xA5));
	}
	if (NULL == g_hbrEmpty)
	{
		g_hbrEmpty = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	}
	if (NULL == g_hbrEmptyAlternate)
	{
		g_hbrEmptyAlternate = CreateSolidBrush(RGB(0xDF, 0xDF, 0xDF));
	}

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
				SelectObject(hDC, g_hbrFilled);
				Rectangle(hDC, i * CELLSIZE, i2 * CELLSIZE, i * CELLSIZE + CELLSIZE, i2 * CELLSIZE + CELLSIZE);

			}
			else
			{
				SelectObject(hDC, ((i + i2) % 2) == 0 ? g_hbrEmpty : g_hbrEmptyAlternate);
				Rectangle(hDC, i * CELLSIZE, i2 * CELLSIZE, i * CELLSIZE + CELLSIZE, i2 * CELLSIZE + CELLSIZE);
			}
		}
	}
}
