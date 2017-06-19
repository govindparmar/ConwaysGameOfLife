#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>
#include <sal.h>

#define IDT_TIMER1 1001
#define EXTERN extern
#define GRIDSIZE 40
#define CELLSIZE 20

EXTERN CONST WCHAR g_wszClassName[];
EXTERN INT g_aGrid[GRIDSIZE][GRIDSIZE];
EXTERN INT g_aUpdate[GRIDSIZE][GRIDSIZE];
EXTERN HDC g_hDC;
EXTERN HBRUSH g_hbrCell;
EXTERN HBRUSH g_hbrBackground;

VOID WINAPI OnClose(_In_ HWND hWnd);
VOID WINAPI OnDestroy(_In_ HWND hWnd);
BOOL WINAPI OnCreate(_In_ HWND hWnd, _In_ LPCREATESTRUCTW lpCreateStruct);
ATOM WINAPI RegisterWCEX(_In_ HINSTANCE hInstance);
VOID CALLBACK TimerProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ UINT_PTR idEvent, _In_ DWORD dwTime);
LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam);
INT APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_z_ LPWSTR lpCmdLine, _In_ INT nShowCmd);
