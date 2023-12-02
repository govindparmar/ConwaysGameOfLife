#include "CGOL.h"

VOID WINAPI OnMouseMove(_In_ HWND hWnd, _In_ INT x, _In_ INT y, _In_ UINT keyFlags)
{
	if (!g_fGameRunning) // Implementation detail for "game is dislpaying the menu screen"
	{
		if (g_pMenuItems != NULL)
		{
			COLORREF crText = RGB(0xFF, 0x02, 0x0A);
			COLORREF crInactiveText = RGB(0, 0xFF, 0);
			COLORREF crBkgnd = RGB(0x09, 0x09, 0x09);
			HBRUSH hbrSMIText = CreateSolidBrush(crText);
			HBRUSH hbrSMIBack = CreateSolidBrush(crBkgnd);
			//	SIZE_T i;
			// 2: Number of CURRENT menu items
			BOOL fDoneDrawingMenu = FALSE;

			if (IsWithinRect(g_pMenuItems[0], x, y))
			{
				SetBkColor(g_hDC, crBkgnd);
				SetTextColor(g_hDC, crText);
				TextOutW(g_hDC, 10, 10, L"G = New Game", 12);
				SetBkColor(g_hDC, 0);
				SetTextColor(g_hDC, crInactiveText);
				TextOutW(g_hDC, 10, 70, L"Q = Quit", 8);
				TextOutW(g_hDC, 10, 40, L"L = Load Game Grid", 18);
				fDoneDrawingMenu = FALSE;
			}
			else if (IsWithinRect(g_pMenuItems[1], x, y))
			{
				SetBkColor(g_hDC, crBkgnd);
				SetTextColor(g_hDC, crText);
				TextOutW(g_hDC, 10, 40, L"L = Load Game Grid", 18);
				SetBkColor(g_hDC, 0);
				SetTextColor(g_hDC, crInactiveText);
				TextOutW(g_hDC, 10, 10, L"G = New Game", 12);
				TextOutW(g_hDC, 10, 70, L"Q = Quit", 8);
				fDoneDrawingMenu = FALSE;
			}
			else if (IsWithinRect(g_pMenuItems[2], x, y))
			{
				SetBkColor(g_hDC, RGB(0x09, 0x09, 0x09));
				SetTextColor(g_hDC, RGB(0xFF, 0x02, 0x0A));
				TextOutW(g_hDC, 10, 70, L"Q = Quit", 8);
				SetBkColor(g_hDC, 0);
				SetTextColor(g_hDC, RGB(0, 255, 0));
				TextOutW(g_hDC, 10, 10, L"G = New Game", 12);
				TextOutW(g_hDC, 10, 40, L"L = Load Game Grid", 18);
				fDoneDrawingMenu = FALSE;
			}
			else
			{
				if (!fDoneDrawingMenu)
				{
					SetBkColor(g_hDC, 0);
					SetTextColor(g_hDC, RGB(0, 255, 0));
					TextOutW(g_hDC, 10, 10, L"G = New Game", 12);
					TextOutW(g_hDC, 10, 70, L"Q = Quit", 8);
					fDoneDrawingMenu = TRUE;
				}
			}
			
		}
	}
}
