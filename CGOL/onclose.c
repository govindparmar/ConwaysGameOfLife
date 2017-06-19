#include "CGOL.h"

VOID WINAPI OnClose(
	_In_ HWND hWnd
)
{
	KillTimer(hWnd, IDT_TIMER1);
	DestroyWindow(hWnd);
}
