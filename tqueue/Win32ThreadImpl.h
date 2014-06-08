#ifndef WIN32THREAD_IMPL_H
#define WIN32THREAD_IMPL_H

#include "WorkerImpl.h"
#include <Windows.h>
#include <share.h>
#include <memory>


class Win32ThreadImpl : public WorkerImpl
{
public:
    explicit Win32ThreadImpl(Closure& closure);

    explicit Win32ThreadImpl(Closure& closure, const char* name);

    ~Win32ThreadImpl();

    //初始化方法
    virtual bool Init();

    //开始
    virtual bool Start();

    //结束
    virtual bool Stop();

    //暂停
    virtual bool Pause();

    //释放对象
    virtual bool UnInit();

    virtual const char* GetName() const ;

    static UINT WINAPI WorkFunc( LPVOID lpParam );

    virtual int GetId() const;

    virtual HANDLE GetHandle() const;

private:

    void SetName(unsigned int id, const char* name);

private:
    //WorkAttrib attrib_;

    Closure closure_;

    ThreadInfo_ thread_info_;

    std::shared_ptr<ThreadAttribute> thread_attrib_;
};

#endif