/** 
 * @file lock.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 18/6/2013
 *
 * 详细说明   
 */
#ifndef LOCK_H
#define LOCK_H

template <typename Impl>
class Lock {
public: 
    Lock() {};

    ~Lock() {};

    void Acquire() 
    { 
        lock_.Lock();
    }

    void Release() 
    {
        lock_.Unlock();
    }

    bool Try() {
        return lock_.Try();
    }

    //void AssertAcquired() const;

#if defined(OS_POSIX)
    // The posix implementation of ConditionVariable needs to be able
    // to see our lock and tweak our debugging counters, as it releases
    // and acquires locks inside of pthread_cond_{timed,}wait.
    friend class ConditionVariable;
#elif defined(WIN32)
    // The Windows Vista implementation of ConditionVariable needs the
    // native handle of the critical section.
    //friend class WinVistaCondVar;
    ;

private:
    Impl lock_;
#endif
};

// A helper class that acquires the given Lock while the AutoLock is in scope.
class AutoLock {
public:
    explicit AutoLock(Lock<LockImpl>& lock) : lock_(lock) {
        lock_.Acquire();
    }

    ~AutoLock() {
        //lock_.AssertAcquired();
        lock_.Release();
    }

private:
    Lock<LockImpl>& lock_;
    //DISALLOW_COPY_AND_ASSIGN(AutoLock);
};

// AutoUnlock is a helper that will Release() the |lock| argument in the
// constructor, and re-Acquire() it in the destructor.
class AutoUnlock {
public:
    explicit AutoUnlock(Lock<LockImpl>& lock) : lock_(lock) {
        // We require our caller to have the lock.
        //lock_.AssertAcquired();
        lock_.Release();
    }

    ~AutoUnlock() {
        lock_.Acquire();
    }

private:
    Lock<LockImpl>& lock_;
};

#endif