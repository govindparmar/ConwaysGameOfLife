#include "DialogEventHandler.h"

_Success_(SUCCEEDED(return))

HRESULT WINAPI CDialogEventHandler_CreateInstance(_In_ REFIID riid, _In_ LPVOID *ppv)
{
    *ppv = nullptr;
    CDialogEventHandler *pDialogEventHandler = new (std::nothrow) CDialogEventHandler();
    HRESULT hr = pDialogEventHandler ? S_OK : E_OUTOFMEMORY;
    if (SUCCEEDED(hr))
    {
        hr = pDialogEventHandler->QueryInterface(riid, ppv);
        pDialogEventHandler->Release();
    }
    return hr;
}
