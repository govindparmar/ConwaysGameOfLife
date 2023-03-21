#include "CGOL.h"

HBRUSH g_hbrCell;
HBRUSH g_hbrBackground;
INT g_aGrid[GRIDSIZE][GRIDSIZE];
INT g_aUpdate[GRIDSIZE][GRIDSIZE];
RECT g_clientRect;

BOOL WINAPI OnCreate(
	_In_ HWND hWnd, 
	_In_ LPCREATESTRUCTW lpCreateStruct
)
{
	INITCOMMONCONTROLSEX iccx;

	iccx.dwICC = ICC_STANDARD_CLASSES;
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	g_hbrCell = CreateSolidBrush(RGB(0, 255, 0));
	g_hbrBackground = CreateSolidBrush(0);

	srand((UINT)time(NULL));
	InitCommonControlsEx(&iccx);
	g_hDC = GetDC(hWnd);
	GetClientRect(hWnd, &g_clientRect);
	
	return TRUE;
}
