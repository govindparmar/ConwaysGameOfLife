#include "BE.h"

BOOL WINAPI SaveBoardToFile(_In_ BOOL fSkipNamingIfPossible)
{
	DWORD dwError;
	WCHAR wszSavePath[MAX_PATH];

	if (fSkipNamingIfPossible && g_wszFileName[0] != L'\0')
	{
		StringCchCopyW(wszSavePath, MAX_PATH, g_wszFileName);
		goto savegrid;
	}
	if (FAILED(BasicFileSave(wszSavePath)))
	{
		return FALSE;
	}

savegrid:
	dwError = SerializeGrid(wszSavePath);
	if (dwError != ERROR_SUCCESS)
	{
		return FALSE;
	}
	g_fTouched = FALSE;
	StringCchCopyW(g_wszFileName, MAX_PATH, wszSavePath);
	return TRUE;
}
