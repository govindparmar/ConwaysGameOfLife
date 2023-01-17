#include "BE.h"

INT g_nCells[GRIDSIZE][GRIDSIZE];

BOOL WINAPI OnCreate(_In_ HWND hWnd, _In_ LPCREATESTRUCTW lpCreateStruct)
{
	INITCOMMONCONTROLSEX iccx;

	iccx.dwICC = ICC_STANDARD_CLASSES;
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);

	InitCommonControlsEx(&iccx);

	ZeroMemory(g_nCells, sizeof(INT) * GRIDSIZE * GRIDSIZE);

	return TRUE;
}
