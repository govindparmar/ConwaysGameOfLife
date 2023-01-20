#include "BE.h"

INT_PTR CALLBACK DialogProc(
	_In_ HWND hDlg,
	_In_ UINT Msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	switch (Msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{
		EndDialog(hDlg, (INT_PTR) 0);
	}
	case WM_INITDIALOG:
		return (INT_PTR) 1;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, (INT_PTR) 0);
		}
	}
	return (INT_PTR) 0;
}
