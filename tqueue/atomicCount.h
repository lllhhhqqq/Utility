/** 
 * @file atomicCount.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 17/5/2013
 *
 * 详细说明   
 */
#ifndef ATOMIC_COUNT_H
#define ATOMIC_COUNT_H

#include <Windows.h>

class Atomic_Count
{
public:
    typedef unsigned int integer_t;

    inline Atomic_Count( integer_t value = 0 )
        :value_(value)
    {

    }

    inline ~Atomic_Count() {}

    inline void Set(integer_t value) { value_ = value; }

    inline integer_t Add (integer_t increment_)
    {
        integer_t old_value;
        old_value = InterlockedExchangeAdd ((long long*) &value, increment_);
        return old_value;
    }

    inline bool Sub(integer_t decrement)
    {
        long delta = - ((long long) decrement);
        integer_t old = InterlockedExchangeAdd ((long long*) &value, delta);
        return old - decrement != 0;
    }

    inline integer_t Get ()
    {
        return value_;
    }

private:

    volatile integer_t value_;
};
#endif