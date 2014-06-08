/** 
 * @file WndInterFace.h
 * @brief 
 * @author Luhaoqing 
 * @date 2014/1/14
 */
#ifndef WND_INTERFACE_DEF_H
#define WND_INTERFACE_DEF_H

#include "define.h"

class IWindow
{
public:
    typedef LRESULT(__stdcall *wnd_proc_callback)(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
};
#endif