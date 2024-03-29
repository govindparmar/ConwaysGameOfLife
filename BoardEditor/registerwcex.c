#include "BE.h"

CONST WCHAR g_wszClassName[] = L"CGOL_BoardEditor_GovindParmar";

_Success_(return)
_Check_return_

ATOM WINAPI RegisterWCEX(_In_ HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEXW));

	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wcex.hIcon = 
	wcex.hIconSm = LoadIconW(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WindowProc;
	wcex.lpszClassName = g_wszClassName;
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDM_MAINWINDOW);

	return RegisterClassExW(&wcex);
}
