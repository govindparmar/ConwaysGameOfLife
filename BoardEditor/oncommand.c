#include "BE.h"

typedef HRESULT(WINAPI *pOpenGGLFile)(_Out_writes_z_(MAX_PATH) WCHAR *wszFileName);
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
		HINSTANCE hInstDLL = NULL;
		pOpenGGLFile OpenGGLFile = NULL;
		WCHAR wszOpenFile[MAX_PATH];
		DWORD dwError;

		hInstDLL = LoadLibraryW(L"FileDialogs.dll");
		if (NULL == hInstDLL)
		{
			dwError = GetLastError();
			MessageBoxW(NULL, L"Could not launch the open file dialog because the library FileDialogs.dll was not found", APP_TITLE, MB_OK | MB_ICONSTOP);
			//ExitProcess(dwError);
			return;
		}

		OpenGGLFile = (pOpenGGLFile) GetProcAddress(hInstDLL, "OpenGGLFile");
		if (NULL == OpenGGLFile)
		{
			dwError = GetLastError();
			MessageBoxW(NULL, L"Could not find the procedure 'OpenGGLFile' in the library FileDialogs.dll", APP_TITLE, MB_OK | MB_ICONSTOP);
			FreeLibrary(hInstDLL);
			return;
		}

		OpenGGLFile(wszOpenFile);
		dwError = DeserializeGrid(hWnd, wszOpenFile);
		if (dwError != ERROR_SUCCESS)
		{
			MessageBoxW(NULL, L"Failed to read grid file", APP_TITLE, MB_OK | MB_ICONSTOP);
		}
		StringCchCopyW(g_wszFileName, MAX_PATH, wszOpenFile);
	}

	if (ID_FILE_SAVE == nID)
	{
		SaveBoardToFile(TRUE);
	}

	if (ID_FILE_SAVEAS == nID)
	{
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
