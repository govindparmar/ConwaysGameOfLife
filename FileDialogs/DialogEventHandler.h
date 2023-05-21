#pragma once
#include <Windows.h>
#define STRICT_TYPED_ITEMIDS
#include <shlobj.h>
#include <objbase.h>      
#include <shobjidl.h>     
#include <shlwapi.h>
#include <knownfolders.h> 
#include <propvarutil.h>  
#include <propkey.h>      
#include <propidl.h>      
#include <strsafe.h>      
#include <shtypes.h>      
#include <new>

#define STATIC static

const COMDLG_FILTERSPEC fileTypes[] =
{
    {L"Game of Life Board files (*.ggl)", L"*.ggl"},
    {L"All Files (*.*)", L"*.*" }
};

class CDialogEventHandler : public IFileDialogEvents, public IFileDialogControlEvents
{
public:
    // IUnknown methods
    IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        STATIC CONST QITAB qit[] = {
            QITABENT(CDialogEventHandler, IFileDialogEvents),
            QITABENT(CDialogEventHandler, IFileDialogControlEvents),
            { 0 },
#pragma warning(suppress:4838)
        };
        return QISearch(this, qit, riid, ppv);
    }

    IFACEMETHODIMP_(ULONG) AddRef()
    {
        return InterlockedIncrement(&_cRef);
    }

    IFACEMETHODIMP_(ULONG) Release()
    {
        LONG cRef = InterlockedDecrement(&_cRef);
        if (!cRef)
        {
            delete this;
        }
        return cRef;
    }

    // IFileDialogEvents methods
    IFACEMETHODIMP OnFileOk(IFileDialog *) 
    { 
        return S_OK; 
    };
    IFACEMETHODIMP OnFolderChange(IFileDialog *) 
    { 
        return S_OK; 
    };
    IFACEMETHODIMP OnFolderChanging(IFileDialog *, IShellItem *) 
    {
        return S_OK; 
    };
    IFACEMETHODIMP OnHelp(IFileDialog *) 
    {
        return S_OK; 
    };
    IFACEMETHODIMP OnSelectionChange(IFileDialog *) 
    { 
        return S_OK; 
    };
    IFACEMETHODIMP OnShareViolation(IFileDialog *, IShellItem *, FDE_SHAREVIOLATION_RESPONSE *) 
    { 
        return S_OK; 
    };
    IFACEMETHODIMP OnTypeChange(IFileDialog *pfd) 
    { 
        return S_OK; 
    };
    IFACEMETHODIMP OnOverwrite(IFileDialog *, IShellItem *, FDE_OVERWRITE_RESPONSE *) 
    { 
        return S_OK; 
    };

    // IFileDialogControlEvents methods
    IFACEMETHODIMP OnItemSelected(IFileDialogCustomize *, DWORD, DWORD) 
    { 
        return S_OK; 
    };
    IFACEMETHODIMP OnButtonClicked(IFileDialogCustomize *, DWORD) 
    { 
        return S_OK; 
    };
    IFACEMETHODIMP OnCheckButtonToggled(IFileDialogCustomize *, DWORD, BOOL) 
    { 
        return S_OK; 
    };
    IFACEMETHODIMP OnControlActivating(IFileDialogCustomize *, DWORD) 
    { 
        return S_OK; 
    };

    CDialogEventHandler() : _cRef(1) 
    {

    };
private:
    virtual ~CDialogEventHandler()
    {
    };
    long _cRef;
};

_Success_(SUCCEEDED(return))

HRESULT WINAPI CDialogEventHandler_CreateInstance(_In_ REFIID riid, _In_ LPVOID *ppv);
