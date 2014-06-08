/** 
 * @file automicptr.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 17/5/2013
 *
 * 详细说明   
 */
#ifndef AUTOMIC_PTR_H
#define AUTOMIC_PTR_H

#include <Windows.h>

template <typename T>
class Atomic_Ptr
{
public:
    inline Atomic_Ptr() : ptr_(NULL)
    {

    }

    inline ~Atomic_Ptr() {}

    inline void Set(T* ptr) {ptr_ = ptr;};

    inline T* xchg(T * val)
    {
        return (T*) InterlockedExchangePointer ((PVOID*) &ptr, val_);
    }

    inline T *cas (T *cmp, T *val)
    {
        return (T*) InterlockedCompareExchangePointer (
            (volatile PVOID*) &ptr, val, cmp);
    }

private:
   volatile  T* ptr_;

   Atomic_Ptr(const Atomic_Ptr&);
   const Atomic_Ptr& operator = (const Atomic_Ptr&);
};
#endif