#include "CGOL.h"

VOID WINAPI OnChar(_In_ HWND hWnd, _In_ WCHAR wc, _In_ INT nRepeat)
{
	switch (wc)
	{
	case L'G': // new game
	case L'g':
		if (g_fGameRunning)
		{
			INT nResponse = MessageBoxW(hWnd, L"Do you want to end the current game and start a new one?", L"New Game", MB_YESNO | MB_ICONQUESTION);
			if (IDYES == nResponse)
			{
				// Start new game
				InitializeGameGrid(hWnd);
				g_fGameRunning = TRUE;
			}

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
		if (MessageBoxW(hWnd, L"Really quit?", L"Conway\'s Game Of Life", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hWnd);
		}
		break;
	}
}