#include "BE.h"

VOID WINAPI OnPaint(_In_ HWND hWnd)
{
	PAINTSTRUCT ps;
	
	BeginPaint(hWnd, &ps);
	DrawGrid(hWnd);
	EndPaint(hWnd, &ps);

	return;
}
