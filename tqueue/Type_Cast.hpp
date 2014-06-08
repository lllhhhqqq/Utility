/** 
 * @file TypeCast.hpp
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 16/4/2013
 *
 * 详细说明   
 */
#ifndef TYPE_CAST_HPP_V1_0
#define TYPE_CAST_HPP_V1_0

template <typename P>
struct SimilarTypeTraits {
    typedef P Type;
};

template <typename T>
struct RefType
{
    typedef T realtype;
    typedef T& reftype;
    typedef const T& const_reftype;

    enum
    {
        size = sizeof(T),
    };
};

template <typename T>

struct RefType<T&>
{
    typedef typename RefType<T>::realtype realtype;
    typedef typename RefType<T>::reftype reftype;
    typedef typename RefType<T>::const_reftype const_reftype;

    enum
    {
        size = RefType<T>::size,
    };
};

template <typename T>
struct RefType<const T&>
{
    typedef typename RefType<T>::realtype realtype;
    typedef typename RefType<T>::reftype reftype;
    typedef typename RefType<T>::const_reftype const_reftype;

    enum
    {
        size = RefType<T>::size,
    };
};

template <typename T>
struct RefType<T*>
{
    typedef T* realtype;
    typedef T* reftype;
    typedef const T* const_reftype;

    enum
    {
        size = sizeof(T*),
    };
};

template <typename T>
struct RefType<const T*>
{
    typedef const T* realtype;
    typedef T* reftype;
    typedef const T* const_reftype;

    enum
    {
        size = sizeof(T*),
    };
};

template <typename T>
struct RefType<T[]>
{
    typedef T* realtype;
    typedef T* reftype;
    typedef const T* const_reftype;

    enum
    {
        size = sizeof(T*),
    };
};

template <typename T,int N>
struct RefType< T[N] >
{
    typedef T* realtype;
    typedef T* reftype;
    typedef const T* const_reftype;

    enum
    {
        size = N*sizeof(T),
    };
};

template <typename T,int N>
struct RefType<const T[N]>
{
    typedef T* realtype;
    typedef T* reftype;
    typedef const T* const_reftype;

    enum
    {
        size = N*sizeof(T),
    };
};

//////////////////////////////////////////////////////////////////////////
//Tuple template
class Tuple0;

#define ARG_TYPE(x) reftype#x
#define DEFINE_ARG_TYPE(type_,x) typedef typename RefType<type_>::const_reftype x;

template <typename T1>
class Tuple1
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    enum
    {
        size1 = RefType<T1>::size,
    };


    explicit Tuple1(reftype1 ref1)
        :ref1_(ref1)
    {}

    reftype1 ref1_;
};

template <typename T1,typename T2>
class Tuple2
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    DEFINE_ARG_TYPE(T2,reftype2)
    enum
    {
        size1 = RefType<T1>::size,
        size2 = RefType<T2>::size,
    };


    explicit Tuple2(reftype1 ref1,reftype2 ref2)
        :ref1_(ref1)
        ,ref2_(ref2)
    {}

    reftype1 ref1_;
    reftype2 ref2_;
};

template <typename T1,typename T2,typename T3>
class Tuple3
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    DEFINE_ARG_TYPE(T2,reftype2)
    DEFINE_ARG_TYPE(T3,reftype3)
    enum
    {
        size1 = RefType<T1>::size,
        size2 = RefType<T2>::size,
        size3 = RefType<T3>::size,
    };


    explicit Tuple3(reftype1 ref1,reftype2 ref2,reftype3 ref3)
        :ref1_(ref1)
        ,ref2_(ref2)
        ,ref3_(ref3)
    {}

    reftype1 ref1_;
    reftype2 ref2_;
    reftype3 ref3_;
};

