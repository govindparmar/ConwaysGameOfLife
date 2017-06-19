#include "CGOL.h"

HBRUSH g_hbrCell;
HBRUSH g_hbrBackground;
INT g_aGrid[GRIDSIZE][GRIDSIZE];
INT g_aUpdate[GRIDSIZE][GRIDSIZE];

BOOL WINAPI OnCreate(
	_In_ HWND hWnd, 
	_In_ LPCREATESTRUCTW lpCreateStruct
)
{
	int x, y;
	g_hbrCell = CreateSolidBrush(RGB(0, 255, 0));
	g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	srand((UINT)time(NULL));
	ZeroMemory(g_aGrid, sizeof(INT) * GRIDSIZE * GRIDSIZE);
	ZeroMemory(g_aUpdate, sizeof(INT) * GRIDSIZE * GRIDSIZE);
	for (y = 0; y < GRIDSIZE; y++)
	{
		for (x = 0; x < GRIDSIZE; x++)
		{
			int random = rand() % 2;
			if (random == 0)
				g_aGrid[y][x] = 1;
			else
				g_aGrid[y][x] = 0;
		}
	}
	for (y = 0; y < GRIDSIZE; y++)
		for (x = 0; x < GRIDSIZE; x++)
			g_aUpdate[y][x] = g_aGrid[y][x];

	g_hDC = GetDC(hWnd);
	SetTimer(hWnd, IDT_TIMER1, 100, TimerProc);
	return TRUE;
}
