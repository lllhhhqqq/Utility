/** 
 * @file main_app.h
 * @brief 
 * @author Luhaoqing 
 * @date 2014/1/3
 */
#ifndef MAIN_APP_DEF_H
#define MAIN_APP_DEF_H

#include <design_pattern/Singleton.h>
#include <Lock/Lock.h>

#include "Base_App.h"

class Param;

class CApp_Ins 
    : public IBaseApplication
    , public Single_No_Lock(CApp_Ins)
{
private:
    CApp_Ins() {}
    
public:
    virtual ~CApp_Ins() {}

    bool Init(HINSTANCE hInstance, LPTSTR lpCmdLine, int nCmdShow) override;

    //Need Run In main thread
    bool Run() override;

    bool UnInit() override;

public:
    HINSTANCE const GetAppInstance() const { return app_instance_; }

private:
    /************************************************************************/
    /* Inner Function                                                       */
    /************************************************************************/
    void SetAppInstance(HINSTANCE instance) { app_instance_ = instance; }

    void ParseParam(LPCTSTR cmd);

private:
    /************************************************************************/
    /* attribute                                                            */
    /************************************************************************/
    //main app instance
    HINSTANCE app_instance_;

    //parameters
    //Param& app_param_;

    /************************************************************************/
    /* other                                                                */
    /************************************************************************/
    Declare_Friend(CApp_Ins)
};

#endif