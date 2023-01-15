#include "CGOL.h"

VOID WINAPI OnChar(_In_ HWND hWnd, _In_ WCHAR wc, _In_ INT nRepeat)
{
	switch (wc)
	{
	case L'G': // new game
	case L'g':
		if (g_fGameRunning)
		{
			g_fGameRunning = FALSE;
			if (IDYES == MessageBoxW(hWnd, L"Do you want to end the current game and start a new one?", APP_TITLE, MB_YESNOQUESTION))
			{
				// Start new game
				InitializeGameGrid(hWnd);
				g_fGameRunning = TRUE;
			}
			g_fGameRunning = TRUE;
		}
		else
		{
			// No game running - Just start new game
			InitializeGameGrid(hWnd);
			g_fGameRunning = TRUE;
		}
		break;
	case L'Q': // quit
	case L'q':
		g_fGameRunning = FALSE;
		if (MessageBoxW(hWnd, L"Really quit?", APP_TITLE, MB_YESNOQUESTION) == IDYES)
		{
			DestroyWindow(hWnd);
		}
		g_fGameRunning = TRUE;
		break;
	}
}