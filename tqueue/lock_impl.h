/** 
 * @file lock_impl.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 18/6/2013
 *
 * 详细说明   
 */
#ifndef LOCKIMPL_H
#define LOCKIMPL_H

#if defined(WIN32)
#include <windows.h>
#elif defined(OS_POSIX)
#include <pthread.h>
#endif

class LockImpl {

public:
#if defined(WIN32)
    typedef CRITICAL_SECTION OSLockType;
#elif defined(OS_POSIX)
    typedef pthread_mutex_t OSLockType;
#endif
    LockImpl();
    ~LockImpl();

    bool Try();

    void Lock();

    void Unlock();

    OSLockType* os_lock() {return &os_lock_;}
private:
    OSLockType os_lock_;

};

class Null_LockImpl {
public:
    typedef int OSLockType;
    Null_LockImpl() {};
    ~Null_LockImpl() {};

    inline bool Try() {return true;};

    void Lock() {};

    void Unlock() {};

    OSLockType* os_lock() {return NULL;}
};

#endif