template <typename T1,typename T2,typename T3,typename T4>
class Tuple4
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    DEFINE_ARG_TYPE(T2,reftype2)
    DEFINE_ARG_TYPE(T3,reftype3)
    DEFINE_ARG_TYPE(T4,reftype4)
    enum
    {
        size1 = RefType<T1>::size,
        size2 = RefType<T2>::size,
        size3 = RefType<T3>::size,
        size4 = RefType<T4>::size,
    };


    explicit Tuple4(reftype1 ref1,reftype2 ref2,reftype3 ref3,reftype4 ref4)
        :ref1_(ref1)
        ,ref2_(ref2)
        ,ref3_(ref3)
        ,ref4_(ref4)
    {}

    reftype1 ref1_;
    reftype2 ref2_;
    reftype3 ref3_;
    reftype4 ref4_;
};
template <typename T1,typename T2,typename T3,typename T4,typename T5>
class Tuple5
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    DEFINE_ARG_TYPE(T2,reftype2)
    DEFINE_ARG_TYPE(T3,reftype3)
    DEFINE_ARG_TYPE(T4,reftype4)
    DEFINE_ARG_TYPE(T5,reftype5)
    enum
    {
        size1 = RefType<T1>::size,
        size2 = RefType<T2>::size,
        size3 = RefType<T3>::size,
        size4 = RefType<T4>::size,
        size5 = RefType<T5>::size,
    };


    explicit Tuple5(reftype1 ref1,reftype2 ref2,reftype3 ref3,reftype4 ref4,reftype5 ref5)
        :ref1_(ref1)
        ,ref2_(ref2)
        ,ref3_(ref3)
        ,ref4_(ref4)
        ,ref5_(ref5)
    {}

    reftype1 ref1_;
    reftype2 ref2_;
    reftype3 ref3_;
    reftype4 ref4_;
    reftype5 ref5_;
};
template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
class Tuple6
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    DEFINE_ARG_TYPE(T2,reftype2)
    DEFINE_ARG_TYPE(T3,reftype3)
    DEFINE_ARG_TYPE(T4,reftype4)
    DEFINE_ARG_TYPE(T5,reftype5)
    DEFINE_ARG_TYPE(T6,reftype6)
    enum
    {
        size1 = RefType<T1>::size,
        size2 = RefType<T2>::size,
        size3 = RefType<T3>::size,
        size4 = RefType<T4>::size,
        size5 = RefType<T5>::size,
        size6 = RefType<T6>::size,
    };


    explicit Tuple6(reftype1 ref1,reftype2 ref2,reftype3 ref3,reftype4 ref4,reftype5 ref5,reftype6 ref6)
        :ref1_(ref1)
        ,ref2_(ref2)
        ,ref3_(ref3)
        ,ref4_(ref4)
        ,ref5_(ref5)
        ,ref6_(ref6)
    {}

    reftype1 ref1_;
    reftype2 ref2_;
    reftype3 ref3_;
    reftype4 ref4_;
    reftype5 ref5_;
    reftype6 ref6_;
};
template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
class Tuple7
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    DEFINE_ARG_TYPE(T2,reftype2)
    DEFINE_ARG_TYPE(T3,reftype3)
    DEFINE_ARG_TYPE(T4,reftype4)
    DEFINE_ARG_TYPE(T5,reftype5)
    DEFINE_ARG_TYPE(T6,reftype6)
    DEFINE_ARG_TYPE(T7,reftype7)
    enum
    {
        size1 = RefType<T1>::size,
        size2 = RefType<T2>::size,
        size3 = RefType<T3>::size,
        size4 = RefType<T4>::size,
        size5 = RefType<T5>::size,
        size6 = RefType<T6>::size,
        size7 = RefType<T7>::size,
    };


    explicit Tuple7(reftype1 ref1,reftype2 ref2,reftype3 ref3,reftype4 ref4,reftype5 ref5,reftype6 ref6,reftype7 ref7)
        :ref1_(ref1)
        ,ref2_(ref2)
        ,ref3_(ref3)
        ,ref4_(ref4)
        ,ref5_(ref5)
        ,ref6_(ref6)
        ,ref7_(ref7)
    {}

    reftype1 ref1_;
    reftype2 ref2_;
    reftype3 ref3_;
    reftype4 ref4_;
    reftype5 ref5_;
    reftype6 ref6_;
    reftype7 ref7_;
};
template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
class Tuple8
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    DEFINE_ARG_TYPE(T2,reftype2)
    DEFINE_ARG_TYPE(T3,reftype3)
    DEFINE_ARG_TYPE(T4,reftype4)
    DEFINE_ARG_TYPE(T5,reftype5)
    DEFINE_ARG_TYPE(T6,reftype6)
    DEFINE_ARG_TYPE(T7,reftype7)
    DEFINE_ARG_TYPE(T8,reftype8)
    enum
    {
        size1 = RefType<T1>::size,
        size2 = RefType<T2>::size,
        size3 = RefType<T3>::size,
        size4 = RefType<T4>::size,
        size5 = RefType<T5>::size,
        size6 = RefType<T6>::size,
        size7 = RefType<T7>::size,
        size8 = RefType<T8>::size,
    };


    explicit Tuple8(reftype1 ref1,reftype2 ref2,reftype3 ref3,reftype4 ref4,reftype5 ref5,reftype6 ref6,reftype7 ref7,reftype8 ref8)
        :ref1_(ref1)
        ,ref2_(ref2)
        ,ref3_(ref3)
        ,ref4_(ref4)
        ,ref5_(ref5)
        ,ref6_(ref6)
        ,ref7_(ref7)
        ,ref8_(ref8)
    {}

    reftype1 ref1_;
    reftype2 ref2_;
    reftype3 ref3_;
    reftype4 ref4_;
    reftype5 ref5_;
    reftype6 ref6_;
    reftype7 ref7_;
    reftype8 ref8_;
};
template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
class Tuple9
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    DEFINE_ARG_TYPE(T2,reftype2)
    DEFINE_ARG_TYPE(T3,reftype3)
    DEFINE_ARG_TYPE(T4,reftype4)
    DEFINE_ARG_TYPE(T5,reftype5)
    DEFINE_ARG_TYPE(T6,reftype6)
    DEFINE_ARG_TYPE(T7,reftype7)
    DEFINE_ARG_TYPE(T8,reftype8)
    DEFINE_ARG_TYPE(T9,reftype9)
    enum
    {
        size1 = RefType<T1>::size,
        size2 = RefType<T2>::size,
        size3 = RefType<T3>::size,
        size4 = RefType<T4>::size,
        size5 = RefType<T5>::size,
        size6 = RefType<T6>::size,
        size7 = RefType<T7>::size,
        size8 = RefType<T8>::size,
        size9 = RefType<T9>::size,
    };


    explicit Tuple9(reftype1 ref1,reftype2 ref2,reftype3 ref3,reftype4 ref4,reftype5 ref5,reftype6 ref6,reftype7 ref7,reftype8 ref8,reftype9 ref9)
        :ref1_(ref1)
        ,ref2_(ref2)
        ,ref3_(ref3)
        ,ref4_(ref4)
        ,ref5_(ref5)
        ,ref6_(ref6)
        ,ref7_(ref7)
        ,ref8_(ref8)
        ,ref9_(ref9)
    {}

    reftype1 ref1_;
    reftype2 ref2_;
    reftype3 ref3_;
    reftype4 ref4_;
    reftype5 ref5_;
    reftype6 ref6_;
    reftype7 ref7_;
    reftype8 ref8_;
    reftype9 ref9_;
};
template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
class Tuple10
{
public:
    DEFINE_ARG_TYPE(T1,reftype1)
    DEFINE_ARG_TYPE(T2,reftype2)
    DEFINE_ARG_TYPE(T3,reftype3)
    DEFINE_ARG_TYPE(T4,reftype4)
    DEFINE_ARG_TYPE(T5,reftype5)
    DEFINE_ARG_TYPE(T6,reftype6)
    DEFINE_ARG_TYPE(T7,reftype7)
    DEFINE_ARG_TYPE(T8,reftype8)
    DEFINE_ARG_TYPE(T9,reftype9)
    DEFINE_ARG_TYPE(T10,reftype10)
    enum
    {
        size1 = RefType<T1>::size,
        size2 = RefType<T2>::size,
        size3 = RefType<T3>::size,
        size4 = RefType<T4>::size,
        size5 = RefType<T5>::size,
        size6 = RefType<T6>::size,
        size7 = RefType<T7>::size,
        size8 = RefType<T8>::size,
        size9 = RefType<T9>::size,
        size10 = RefType<T10>::size,
    };


