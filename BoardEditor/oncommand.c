#include "BE.h"

WCHAR g_wszFileName[] = { L'\0' };

VOID WINAPI OnCommand(
	_In_ HWND hWnd,
	_In_ INT nID,
	_In_ HWND hwSource,
	_In_ UINT uNotify
)
{
	if (ID_FILE_NEW == nID)
	{
		if (g_fTouched)
		{
			if (MessageBoxW(NULL, L"Start a new file, discarding current unsaved changes?", APP_TITLE, MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				RECT rect;
				
				ZeroMemory(&g_nCells, sizeof(INT) * GRIDSIZE * GRIDSIZE);
				GetClientRect(hWnd, &rect);
				RedrawWindow(hWnd, &rect, NULL, RDW_INVALIDATE);
				g_fTouched = FALSE;
			}
		}
		else
		{
			// New when untouched SAVED file is open?
		}
	}



	return;
}
