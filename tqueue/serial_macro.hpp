#ifndef SERIAL_MACRO_H
#define SERIAL_MACRO_H

//////////////////////////////////////////////////////////////////////////
#include "ShareMemoryWrap.h"

#define FindST(st, x) (size_t)&(((st*)0)->x)
#define SizeST(st, x) sizeof(((st*)0)->x)
#define NEWREF(org,x) *(void*((unsigned long)org+(unsigned long)(&x)))

//////////////////////////////////////////////////////////////////////////
#define INTERFACE_CALL_BASE(cls) \
struct Inner_Call_Base \
{ \
	virtual void WriteBuff(cls& impl,const void* ptr) = 0; \
	virtual void ReadBuff(cls& impl,void* ptr) = 0; \
};

template <typename _TyImpl>
struct Inner_Call_BaseT
{
	virtual size_t GetReadSize(_TyImpl& impl) = 0;
    virtual size_t GetWriteSize(_TyImpl& impl,const void* ptr) = 0;
	virtual void WriteBuff(_TyImpl& impl,const void* ptr) = 0;
	virtual void ReadBuff(_TyImpl& impl,void* ptr) = 0;
};

#define DECLARE_INNER_CALL(Impl) \
template < typename T> \
struct Inner_Call : public Inner_Call_BaseT<Impl> \
{ \
explicit Inner_Call(T& tuple):inner_tuple_(tuple) {}; \
virtual size_t GetReadSize(Impl& impl) \
{ return ParamTraits<Impl, T>::GetReadSize(impl); } \
virtual size_t GetWriteSize(Impl& impl,const void* ptr) \
{ return ParamTraits<Impl, T>::GetWriteSize(impl,inner_tuple_, ptr); } \
virtual void WriteBuff(Impl& impl,const void* ptr) \
{ ParamTraits<Impl, T>::write_ptr(impl,inner_tuple_, ptr);} \
virtual void ReadBuff(Impl& impl,void* ptr) \
{ ParamTraits<Impl,T>::read_ptr(impl,inner_tuple_, ptr); } \
private: \
T inner_tuple_; \
std::vector<size_t> offset_vec_; \
};

//DECLARE_INNER_CALL(MemoryRead);
DECLARE_INNER_CALL(ShareMemoryWrap);

template < typename T>
inline Inner_Call<T>* Make_Inner_Call(T& t)
{
	return new Inner_Call<T>(t);
}

#define METHOD_PROLOGUE_INNER(theClass, localClass) \
	theClass* pThis = \
	((theClass*)((unsigned char*)this - FindST(theClass, inn_))); \
	pThis;

