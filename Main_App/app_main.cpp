#include "export.h"
#include "main_app.h"

int App_EntryPoint(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    _In_ LPTSTR lpCmdLine, int nCmdShow)
{
    int error_num = ERROR_SUCCESS;
    if (CApp_Ins::Ins()->Init(hInstance, lpCmdLine, nCmdShow)
        && CApp_Ins::Ins()->Run()) 
        ;
    
    CApp_Ins::Ins()->UnInit();

    return error_num;
    //return 0;
}