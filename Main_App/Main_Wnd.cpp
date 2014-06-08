#include "Main_Wnd.h"

//#include "Default_WindowProc.h"

//to do ,通过元编程把winproc函数的封装起来

//Default_Window::real_wnd_proc_

Default_Window::Default_Window(HINSTANCE appinstance /*= NULL*/, 
    int nCmdShow /*= 0*/, std::string title /*= ""*/)
: app_instance_(appinstance), 
  cmdshow_(nCmdShow), 
  title_(title), 
  default_wnd_proc_(NULL)
{

}

Default_Window::~Default_Window()
{
    //free resouce
}

BOOL Default_Window::InitWnd()
{
    wnd_ = CreateWindow(
        "MainWClass",        // name of window class 
        title_.c_str(),            // title-bar string 
        WS_OVERLAPPEDWINDOW, // top-level window 
        CW_USEDEFAULT,       // default horizontal position 
        CW_USEDEFAULT,       // default vertical position 
        CW_USEDEFAULT,       // default width 
        CW_USEDEFAULT,       // default height 
        (HWND)NULL,         // no owner window 
        (HMENU)NULL,        // use class menu 
        app_instance_,           // handle to application instance 
        (LPVOID)NULL);      // no window-creation data 

    if (!wnd_)
        return FALSE;

    // Show the window and send a WM_PAINT message to the window 
    // procedure. 

    ShowWindow(wnd_, cmdshow_);
    UpdateWindow(wnd_);
    return TRUE;
}

BOOL Default_Window::DestoryWnd()
{
    //not impl, no throw,to send message 
    throw("not impl");
}

void Default_Window::SetStyle(int nstyle)
{
    throw("not impl");
}

BOOL Default_Window::Init()
{
    BOOL ret = FALSE;
    if (RegistProc() && RegistClass() && InitWnd())
    {
        /*lop_thread_ = new Threading::CThread("windproc", Bind(&Default_WindowProc::Loop, wnd_proc_));
        lop_thread_->Init();*/

        ret = TRUE;
    }

    return ret;
}

BOOL Default_Window::InitProc()
{
    // to impl factory mode
    //Default_WindowProc* pWndProc = new Default_WindowProc();

    /*if (NULL != pWndProc)
    {
        real_wnd_proc_ = pWndProc;
        return TRUE;
    }*/



    return FALSE;
}

void Default_Window::SetTitle(LPCTSTR title)
{
    title_ = title;
}

void Default_Window::SetTitle(std::string &title)
{
    title_ = title;
}

BOOL Default_Window::RegistClass()
{
    WNDCLASSEX wcx;

    // Fill in the window class structure with parameters 
    // that describe the main window. 

    //fun_callback1 f =
    //reinterpret_cast<fun_callback1>(fun_);

    wcx.cbSize = sizeof(wcx);          // size of structure 
    wcx.style = CS_HREDRAW |
        CS_VREDRAW;                    // redraw if size changes 
    //wcx.lpfnWndProc = &(proc_->WndProc);     // points to window procedure 
    wcx.lpfnWndProc = *default_wnd_proc_;     // points to window procedure 
    wcx.cbClsExtra = 0;                // no extra class memory 
    wcx.cbWndExtra = 0;                // no extra window memory 
    wcx.hInstance = app_instance_;         // handle to instance 
    wcx.hIcon = LoadIcon(NULL,
        IDI_APPLICATION);              // predefined app. icon 
    wcx.hCursor = LoadCursor(NULL,
        IDC_ARROW);                    // predefined arrow 
    wcx.hbrBackground = (HBRUSH)GetStockObject(
        WHITE_BRUSH);                  // white background brush 
    wcx.lpszMenuName = "MainMenu";    // name of menu resource 
    wcx.lpszClassName = "MainWClass";  // name of window class 
    wcx.hIconSm = (HICON)LoadImage(app_instance_, // small class icon 
        MAKEINTRESOURCE(5),
        IMAGE_ICON,
        GetSystemMetrics(SM_CXSMICON),
        GetSystemMetrics(SM_CYSMICON),
        LR_DEFAULTCOLOR);

    // Register the window class. 

    return RegisterClassEx(&wcx);
}

BOOL Default_Window::RegistProc()
{
    BOOL ret = FALSE;

    if (InitProc())
    {
        default_wnd_proc_ = WndProc;
        ret = TRUE;
    }

    return ret;
}

void Default_Window::Run()
{
    //lop_thread_->Start();
}

//--------------------------------------------------------------------------------
LRESULT __stdcall Default_Window::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    //get this
    static UINT s_uTaskbarRestart;

    switch (uMessage)
    {
    case WM_CREATE:
        s_uTaskbarRestart = RegisterWindowMessage(TEXT("TaskbarCreated"));
        break;

    case WM_DESTROY:
        return -1;

    default:
        if (uMessage == s_uTaskbarRestart)
            //AddTaskbarIcons();
            break;
    }

    return DefWindowProc(hWnd, uMessage, wParam, lParam);
}
