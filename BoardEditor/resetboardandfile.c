#include "BE.h"

_Post_satisfies_(!g_fTouched && L'\0' == g_wszFileName[0])

VOID WINAPI ResetBoardAndFile(_In_ HWND hWnd)
{
	RECT rect;
	
	ZeroMemory(g_nCells, sizeof(INT) * GRIDSIZE * GRIDSIZE);
	GetClientRect(hWnd, &rect);
	RedrawWindow(hWnd, &rect, NULL, RDW_INVALIDATE);
	g_wszFileName[0] = L'\0';
	SetWindowTextW(hWnd, APP_TITLE);
	g_fTouched = FALSE;
}
