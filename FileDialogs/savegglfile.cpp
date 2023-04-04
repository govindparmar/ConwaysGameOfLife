#include "DialogEventHandler.h"
#include <Windows.h>

_Success_(SUCCEEDED(return))

HRESULT WINAPI SaveGGLFile(_Out_writes_z_(MAX_PATH) WCHAR *pSaveFileName)
{
    IFileDialog *pfd = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
    if (SUCCEEDED(hr))
    {
        IFileDialogEvents *pfde = nullptr;
        hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
        if (SUCCEEDED(hr))
        {
            DWORD dwCookie;
            hr = pfd->Advise(pfde, &dwCookie);
            if (SUCCEEDED(hr))
            {
                hr = pfd->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
                if (SUCCEEDED(hr))
                {
                    hr = pfd->Show(nullptr);
                    if (SUCCEEDED(hr))
                    {
                        IShellItem *psr = nullptr;
                        hr = pfd->GetResult(&psr);
                        if (SUCCEEDED(hr))
                        {
                            PWSTR pwfp = nullptr;
                            hr = psr->GetDisplayName(SIGDN_FILESYSPATH, &pwfp);
                            if (SUCCEEDED(hr))
                            {
                                StringCchCopyW(pSaveFileName, MAX_PATH, pwfp);
                                if (wcsstr(pSaveFileName, L".ggl") == nullptr)
                                {
                                    StringCchCatW(pSaveFileName, MAX_PATH, L".ggl");
                                }
                                CoTaskMemFree(pwfp);
                            }
                            psr->Release();
                        }
                    }
                }
            }
            pfd->Unadvise(dwCookie);
        }
        pfde->Release();
    }
    pfd->Release();

    return hr;
}