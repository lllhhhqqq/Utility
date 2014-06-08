#include "main_app.h"

bool CApp_Ins::Init(HINSTANCE hInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    
    bool ret = true;

    SetAppInstance(hInstance);

    ParseParam(lpCmdLine);

    return ret;
}

bool CApp_Ins::Run()
{
    bool ret = false;

    return ret;
}

bool CApp_Ins::UnInit()
{
    bool ret = false;

    return ret;
}

void CApp_Ins::ParseParam(LPCTSTR cmd)
{

}