    explicit Tuple10(reftype1 ref1,reftype2 ref2,reftype3 ref3,reftype4 ref4,reftype5 ref5,reftype6 ref6,reftype7 ref7,reftype8 ref8,reftype9 ref9,reftype10 ref10)
        :ref1_(ref1)
        ,ref2_(ref2)
        ,ref3_(ref3)
        ,ref4_(ref4)
        ,ref5_(ref5)
        ,ref6_(ref6)
        ,ref7_(ref7)
        ,ref8_(ref8)
        ,ref9_(ref9)
        ,ref10_(ref10)
    {}

    reftype1 ref1_;
    reftype2 ref2_;
    reftype3 ref3_;
    reftype4 ref4_;
    reftype5 ref5_;
    reftype6 ref6_;
    reftype7 ref7_;
    reftype8 ref8_;
    reftype9 ref9_;
    reftype10 ref10_;
};

template <typename T1>
inline Tuple1<T1> MakeTuple(const T1& p1)
{
    return Tuple1<T1>(p1);
}

template <typename T1,typename T2>
inline Tuple2<T1,T2> MakeTuple(const T1& p1,const T2& p2)
{
    return Tuple2<T1,T2>(p1,p2);
}

template <typename T1,typename T2,typename T3>
inline Tuple3<T1,T2,T3> MakeTuple(const T1& p1,const T2& p2,const T3& p3)
{
    return Tuple3<T1,T2,T3>(p1,p2,p3);
}

