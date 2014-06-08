/** 
 * @file ThreadDef.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 6/6/2013
 *
 * 详细说明   
 */
#ifndef THREAD_ATTRIB_H
#define THREAD_ATTRIB_H

#include <Windows.h>
#include <functional>
#include <string>

#define INVAILDHANDLE (unsigned long)-1
#define DEFAULT_TIME_TOCALL 500

typedef struct ThreadAttribute_ {
    HANDLE	thread_;				//thread handle
    HANDLE	stopsig_;				//sig to stop thread
    HANDLE	tmpsig_;				//sig to pause thread
    DWORD	interval_;				//time to wait

    ThreadAttribute_()
        : thread_(INVALID_HANDLE_VALUE)
        , stopsig_(CreateEvent( 0, FALSE, FALSE, 0 ))
        , tmpsig_(CreateEvent( 0, FALSE, TRUE, 0 ))
        , interval_(DEFAULT_TIME_TOCALL) 
    {};

    ThreadAttribute_(DWORD TimetoCall)
        : thread_(INVALID_HANDLE_VALUE)
        , stopsig_(CreateEvent( 0, FALSE, FALSE, 0 ))
        , tmpsig_(CreateEvent( 0, FALSE, TRUE, 0 ))
        , interval_(TimetoCall) 
    {};

} ThreadAttribute;

typedef std::function<void(void)> Closure;

typedef struct ThreadInfo_ {
    const std::string name_;
    unsigned int id_;

    ThreadInfo_()
        :name_("")
        ,id_(INVAILDHANDLE) 
    {}

    explicit ThreadInfo_(const char* threadname)
        : name_(threadname)
        , id_(INVAILDHANDLE) 
    {}
} ThreadInfo;

typedef struct ProcessInfo_ {
    const std::string name_;
    unsigned long id_;

    ProcessInfo_()
        : name_("")
        , id_(INVAILDHANDLE)
    {

    }

    explicit ProcessInfo_(const char* name)
        : name_(name)
        , id_(INVAILDHANDLE)
    {

    }
} ProcessInfo;

#endif