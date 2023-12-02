#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <strsafe.h>
#include <sal.h>
#include "resource.h"
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

#define EXTERN extern
#define APP_TITLE L"Game of Life Board Editor"



EXTERN INT g_nCells[GRIDSIZE][GRIDSIZE];

_Success_(ERROR_SUCCESS == return)
_Check_return_

DWORD WINAPI DeserializeGrid(_In_ HWND hWnd, _In_reads_or_z_(MAX_PATH) WCHAR *wszFileName);
INT_PTR CALLBACK DialogProc(
	_In_ HWND hDlg,
	_In_ UINT Msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

_Success_(TRUE)
_Post_satisfies_(g_hbrFilled != NULL && g_hbrEmpty != NULL && g_hbrEmptyAlternate != NULL)

VOID WINAPI DrawGrid(_In_ HWND hWnd);
BOOL CALLBACK EnumChildProc(
	_In_ HWND hWnd,
	_In_ LPARAM lParam
);
VOID WINAPI OnClose(_In_ HWND hWnd);
VOID WINAPI OnCommand(
	_In_ HWND hWnd,
	_In_ INT nID,
	_In_ HWND hwSource,
	_In_ UINT uNotify
);
BOOL WINAPI OnCreate(_In_ HWND hWnd, _In_ LPCREATESTRUCTW lpCreateStruct);
VOID WINAPI OnDestroy(_In_ HWND hWnd);
VOID WINAPI OnLButtonDown(_In_ HWND hWnd, _In_ BOOL fDoubleClick, _In_ INT x, _In_ INT y, _In_ UINT keyFlags);
VOID WINAPI OnPaint(_In_ HWND hWnd);

_Success_(return)
_Check_return_

ATOM WINAPI RegisterWCEX(_In_ HINSTANCE hInstance);

_Post_satisfies_(!g_fTouched && L'\0' == g_wszFileName[0])

VOID WINAPI ResetBoardAndFile(_In_ HWND hWnd);

_Success_(return)
_Check_return_
_Post_satisfies_(!g_fTouched)

BOOL WINAPI SaveBoardToFile(_In_ BOOL fSkipNamingIfPossible);

_Success_(ERROR_SUCCESS == return)
_Check_return_

DWORD WINAPI SerializeGrid(_In_reads_or_z_(MAX_PATH) WCHAR *wszFileName);
LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
INT APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ INT nShowCmd);

EXTERN CONST WCHAR g_wszClassName[];
EXTERN WCHAR g_wszFileName[MAX_PATH];
EXTERN BOOL g_fTouched;
EXTERN BOOL g_fFileOpen;
EXTERN HBRUSH g_hbrFilled, g_hbrEmpty, g_hbrEmptyAlternate;
