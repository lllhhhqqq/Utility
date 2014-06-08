/** 
 * @file Lock.h
 * @brief 
 * @author Luhaoqing 
 * @date 2013/11/20
*/
#ifndef _LOCK_H_
#define _LOCK_H_

namespace base {
    class NullLock
    {
    public:
        void lock() {}
        void unlock() {}
    };

template <typename LockImpl>
class Lock
{
public:
    explicit Lock(LockImpl* impl = NULL) : impl_(impl) {}
    virtual ~Lock() {}

    void lock()
    {
        impl_.lock();
    }

    void unlock()
    {
        impl_.unlock();
    }

    LockImpl* impl_;
};

typedef Lock<NullLock> NULL_LOCK;
}//base
#endif