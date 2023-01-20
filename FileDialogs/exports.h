#include "DialogEventHandler.h"
#include <Windows.h>
#include <sal.h>
#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
	_Success_(SUCCEEDED(return))

	HRESULT WINAPI OpenGGLFile(_Out_writes_z_(MAX_PATH) WCHAR *pOutFileName);

	_Success_(SUCCEEDED(return))

	HRESULT WINAPI SaveGGLFile(_Out_writes_z_(MAX_PATH) WCHAR *pSaveFileName);
#ifdef __cplusplus
} // extern "C"
#endif