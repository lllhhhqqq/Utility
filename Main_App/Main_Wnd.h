/** 
 * @file Main_Wnd.h
 * @brief 
 * @author Luhaoqing 
 * @date 2014/1/3
 */
#ifndef MAIN_WND_DEF_H
#define MAIN_WND_DEF_H

#include "WndInterFace.h"

class CWndProc;

//main wnd
class Default_Window
    : public IWindow
{
public:
    explicit Default_Window(HINSTANCE appinstance = NULL, int nCmdShow = 0, 
        std::string title = "");

    virtual ~Default_Window();

public:

    //the function to init the window whole
    virtual BOOL Init();

    void Run();

    //Attrib
    //--set function here
    void SetTitle(LPCTSTR title);

    void SetTitle(std::string &title);

    //--get function here
    HWND const GetWnd() const { return wnd_; }

    CWndProc* const GetProc() const { return real_wnd_proc_; }

    LPCTSTR GetTitle() const { return title_.c_str(); }

private:

    //the function to Create windows
    BOOL InitWnd();

    virtual BOOL InitProc();

    BOOL RegistProc();

    BOOL RegistClass();

    //the funciton to destory windows
    BOOL DestoryWnd();

    //the function to set style
    virtual void SetStyle(int nstyle);

    //how to show in the windows titlebar
    std::string title_;

    //the style to show
    int cmdshow_;

protected:

    //the window handle 
    HWND	wnd_;

    //main app instance
    HINSTANCE   app_instance_;

    //regist the wndproc class
    static CWndProc* real_wnd_proc_;

    wnd_proc_callback default_wnd_proc_;

private:
    static LRESULT __stdcall WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

    DISALLOW_COPY_ASSIGN(Default_Window)
};

#endif