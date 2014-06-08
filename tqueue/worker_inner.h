/** 
 * @file worker_inner.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 5/6/2013
 *
 * 详细说明   
 */
#ifndef WORKER_INNER_H
#define WORKER_INNER_H

class BaseWork
{
    virtual void Run(ParamList& param) = 0;
};

#define FetchValue(i) param[i]

//make paramlist, using tuple
//////////////////////////////////////////////////////////////////////////
//0
template <typename Return>
inline void BindImpl(Return (*fun)(), ParamList& param)
{
    FetchValue(0) = (*fun)();
}

template <typename Return, typename Cls>
inline void BindImpl(Return (Cls::*fun)(), ParamList& param)
{
    FetchValue(0) = (*fun)();
}

template <>
inline void BindImpl(void (*fun)(), ParamList& param)
{
    (*fun)();
}

template <typename Cls>
inline void BindImpl(void (Cls::*fun)(), ParamList& param)
{
    (*fun)();
}

//1
template <typename Return, typename P1>
inline void BindImpl(Return (*fun)(P1), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1));
}

template <typename Return, typename Cls, typename P1>
inline void BindImpl(Return (Cls::*fun)(P1), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1));
}

template <typename P1>
inline void BindImpl(void (*fun)(P1), ParamList& param)
{
    (*fun)(FetchValue(1));
}

template <typename Cls, typename P1>
inline void BindImpl(void (Cls::*fun)(P1), ParamList& param)
{
    (*fun)(FetchValue(1));
}

//2
template <typename Return, typename P1, typename P2>
inline void BindImpl(Return (*fun)(P1, P2), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2));
}

template <typename Return, typename Cls, typename P1, typename P2>
inline void BindImpl(Return (Cls::*fun)(P1, P2), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2));
}

template <typename P1, typename P2>
inline void BindImpl(void (*fun)(P1, P2), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2));
}

template <typename Cls, typename P1, typename P2>
inline void BindImpl(void (Cls::*fun)(P1, P2), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2));
}

//3
template <typename Return, typename P1, typename P2, typename P3>
inline void BindImpl(Return (*fun)(P1, P2, P3), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3));
}

template <typename Return, typename Cls, typename P1, typename P2, typename P3>
inline void BindImpl(Return (Cls::*fun)(P1, P2, P3), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3));
}

template <typename P1, typename P2, typename P3>
inline void BindImpl(void (*fun)(P1, P2, P3), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3));
}

template <typename Cls, typename P1, typename P2, typename P3>
inline void BindImpl(void (Cls::*fun)(P1, P2, P3), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3));
}

//4
template <typename Return, typename P1, typename P2, typename P3, typename P4>
inline void BindImpl(Return (*fun)(P1, P2, P3, P4), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4));
}

template <typename Return, typename Cls, typename P1, typename P2, typename P3, typename P4>
inline void BindImpl(Return (Cls::*fun)(P1, P2, P3, P4), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4));
}

template <typename P1, typename P2, typename P3, typename P4>
inline void BindImpl(void (*fun)(P1, P2, P3, P4), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4));
}

template <typename Cls, typename P1, typename P2, typename P3, typename P4>
inline void BindImpl(void (Cls::*fun)(P1, P2, P3, P4), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4));
}
//5
template <typename Return, typename P1, typename P2, typename P3, typename P4, typename P5>
inline void BindImpl(Return (*fun)(P1, P2, P3, P4, P5), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5));
}

template <typename Return, typename Cls, typename P1, typename P2, typename P3, typename P4, typename P5>
inline void BindImpl(Return (Cls::*fun)(P1, P2, P3, P4, P5), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5));
}

template <typename P1, typename P2, typename P3, typename P4, typename P5>
inline void BindImpl(void (*fun)(P1, P2, P3, P4, P5), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5));
}

template <typename Cls, typename P1, typename P2, typename P3, typename P4, typename P5>
inline void BindImpl(void (Cls::*fun)(P1, P2, P3, P4, P5), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5));
}

//6
template <typename Return, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
inline void BindImpl(Return (*fun)(P1, P2, P3, P4, P5, P6), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5), FetchValue(6));
}

template <typename Return, typename Cls, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
inline void BindImpl(Return (Cls::*fun)(P1, P2, P3, P4, P5, P6), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5), FetchValue(6));
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
inline void BindImpl(void (*fun)(P1, P2, P3, P4, P5, P6), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5), FetchValue(6));
}

template <typename Cls, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
inline void BindImpl(void (Cls::*fun)(P1, P2, P3, P4, P5, P6), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5), FetchValue(6));
}

//7
template <typename Return, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
inline void BindImpl(Return (*fun)(P1, P2, P3, P4, P5, P6, P7), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7));
}

template <typename Return, typename Cls, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
inline void BindImpl(Return (Cls::*fun)(P1, P2, P3, P4, P5, P6, P7), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7));
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
inline void BindImpl(void (*fun)(P1, P2, P3, P4, P5, P6, P7), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7));
}

template <typename Cls, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
inline void BindImpl(void (Cls::*fun)(P1, P2, P3, P4, P5, P6, P7), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7));
}
//8
template <typename Return, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
inline void BindImpl(Return (*fun)(P1, P2, P3, P4, P5, P6, P7, P8), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8));
}

template <typename Return, typename Cls, typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8>
inline void BindImpl(Return (Cls::*fun)(P1, P2, P3, P4, P5, P6, P7, P8), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8));
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
inline void BindImpl(void (*fun)(P1, P2, P3, P4, P5, P6, P7, P8), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8));
}

template <typename Cls, typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8>
    inline void BindImpl(void (Cls::*fun)(P1, P2, P3, P4, P5, P6, P7, P8), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8));
}
//9
template <typename Return, typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
inline void BindImpl(Return (*fun)(P1, P2, P3, P4, P5, P6, P7, P8, P9), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8), FetchValue(9));
}

template <typename Return, typename Cls, typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
inline void BindImpl(Return (Cls::*fun)(P1, P2, P3, P4, P5, P6, P7, P8, P9), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8), FetchValue(9));
}

template <typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
    inline void BindImpl(void (*fun)(P1, P2, P3, P4, P5, P6, P7, P8, P9), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8), FetchValue(9));
}

template <typename Cls, typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
    inline void BindImpl(void (Cls::*fun)(P1, P2, P3, P4, P5, P6, P7, P8, P9), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8), FetchValue(9));
}

//10
template <typename Return, typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
inline void BindImpl(Return (*fun)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8), FetchValue(9), FetchValue(10));
}

template <typename Return, typename Cls, typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
inline void BindImpl(Return (Cls::*fun)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10), ParamList& param)
{
    FetchValue(0) = (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8), FetchValue(9), FetchValue(10));
}

template <typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
    inline void BindImpl(void (*fun)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8), FetchValue(9), FetchValue(10));
}

template <typename Cls, typename P1, typename P2, typename P3, 
    typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
    inline void BindImpl(void (Cls::*fun)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10), ParamList& param)
{
    (*fun)(FetchValue(1), FetchValue(2), FetchValue(3), 
        FetchValue(4), FetchValue(5), FetchValue(6), FetchValue(7), FetchValue(8), FetchValue(9), FetchValue(10));
}
//////////////////////////////////////////////////////////////////////////

/*
template <typename R>
class Work
{
    virtual void Run(ParamList& param)
    {

    }
};

template <typename R, typename T1>
class Work*/

#endif