/** 
 * @file Singleton.h
 * @brief singleton file template
 * @author Luhaoqing 
 * @date 2013/11/20
 */
#ifndef SINGLETON_DEFINE_H
#define SINGLETON_DEFINE_H

#include "Lock/Lock.h"

namespace base {
template <typename T, typename Lock>
class Singleton
{
public:
    static T* Ins()
    {
        //static Singleton<T, Lock> ins;
        static T ins;
        return &ins;
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}

private:
    //T* ins_;*/
};

//typedef Singleton<T, NullLock> Single_No_Lock<T>;


}//base

#define Single_No_Lock(T) base::Singleton<T, base::NullLock>

#define Declare_Friend(T) friend Single_No_Lock(T);

#endif