#include "BE.h"

INT APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ INT nShowCmd)
{
	HWND hWnd;
	MSG Msg;
	NONCLIENTMETRICSW ncm;
	HFONT hfDefault;

	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICSW));
	ncm.cbSize = sizeof(NONCLIENTMETRICSW);
	SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICSW), &ncm, FALSE);
	hfDefault = CreateFontIndirectW(&ncm.lfMessageFont);

	if (RegisterWCEX(hInstance) == (ATOM)0)
	{
		MessageBoxW(NULL, L"Window registration failed", L"Error", MB_ICONSTOP | MB_OK);
		return 0;
	}

	hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, g_wszClassName, APP_TITLE, WS_VISIBLE | WS_SYSMENU, 100, 100, (GRIDSIZE * CELLSIZE) + CELLSIZE + 10, (GRIDSIZE * CELLSIZE) + CELLSIZE + 53, NULL, NULL, hInstance, NULL);
	if (hWnd == NULL)
	{
		MessageBoxW(NULL, L"Window creation failed", L"Error", MB_ICONSTOP | MB_OK);
		return 0;
	}
	
	ShowWindow(hWnd, nShowCmd);
	EnumChildWindows(hWnd, EnumChildProc, (LPARAM) &hfDefault);
	DrawGrid(hWnd);
	UpdateWindow(hWnd);

	while (GetMessageW(&Msg, NULL, 0, 0) > 0)
	{
		//if (!IsDialogMessageW(hWnd, &Msg))
		//{
			TranslateMessage(&Msg);
			DispatchMessageW(&Msg);
		//}
	}

	return (INT) Msg.wParam;
}
