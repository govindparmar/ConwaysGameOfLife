#include "CGOL.h"

VOID WINAPI MenuScreen()
{
	if (NULL == g_hDC)
	{
		return;
	}

	SelectObject(g_hDC, g_hbrBackground);
	Rectangle(g_hDC, 0, 0, GRIDSIZE * CELLSIZE, GRIDSIZE * CELLSIZE);
	SelectObject(g_hDC, g_hbrCell);
	SetBkColor(g_hDC, 0);
	SetTextColor(g_hDC, RGB(0, 255, 0));
	//SetText
	TextOutW(g_hDC, 10, 10, L"G = New Game", 12);
	TextOutW(g_hDC, 10, 40, L"Q = Quit", 8);
}