/** 
 * @file WorkerImpl.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 6/6/2013
 *
 * 详细说明   
 */
#ifndef WORKER_IMPL_H
#define WORKER_IMPL_H

#include "ThreadDef.h"
#include <string>


/// Worker Bind Call, call to get tasklist then call task->worker(task->param);
class WorkerImpl
{
public:
    //初始化方法
    virtual bool Init() = 0;

    //开始
    virtual bool Start() = 0;

    //结束
    virtual bool Stop() = 0;

    //暂停
    virtual bool Pause() = 0; 

    //释放对象
    virtual bool UnInit() = 0;

    //
    virtual const char* GetName() const = 0;

    virtual int GetId() const = 0;

    virtual HANDLE GetHandle() const = 0;


    //Closure& closure_;
};

#endif // !WORKER_IMPL_H
