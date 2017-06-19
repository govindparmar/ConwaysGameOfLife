#include "CGOL.h"

VOID WINAPI OnClose(
	_In_ HWND hWnd
)
{
	DestroyWindow(hWnd);
}
