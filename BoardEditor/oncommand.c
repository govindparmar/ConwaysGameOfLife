#include "BE.h"

WCHAR g_wszFileName[MAX_PATH] = { L'\0' };

VOID WINAPI OnCommand(
	_In_ HWND hWnd,
	_In_ INT nID,
	_In_ HWND hwSource,
	_In_ UINT uNotify
)
{
	if (ID_FILE_NEW == nID)
	{
		if (g_fTouched)
		{
			if (MessageBoxW(NULL, L"Start a new file, discarding current unsaved changes?", APP_TITLE, MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				ResetBoardAndFile(hWnd);
			}
		}
		else
		{
			ResetBoardAndFile(hWnd);
		}
	}

	if (ID_FILE_OPEN == nID)
	{
		WCHAR wszOpenFile[MAX_PATH];
		DWORD dwError;

		BasicFileOpen(wszOpenFile);
		dwError = DeserializeGrid(hWnd, wszOpenFile);
		if (dwError != ERROR_SUCCESS)
		{
			MessageBoxW(NULL, L"Failed to open file", APP_TITLE, MB_OK | MB_ICONSTOP);
		}
		StringCchCopyW(g_wszFileName, MAX_PATH, wszOpenFile);
	}

	if (ID_FILE_SAVE == nID)
	{
		/*DWORD dwError;
		if (L'\0' == g_wszFileName[0])
		{
			WCHAR wszSaveFile[MAX_PATH];
			if (FAILED(BasicFileSave(wszSaveFile)))
			{
				MessageBoxW(NULL, L"Could not save the file", APP_TITLE, MB_OK | MB_ICONSTOP);
			}			
			dwError = SerializeGrid(wszSaveFile);
			if (dwError != ERROR_SUCCESS)
			{
				MessageBoxW(NULL, L"Could not save the file", APP_TITLE, MB_OK | MB_ICONSTOP);
			}
			else
			{
				g_fTouched = FALSE;
				StringCchCopyW(g_wszFileName, MAX_PATH, wszSaveFile);
			}
		}
		else
		{
			dwError = SerializeGrid(g_wszFileName);
			if (dwError != ERROR_SUCCESS)
			{
				MessageBoxW(NULL, L"Could not save the file", APP_TITLE, MB_OK | MB_ICONSTOP);
			}
			else
			{
				g_fTouched = FALSE;
			}
		}*/
		SaveBoardToFile(TRUE);
	}

	if (ID_FILE_SAVEAS == nID)
	{
		/*DWORD dwError;
		WCHAR wszSaveFile[MAX_PATH];
		if (FAILED(BasicFileSave(wszSaveFile)))
		{
			MessageBoxW(NULL, L"Could not save the file", APP_TITLE, MB_OK | MB_ICONSTOP);
		}
		dwError = SerializeGrid(wszSaveFile);
		if (dwError != ERROR_SUCCESS)
		{
			MessageBoxW(NULL, L"Could not save the file", APP_TITLE, MB_OK | MB_ICONSTOP);
		}
		else
		{
			g_fTouched = FALSE;
			StringCchCopyW(g_wszFileName, MAX_PATH, wszSaveFile);
		}*/
		SaveBoardToFile(FALSE);
	}

	if (ID_FILE_CLOSE == nID)
	{
		if (g_wszFileName[0] != L'\0')
		{
			ResetBoardAndFile(hWnd);
		}
	}
	
	if (ID_FILE_EXIT == nID)
	{
		if (g_fTouched)
		{
			if (MessageBoxW(NULL, L"You have unsaved changes. Really discard and exit?", APP_TITLE, MB_YESNO | MB_ICONWARNING) == IDYES)
			{
				DestroyWindow(hWnd);
			}
		}
		else
		{
			if (MessageBoxW(NULL, L"Really exit?", APP_TITLE, MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DestroyWindow(hWnd);
			}
		}
	}

	if (ID_HELP_ABOUT == nID)
	{
		DialogBoxW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(IDD_ABOUT), hWnd, DialogProc);
	}

	if (g_wszFileName[0] != L'\0')
	{
		WCHAR wszTitle[MAX_PATH + 100];
		StringCchPrintfW(wszTitle, MAX_PATH + 100, L"%s - %s %c", APP_TITLE, g_wszFileName, g_fTouched ? L'*' : L'\0');
		SetWindowTextW(hWnd, wszTitle);
	}

	return;
}
