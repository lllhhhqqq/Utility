/** 
 * @file Base_App.h
 * @brief 
 * @author Luhaoqing 
 * @date 2014/1/3
 */
#ifndef BASE_APP_DEF_H
#define BASE_APP_DEF_H

#include "define.h"

//to do, Inter face need move to public 
class IEnv;

//HINSTANCE hInstance, HINSTANCE hPrevInstance,_In_ LPTSTR lpCmdLine, int nCmdShow)

class IBaseApplication
{
public:
    virtual bool Init(HINSTANCE, LPTSTR,int) = 0;

    //Need Run In main thread
    virtual bool Run() = 0;

    virtual bool UnInit() = 0;
};

#endif