#include "BE.h"

VOID WINAPI OnLButtonDown(_In_ HWND hWnd, _In_ BOOL fDoubleClick, _In_ INT x, _In_ INT y, _In_ UINT keyFlags)
{
	INT xCell, yCell;
	WCHAR wszMsg[200];
	HBRUSH hbrCell = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	BOOL fRedraw = FALSE;
	RECT rect;

	xCell = (x / CELLSIZE);
	yCell = (y / CELLSIZE);

	if (xCell < GRIDSIZE && yCell < GRIDSIZE) // Should always be true if window is drawn correctly
	{
		if (g_nCells[xCell][yCell])
		{
			g_nCells[xCell][yCell] = 0;
		}
		else
		{
			g_nCells[xCell][yCell] = 1;
		}
		fRedraw = TRUE;
	}
	if (fRedraw)
	{
		rect.top = (yCell * CELLSIZE) - 1;
		rect.left = (xCell * CELLSIZE) - 1;
		rect.bottom = (yCell * CELLSIZE) + CELLSIZE + 1;
		rect.right = (xCell * CELLSIZE) + CELLSIZE + 1;
		RedrawWindow(hWnd, &rect, NULL, RDW_INVALIDATE);
	}
}
