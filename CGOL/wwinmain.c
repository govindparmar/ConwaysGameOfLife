#include "CGOL.h"

CONST WCHAR g_wszClassName[] = L"CGOL_GovindParmar";

INT APIENTRY wWinMain(
	_In_ HINSTANCE hInstance, 
	_In_ HINSTANCE hPrevInstance, 
	_In_z_ LPWSTR lpCmdLine, 
	_In_ INT nShowCmd
)
{
	HWND hWnd; 
	MSG Msg; 

	if (RegisterWCEX(hInstance)==(ATOM)0) 
	{
		MessageBoxW(NULL, L"Window registration failed", L"Error", MB_ICONSTOP | MB_OK);
		return 0;
	}

	hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, g_wszClassName, L"Conway\'s Game of Life", WS_VISIBLE | WS_SYSMENU, 100, 100, GRIDSIZE * 20, GRIDSIZE * 20, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL) 
	{
		MessageBoxW(NULL, L"Window creation failed", L"Error", MB_ICONSTOP | MB_OK);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	while (GetMessageW(&Msg, NULL, 0, 0) > 0) 
	{ 
		TranslateMessage(&Msg); 
		DispatchMessageW(&Msg); 
	}
	return Msg.wParam;
}
