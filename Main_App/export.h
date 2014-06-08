/** 
 * @file export.h
 * @brief 
 * @author Luhaoqing 
 * @date 2014/1/3
 */
#ifndef MAIN_APP_EXPORT_H
#define MAIN_APP_EXPORT_H

#include "define.h"

#ifdef Lib_EXPORT
#define _DECLARE_APP
#else
#ifndef _DECLARE_APP
#define _DECLARE_APP __declspec(dllexport)
#else
#define _DECLARE_APP __declspec(dllimport)
#endif
#endif

//declare output func here

int _DECLARE_APP App_EntryPoint(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    _In_ LPTSTR lpCmdLine, int nCmdShow);

#endif