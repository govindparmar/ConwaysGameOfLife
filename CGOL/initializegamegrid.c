#include "CGOL.h"

VOID WINAPI InitializeGameGrid (_In_ HWND hWnd)
{
	INT x, y;

	ZeroMemory(g_aGrid, sizeof(INT) * GRIDSIZE * GRIDSIZE);
	ZeroMemory(g_aUpdate, sizeof(INT) * GRIDSIZE * GRIDSIZE);
	for (y = 0; y < GRIDSIZE; y++)
	{
		for (x = 0; x < GRIDSIZE; x++)
		{
			g_aGrid[y][x] = !!(rand() % 2);
		}
	}
	for (y = 0; y < GRIDSIZE; y++)
	{
		for (x = 0; x < GRIDSIZE; x++)
		{
			g_aUpdate[y][x] = g_aGrid[y][x];
		}
	}
	SetTimer(hWnd, IDT_TIMER1, TIMER_TICK, TimerProc);
}