#define DECLARE_INNER_ORG(cls, IMPL) \
static size_t GetReadSize(IMPL& impl) \
{ return cls::inn_.inner_call_->GetReadSize(impl); }\
	static size_t GetWriteSize(IMPL& impl,const cls* pThis) \
{ return cls::inn_.inner_call_->GetWriteSize(impl, pThis);} \
	static void WriteBuff(IMPL& impl,const cls* pThis)\
{\
	cls::inn_.inner_call_->WriteBuff(impl,pThis);\
}\
	static void ReadBuff(IMPL& impl,cls* pThis)\
{\
	cls::inn_.inner_call_->ReadBuff(impl,pThis);\
}\
struct Inner{ \
	Inner():inner_call_(NULL) \
{\
	METHOD_PROLOGUE_INNER(cls,Inner);

#define DECLARE_INNER_ST(cls) DECLARE_INNER_ORG(cls, ShareMemoryWrap)

#define SERIAL_1(P1) \
auto tuple = MakeTuple(pThis->P1);

#define SERIAL_2(P1,P2) \
auto tuple = MakeTuple(pThis->P1,pThis->P2);

#define SERIAL_3(P1,P2,P3) \
auto tuple = MakeTuple(pThis->P1,pThis->P2,pThis->P3);

#define SERIAL_4(P1,P2,P3,P4) \
auto tuple = MakeTuple(pThis->P1,pThis->P2,pThis->P3,pThis->P4);

#define SERIAL_5(P1,P2,P3,P4,P5) \
auto tuple = MakeTuple(pThis->P1,pThis->P2,pThis->P3,pThis->P4,pThis->P5);

#define SERIAL_6(P1,P2,P3,P4,P5,P6) \
auto tuple = MakeTuple(pThis->P1,pThis->P2,pThis->P3,pThis->P4,pThis->P5,pThis->P6);

#define SERIAL_7(P1,P2,P3,P4,P5,P6,P7) \
auto tuple = MakeTuple(pThis->P1,pThis->P2,pThis->P3,pThis->P4,pThis->P5,pThis->P6,pThis->P7);

#define SERIAL_8(P1,P2,P3,P4,P5,P6,P7,P8) \
auto tuple = MakeTuple(pThis->P1,pThis->P2,pThis->P3,pThis->P4,pThis->P5,pThis->P6,pThis->P7,pThis->P8);

#define SERIAL_9(P1,P2,P3,P4,P5,P6,P7,P8,P9) \
auto tuple = MakeTuple(pThis->P1,pThis->P2,pThis->P3,pThis->P4,pThis->P5,pThis->P6,pThis->P7,pThis->P8,pThis->P9);

#define SERIAL_10(P1,P2,P3,P4,P5,P6,P7,P8,P9,P10) \
auto tuple = MakeTuple(pThis->P1,pThis->P2,pThis->P3,pThis->P4,pThis->P5,pThis->P6,pThis->P7,pThis->P8,pThis->P9,pThis->P10);

#define END_INNER_ST \
inner_call_ = Make_Inner_Call(tuple);\
}\
~Inner()\
{\
delete inner_call_;\
}\
Inner_Call_BaseT<ShareMemoryWrap>* inner_call_;\
};\
public:\
static Inner inn_;

#define DECLARE_SERIAL_1(cls,P1) DECLARE_INNER_ST(cls) SERIAL_1(P1) END_INNER_ST
#define DECLARE_SERIAL_2(cls,P1,P2) DECLARE_INNER_ST(cls) SERIAL_2(P1,P2) END_INNER_ST
#define DECLARE_SERIAL_3(cls,P1,P2,P3) DECLARE_INNER_ST(cls) SERIAL_3(P1,P2,P3) END_INNER_ST
#define DECLARE_SERIAL_4(cls,P1,P2,P3,P4) DECLARE_INNER_ST(cls) SERIAL_4(P1,P2,P3,P4) END_INNER_ST
#define DECLARE_SERIAL_5(cls,P1,P2,P3,P4,P5) DECLARE_INNER_ST(cls) SERIAL_5(P1,P2,P3,P4,P5) END_INNER_ST
#define DECLARE_SERIAL_6(cls,P1,P2,P3,P4,P5,P6) DECLARE_INNER_ST(cls) SERIAL_6(P1,P2,P3,P4,P5,P6) END_INNER_ST
#define DECLARE_SERIAL_7(cls,P1,P2,P3,P4,P5,P6,P7) DECLARE_INNER_ST(cls) SERIAL_7(P1,P2,P3,P4,P5,P6,P7) END_INNER_ST
#define DECLARE_SERIAL_8(cls,P1,P2,P3,P4,P5,P6,P7,P8) DECLARE_INNER_ST(cls) SERIAL_8(P1,P2,P3,P4,P5,P6,P7,P8) END_INNER_ST
#define DECLARE_SERIAL_9(cls,P1,P2,P3,P4,P5,P6,P7,P8,P9) DECLARE_INNER_ST(cls) SERIAL_8(P1,P2,P3,P4,P5,P6,P7,P8,P9) END_INNER_ST
#define DECLARE_SERIAL_10(cls,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10) DECLARE_INNER_ST(cls) SERIAL_8(P1,P2,P3,P4,P5,P6,P7,P8,P9,P10) END_INNER_ST

#define BEGIN_SERIAL(cls) struct  cls {
#define END_SERIAL(cls) }; cls::Inner cls::inn_;

#endif