#include "CGOL.h"

ATOM WINAPI RegisterWCEX(
	_In_ HINSTANCE hInstance
)
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
	
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wcex.hIcon = 
	wcex.hIconSm = LoadIconW(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WindowProc;
	wcex.lpszClassName = g_wszClassName;
	
	return RegisterClassExW(&wcex);
}
