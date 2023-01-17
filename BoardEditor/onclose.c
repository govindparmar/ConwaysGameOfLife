#include "BE.h"

VOID WINAPI OnClose(_In_ HWND hWnd)
{
	DestroyWindow(hWnd);
}
