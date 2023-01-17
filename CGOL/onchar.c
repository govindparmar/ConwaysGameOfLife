#include "CGOL.h"

VOID WINAPI OnChar(_In_ HWND hWnd, _In_ WCHAR wc, _In_ INT nRepeat)
{
	CONST HANDLE hHeap = GetProcessHeap();

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
		if (g_fGameRunning)
		{
			g_fGameRunning = FALSE;
			if (MessageBoxW(hWnd, L"Really quit current game?", APP_TITLE, MB_YESNOQUESTION) == IDYES)
			{

				g_fGameRunning = FALSE;
				KillTimer(hWnd, IDT_TIMER1);
				MenuScreen();
			}
			else
			{
				g_fGameRunning = TRUE;
			}
		}
		else
		{
			if (MessageBoxW(hWnd, L"Really exit program?", APP_TITLE, MB_OK | MB_ICONQUESTION) == IDYES)
			{
				g_fGameRunning = FALSE;
				KillTimer(hWnd, IDT_TIMER1);
				DestroyWindow(hWnd);
			}
		}
		break;
	}
}