template <typename T1,typename T2,typename T3,typename T4>
inline Tuple4<T1,T2,T3,T4> MakeTuple(const T1& p1,const T2& p2,const T3& p3,const T4& p4)
{
    return Tuple4<T1,T2,T3,T4>(p1,p2,p3,p4);
}

template <typename T1,typename T2,typename T3,typename T4,typename T5>
inline Tuple5<T1,T2,T3,T4,T5> MakeTuple(const T1& p1,const T2& p2,const T3& p3,const T4& p4,const T5& p5)
{
    return Tuple5<T1,T2,T3,T4,T5>(p1,p2,p3,p4,p5);
}

template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
inline Tuple6<T1,T2,T3,T4,T5,T6> MakeTuple(const T1& p1,const T2& p2,const T3& p3,const T4& p4,const T5& p5,const T6& p6)
{
    return Tuple6<T1,T2,T3,T4,T5,T6>(p1,p2,p3,p4,p5,p6);
}

template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
inline Tuple7<T1,T2,T3,T4,T5,T6,T7> MakeTuple(const T1& p1,const T2& p2,const T3& p3,const T4& p4,const T5& p5,const T6& p6,const T7& p7)
{
    return Tuple7<T1,T2,T3,T4,T5,T6,T7>(p1,p2,p3,p4,p5,p6,p7);
}

template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
inline Tuple8<T1,T2,T3,T4,T5,T6,T7,T8> MakeTuple(const T1& p1,const T2& p2,const T3& p3,const T4& p4,const T5& p5,const T6& p6,const T7& p7,const T8& p8)
{
    return Tuple8<T1,T2,T3,T4,T5,T6,T7,T8>(p1,p2,p3,p4,p5,p6,p7,p8);
}

template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
inline Tuple9<T1,T2,T3,T4,T5,T6,T7,T8,T9> MakeTuple(const T1& p1,const T2& p2,const T3& p3,const T4& p4,const T5& p5,const T6& p6,const T7& p7,const T8& p8,const T9& p9)
{
    return Tuple9<T1,T2,T3,T4,T5,T6,T7,T8,T9>(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}

template <typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
inline Tuple10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> MakeTuple(const T1& p1,const T2& p2,const T3& p3,const T4& p4,const T5& p5,const T6& p6,const T7& p7,const T8& p8,const T9& p9,const T10& p10)
{
    return Tuple10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10>(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10);
}

#endif // !TYPE_CAST_V1_0
