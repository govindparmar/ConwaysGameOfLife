#include "CGOL.h"

typedef HRESULT(WINAPI *pOpenGGLFile)(_Out_writes_z_(MAX_PATH) WCHAR *wszFileName);

_Success_(ERROR_SUCCESS == return)
_Check_return_

DWORD WINAPI OpenBoard(_In_ HWND hWnd)
{
	HINSTANCE hInstDLL = NULL;
	pOpenGGLFile OpenGGLFile = NULL;
	DWORD dwError;
	WCHAR wszFileName[MAX_PATH];

	hInstDLL = LoadLibraryW(L"FileDialogs.dll");
	if (NULL == hInstDLL)
	{
		dwError = GetLastError();
		MessageBoxW(NULL, L"Could not launch the open file dialog because the library FileDialogs.dll was not found", APP_TITLE, MB_OK | MB_ICONSTOP);
		goto cleanup;
	}

	OpenGGLFile = (pOpenGGLFile) GetProcAddress(hInstDLL, "OpenGGLFile");
	if (NULL == OpenGGLFile)
	{
		dwError = GetLastError();
		MessageBoxW(NULL, L"Could not find the procedure 'OpenGGLFile' in the library FileDialogs.dll", APP_TITLE, MB_OK | MB_ICONSTOP);
		goto cleanup;
	}

	if (SUCCEEDED(OpenGGLFile(wszFileName)))
	{
		if (LoadGridFile(wszFileName, hWnd))
		{
			g_fGameRunning = TRUE;
		}
	}
	dwError = ERROR_SUCCESS;
cleanup:
	if (hInstDLL != NULL)
	{
		FreeLibrary(hInstDLL);
	}

	return dwError;

}