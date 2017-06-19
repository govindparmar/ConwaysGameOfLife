#include "CGOL.h"

ATOM WINAPI RegisterWCEX(
	_In_ HINSTANCE hInstance
)
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
	
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wcex.hIcon = LoadIconW(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIconW(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WindowProc;
	wcex.lpszClassName = g_wszClassName;
	
	return RegisterClassExW(&wcex);
}
