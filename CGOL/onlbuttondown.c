#include "CGOL.h"

VOID WINAPI OnLButtonDown(_In_ HWND hWnd, _In_ BOOL fDoubleClick, _In_ INT x, _In_ INT y, _In_ UINT keyFlags)
{
	if (!g_fGameRunning && g_pMenuItems != NULL)
	{
		if (IsWithinRect(g_pMenuItems[0], x, y)) // New Game Menu Item
		{
			InitializeGameGrid(hWnd);
			g_fGameRunning = TRUE;
		}
		else if (IsWithinRect(g_pMenuItems[1], x, y))
		{
			if (MessageBoxW(hWnd, L"Really quit?", APP_TITLE, MB_YESNOQUESTION) == IDYES)
			{
				DestroyWindow(hWnd);
			}
		}
	}
}