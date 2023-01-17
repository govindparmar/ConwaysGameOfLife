#include "BE.h"

BOOL g_fTouched = FALSE;

VOID WINAPI OnLButtonDown(_In_ HWND hWnd, _In_ BOOL fDoubleClick, _In_ INT x, _In_ INT y, _In_ UINT keyFlags)
{
	INT xCell, yCell;
	//WCHAR wszMsg[200];
	BOOL fRedraw = FALSE;

	xCell = (x / CELLSIZE);
	yCell = (y / CELLSIZE);

	/*StringCchPrintfW(wszMsg, 200, L"(%I32d, %I32d)", xCell, yCell);
	if (xCell > 30 && yCell > 30)

	{
		MessageBoxW(NULL, wszMsg, APP_TITLE, MB_OK | MB_ICONASTERISK);
	}*/

	if (xCell < GRIDSIZE && yCell < GRIDSIZE) // Should always be true if window is drawn correctly
	{
		if (g_nCells[xCell][yCell])
		{
			g_nCells[xCell][yCell] = 0;
		}
		else
		{
			g_nCells[xCell][yCell] = 1;
			g_fTouched = TRUE;
			
		}
		fRedraw = TRUE;
	}
	if (fRedraw)
	{
		RECT rect;
		
		rect.top = (yCell * CELLSIZE) - 1;
		rect.left = (xCell * CELLSIZE) - 1;
		rect.bottom = (yCell * CELLSIZE) + CELLSIZE + 1;
		rect.right = (xCell * CELLSIZE) + CELLSIZE + 1;
		RedrawWindow(hWnd, &rect, NULL, RDW_INVALIDATE);
	}
}
