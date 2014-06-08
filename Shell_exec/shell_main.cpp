#include <windows.h>
#include <tchar.h>
#include <export.h>
#include <vector>

int __stdcall _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    _In_ LPTSTR lpCmdLine, int nCmdShow)
{  
	return App_EntryPoint(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}