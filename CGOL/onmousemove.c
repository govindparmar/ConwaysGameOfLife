#include "CGOL.h"

VOID WINAPI OnMouseMove(_In_ HWND hWnd, _In_ INT x, _In_ INT y, _In_ UINT keyFlags)
{
	if (!g_fGameRunning) // Implementation detail for "game is dislpaying the menu screen"
	{
		if (g_pMenuItems != NULL)
		{
			HBRUSH hbrSMIText = CreateSolidBrush(RGB(0xFF, 0x02, 0x0A));
			HBRUSH hbrSMIBack = CreateSolidBrush(RGB(0x09, 0x09, 0x09));
		//	SIZE_T i;
			// 2: Number of CURRENT menu items
			BOOL fWeGood = FALSE;
			if (IsWithinRect(g_pMenuItems[0], x, y))
			{
				SetBkColor(g_hDC, RGB(0x09, 0x09, 0x09));
				SetTextColor(g_hDC, RGB(0xFF, 0x02, 0x0A));
				TextOutW(g_hDC, 10, 10, L"G = New Game", 12);
				SetBkColor(g_hDC, 0);
				SetTextColor(g_hDC, RGB(0, 255, 0));
				TextOutW(g_hDC, 10, 40, L"Q = Quit", 8);
				fWeGood = FALSE;
			}
			else if (IsWithinRect(g_pMenuItems[1], x, y))
			{
				SetBkColor(g_hDC, RGB(0x09, 0x09, 0x09));
				SetTextColor(g_hDC, RGB(0xFF, 0x02, 0x0A));
				TextOutW(g_hDC, 10, 40, L"Q = Quit", 8);
				SetBkColor(g_hDC, 0);
				SetTextColor(g_hDC, RGB(0, 255, 0));
				TextOutW(g_hDC, 10, 10, L"G = New Game", 12);
				fWeGood = FALSE;
			}
			else
			{
				if (!fWeGood)
				{
					SetBkColor(g_hDC, 0);
					SetTextColor(g_hDC, RGB(0, 255, 0));
					TextOutW(g_hDC, 10, 10, L"G = New Game", 12);
					TextOutW(g_hDC, 10, 40, L"Q = Quit", 8);
					fWeGood = TRUE;
				}
			}
			
		}
	}
}