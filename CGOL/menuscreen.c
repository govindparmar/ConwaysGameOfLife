#include "CGOL.h"

RECT *g_pMenuItems = NULL;

VOID WINAPI MenuScreen()
{
	CONST HANDLE hHeap = GetProcessHeap();
	RECT rMenuItem;

	if (NULL == g_hDC)
	{
		return;
	}

	ZeroMemory(&rMenuItem, sizeof(RECT));
	rMenuItem.right = 200;
	rMenuItem.bottom = 23;

	if (g_pMenuItems != NULL)
	{
		HeapFree(hHeap, 0, g_pMenuItems);
		g_pMenuItems = NULL;
	}

	g_pMenuItems = (RECT *) HeapAlloc(hHeap, HEAP_ZERO_MEMORY, 3 * sizeof(RECT)); // as in 3 menu items right now
	if (NULL == g_pMenuItems)
	{
		MessageBoxW(NULL, L"Out of memory", APP_TITLE, MB_OK | MB_ICONSTOP);
		ExitProcess(ERROR_OUTOFMEMORY);
	}

	SelectObject(g_hDC, g_hbrBackground);
	Rectangle(g_hDC, 0, 0, GRIDSIZE * CELLSIZE, GRIDSIZE * CELLSIZE);
	SelectObject(g_hDC, g_hbrCell);
	SetBkColor(g_hDC, 0);
	SetTextColor(g_hDC, RGB(0, 0xFF, 0));
	
	ExtTextOutW(g_hDC, 10, 10, ETO_CLIPPED , &rMenuItem, L"G = New Game", 12, NULL);
	CopyMemory(&g_pMenuItems[0], &rMenuItem, sizeof(RECT));
	rMenuItem.bottom += 30;
	ExtTextOutW(g_hDC, 10, 40, ETO_CLIPPED, &rMenuItem, L"L = Load Game Grid", 18, NULL);
	CopyMemory(&g_pMenuItems[1], &rMenuItem, sizeof(RECT));
	rMenuItem.bottom += 30;
	ExtTextOutW(g_hDC, 10, 70, ETO_CLIPPED , &rMenuItem, L"Q = Quit", 8, NULL);
	CopyMemory(&g_pMenuItems[2], &rMenuItem, sizeof(RECT));
	
}
