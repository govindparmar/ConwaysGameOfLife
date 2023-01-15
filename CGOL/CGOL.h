#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <stdlib.h>
#include <time.h>
#include <strsafe.h>
#include <sal.h>


#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#define IDT_TIMER1 1001
#define EXTERN extern
#define GRIDSIZE 40
#define CELLSIZE 10

EXTERN CONST WCHAR g_wszClassName[];
EXTERN INT g_aGrid[GRIDSIZE][GRIDSIZE];
EXTERN INT g_aUpdate[GRIDSIZE][GRIDSIZE];
EXTERN HDC g_hDC;
EXTERN HBRUSH g_hbrCell;
EXTERN HBRUSH g_hbrBackground;
EXTERN BOOL g_fGameRunning;

VOID WINAPI InitializeGameGrid(_In_ HWND hWnd);
VOID WINAPI MenuScreen();
VOID WINAPI OnChar(_In_ HWND hWnd, _In_ WCHAR wc, _In_ INT nRepeat);
VOID WINAPI OnClose(_In_ HWND hWnd);
VOID WINAPI OnDestroy(_In_ HWND hWnd);
BOOL WINAPI OnCreate(_In_ HWND hWnd, _In_ LPCREATESTRUCTW lpCreateStruct);
VOID WINAPI OnPaint(_In_ HWND hWnd);
ATOM WINAPI RegisterWCEX(_In_ HINSTANCE hInstance);
VOID CALLBACK TimerProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ UINT_PTR idEvent, _In_ DWORD dwTime);
LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
INT APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ INT nShowCmd);
