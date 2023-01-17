#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <stdlib.h>
#include <time.h>
#include <strsafe.h>
#include <sal.h>
#include "..\Common\GameBoard.h"


#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#define APP_TITLE L"Conway\'s Game Of Life"
#define TIMER_TICK 100
#define IDT_TIMER1 1001
#define MB_YESNOQUESTION (MB_YESNO | MB_ICONQUESTION)
#define EXTERN extern

#ifdef __cplusplus
extern "C"
{
#endif

	EXTERN CONST WCHAR g_wszClassName[];
	EXTERN INT g_aGrid[GRIDSIZE][GRIDSIZE];
	EXTERN INT g_aUpdate[GRIDSIZE][GRIDSIZE];
	EXTERN HDC g_hDC;
	EXTERN HBRUSH g_hbrCell;
	EXTERN HBRUSH g_hbrBackground;
	EXTERN BOOL g_fGameRunning;
	EXTERN RECT *g_pMenuItems;
	EXTERN RECT g_clientRect;

	_Success_(SUCCEEDED(return))

	HRESULT WINAPI BasicFileOpen(_Out_writes_z_(MAX_PATH) WCHAR *pOutFileName);
	
	VOID WINAPI InitializeGameGrid(_In_ HWND hWnd);

	_Ret_range_(FALSE, TRUE)

	BOOL WINAPI IsWithinRect(_In_ RECT rect, _In_ INT x, _In_ INT y);
	BOOL WINAPI LoadGridFile(_In_reads_or_z_(MAX_PATH) WCHAR *wszFileName, _In_ HWND hWnd); // 2nd param for GetClientRect call;
	VOID WINAPI MenuScreen();
	VOID WINAPI OnChar(_In_ HWND hWnd, _In_ WCHAR wc, _In_ INT nRepeat);
	VOID WINAPI OnClose(_In_ HWND hWnd);
	VOID WINAPI OnDestroy(_In_ HWND hWnd);
	BOOL WINAPI OnCreate(_In_ HWND hWnd, _In_ LPCREATESTRUCTW lpCreateStruct);
	VOID WINAPI OnLButtonDown(_In_ HWND hwnd, _In_ BOOL fDoubleClick, _In_ INT x, _In_ INT y, _In_ UINT keyFlags);
	VOID WINAPI OnMouseMove(_In_ HWND hWnd, _In_ INT x, _In_ INT y, _In_ UINT keyFlags);
	VOID WINAPI OnPaint(_In_ HWND hWnd);
	ATOM WINAPI RegisterWCEX(_In_ HINSTANCE hInstance);
	VOID CALLBACK TimerProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ UINT_PTR idEvent, _In_ DWORD dwTime);
	LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
	INT APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ INT nShowCmd);

#ifdef __cplusplus
}
#endif