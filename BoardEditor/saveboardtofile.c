#include "BE.h"

typedef HRESULT(WINAPI *pSaveGGLFile)(_Out_writes_z_(MAX_PATH) WCHAR *wszFileName);

BOOL WINAPI SaveBoardToFile(_In_ BOOL fSkipNamingIfPossible)
{
	HINSTANCE hInstDLL = NULL;
	pSaveGGLFile SaveGGLFile = NULL;
	DWORD dwError;
	WCHAR wszSavePath[MAX_PATH];

	if (fSkipNamingIfPossible && g_wszFileName[0] != L'\0')
	{
		StringCchCopyW(wszSavePath, MAX_PATH, g_wszFileName);
		goto savegrid;
	}

	hInstDLL = LoadLibraryW(L"FileDialogs.dll");
	if (NULL == hInstDLL)
	{
		dwError = GetLastError();
		MessageBoxW(NULL, L"Could not launch the save file dialog because the library FileDialogs.dll was not found", APP_TITLE, MB_OK | MB_ICONSTOP);
		SetLastError(dwError);
		return FALSE;
	}

	SaveGGLFile = (pSaveGGLFile) GetProcAddress(hInstDLL, "SaveGGLFile");
	if (NULL == SaveGGLFile)
	{
		dwError = GetLastError();
		MessageBoxW(NULL, L"Could not find the procedure 'SaveGGLFile' in the library FileDialogs.dll", APP_TITLE, MB_OK | MB_ICONSTOP);
		FreeLibrary(hInstDLL);
		SetLastError(dwError);
		return FALSE;
	}

	if (FAILED(SaveGGLFile(wszSavePath)))
	{
		FreeLibrary(hInstDLL);
		return FALSE;
	}
	FreeLibrary(hInstDLL);

savegrid:
	dwError = SerializeGrid(wszSavePath);
	if (dwError != ERROR_SUCCESS)
	{
		SetLastError(dwError);
		return FALSE;
	}
	g_fTouched = FALSE;
	StringCchCopyW(g_wszFileName, MAX_PATH, wszSavePath);
	SetLastError(ERROR_SUCCESS);
	return TRUE;
}
