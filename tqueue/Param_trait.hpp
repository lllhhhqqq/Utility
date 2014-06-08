#ifndef PARAMTRAITS_H
#define PARAMTRAITS_H

//#include "ShareMemoryWrap.h"

template <typename T>
class OffSetPtr
{
public:
	typedef typename RefType<T>::reftype reftype;
	typedef typename RefType<T>::const_reftype const_reftype;

	inline static reftype GetPtr(const void* ptr_org,const_reftype refval)
	{
		return (reftype)(*((unsigned char*)ptr_org+reinterpret_cast<unsigned long>(&const_cast<reftype>(refval))));
	}

	inline static reftype GetPtr(const void* ptr_org,reftype refval)
	{
		return (reftype)(*((unsigned char*)ptr_org+reinterpret_cast<unsigned long>(&refval)));
	}
};

template <typename T>
class OffSetPtr<T*>
{
public:
	typedef typename RefType<T*>::reftype reftype;
	typedef typename RefType<T*>::const_reftype const_reftype;

	inline static reftype GetPtr(const void* ptr_org,T* refval)
	{
		return (reftype)((unsigned char*)ptr_org+reinterpret_cast<unsigned long>(refval));
	}

	inline static reftype GetPtr(const void* ptr_org,const T* refval)
	{
		return (reftype)((unsigned char*)ptr_org+reinterpret_cast<unsigned long>(refval));
	}
}; 

//////////////////////////////////////////////////////////////////////////
//GetSize模板
template <typename T>
class GetSize
{
public:
	typedef typename RefType<T>::reftype reftype;
	typedef typename RefType<T>::const_reftype const_reftype;

	inline static size_t Size(const_reftype ref)
	{
		return sizeof(ref) + sizeof(size_t);
	}
};

template <typename T, int N>
class GetSize<T[N]>
{
public:
    typedef typename RefType<T[N]>::reftype reftype;
    typedef typename RefType<T[N]>::const_reftype const_reftype;

    inline static size_t Size(const_reftype ref)
    {
        return RefType<T[N]>::size + sizeof(size_t);
    }
};

template <typename T>
class GetSize<T*>
{
public:
	typedef typename RefType<T*>::reftype reftype;
	typedef typename RefType<T*>::const_reftype const_reftype;

	inline static size_t Size(T* ref)
	{
		return sizeof(ref) + sizeof(size_t);
	}
};

template <>
class GetSize<const char*>
{
	inline static size_t Size(const char* ref)
	{
		return strlen(ref) + sizeof(size_t);
	}
};

template <>
class GetSize<std::string&>
{
public:
	inline static size_t Size(std::string& ref)
	{
		return ref.length() + sizeof(size_t);
	}
};

template <>
class GetSize<const std::string&>
{
public:
	inline static size_t Size(const std::string& ref)
	{
		return ref.length();
	}
};

template <typename T>
class GetSize< std::list<T> >
{
public:
inline static size_t Size(std::list<T>& ref)
{
    T ref_sub;
    return ref.size() * GetSize<T>::Size(ref_sub);
}
};

template <typename T>
class GetSize< std::vector<T> >
{
public:
    inline static size_t Size(std::list<T>& ref)
    {
        T ref_sub;
        return ref.size() * GetSize<T>::Size(ref_sub);
    }
};

#define WRITE_PREDEF \
size_t write_offset = GetWriteSize(impl, p, ptr); \
impl.RequestWrite(write_offset); \
DataProxy<reftype1, _TyImpl>::write_head(impl,write_offset);

#define READ_PREDEF \
impl.InitRead(); \
size_t read_offset = DataProxy<reftype1, _TyImpl>::read_head(impl); \
impl.RequestRead(read_offset);

//To do _Tyimpl 改成 _TyImplIn 和 _TyImplOut 两个模板参数
template <typename _TyImpl, typename T1>
struct ParamTraits
{
    static size_t GetWriteSize(_TyImpl& impl,const T1 &p)
    {
        return T1::GetWriteSize(impl, &p);
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return T1::GetReadSize(impl);
	}

	static inline void write(_TyImpl& impl,const T1 &p)
	{
		T1::WriteBuff(impl,&p);
	}

	static inline void read(_TyImpl& impl,T1 &p)
	{
		T1::ReadBuff(impl,&p);
	}

	static inline void write_ptr(_TyImpl& impl,const T1 &p,const void* offset)
	{
		T1::write_ptr(impl,&p,offset);
	}

	static inline void read_ptr(_TyImpl& impl,T1 &p,void* offset)
	{
		T1::read_ptr(impl,&p,offset);
	}
};

template <typename _TyImpl, typename T1>
struct ParamTraits< _TyImpl, Tuple1<T1> >
{
	typedef Tuple1<T1> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);

        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);

        //WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);

        //READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
	}

};

template <typename _TyImpl, typename T1, typename T2>
struct ParamTraits< _TyImpl, Tuple2<T1,T2> >
{
	typedef Tuple2<T1,T2> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;
	typedef typename RefType<typename param_type::reftype2>::reftype reftype2;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
        reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
        
        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        write_offset += GetSize<reftype2>::Size(ref2);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, p.ref2_,  param_type::size2);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(p.ref2_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);

        //WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, ref2,  param_type::size2);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);

        //READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(ref2));
	}

};

template <typename _TyImpl, typename T1, typename T2, typename T3>
struct ParamTraits< _TyImpl, Tuple3<T1,T2,T3> >
{
	typedef Tuple3<T1,T2,T3> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;
	typedef typename RefType<typename param_type::reftype2>::reftype reftype2;
	typedef typename RefType<typename param_type::reftype3>::reftype reftype3;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
        reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
        reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);

        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        write_offset += GetSize<reftype2>::Size(ref2);
        write_offset += GetSize<reftype3>::Size(ref3);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, p.ref2_,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, p.ref3_,  param_type::size3);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(p.ref2_));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(p.ref3_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);

		//WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, ref2,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, ref3,  param_type::size3);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);

		//READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(ref2));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(ref3));
	}

};

template <typename _TyImpl, typename T1, typename T2, typename T3, typename T4>
struct ParamTraits< _TyImpl, Tuple4<T1,T2,T3,T4> >
{
	typedef Tuple4<T1,T2,T3,T4> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;
	typedef typename RefType<typename param_type::reftype2>::reftype reftype2;
	typedef typename RefType<typename param_type::reftype3>::reftype reftype3;
	typedef typename RefType<typename param_type::reftype4>::reftype reftype4;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
        reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
        reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
        reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);

        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        write_offset += GetSize<reftype2>::Size(ref2);
        write_offset += GetSize<reftype3>::Size(ref3);
        write_offset += GetSize<reftype4>::Size(ref4);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, p.ref2_,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, p.ref3_,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, p.ref4_,  param_type::size4);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(p.ref2_));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(p.ref3_));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(p.ref4_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);

        //WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, ref2,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, ref3,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, ref4,  param_type::size4);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);

        //READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(ref2));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(ref3));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(ref4));
	}

};

template <typename _TyImpl, typename T1, typename T2, typename T3, typename T4, typename T5>
struct ParamTraits< _TyImpl, Tuple5<T1,T2,T3,T4,T5> >
{
	typedef Tuple5<T1,T2,T3,T4,T5> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;
	typedef typename RefType<typename param_type::reftype2>::reftype reftype2;
	typedef typename RefType<typename param_type::reftype3>::reftype reftype3;
	typedef typename RefType<typename param_type::reftype4>::reftype reftype4;
	typedef typename RefType<typename param_type::reftype5>::reftype reftype5;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
        reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
        reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
        reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
        reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);

        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        write_offset += GetSize<reftype2>::Size(ref2);
        write_offset += GetSize<reftype3>::Size(ref3);
        write_offset += GetSize<reftype4>::Size(ref4);
        write_offset += GetSize<reftype5>::Size(ref5);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, p.ref2_,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, p.ref3_,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, p.ref4_,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, p.ref5_,  param_type::size5);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(p.ref2_));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(p.ref3_));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(p.ref4_));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(p.ref5_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);

        //WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, ref2,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, ref3,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, ref4,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, ref5,  param_type::size5);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);

        //READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(ref2));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(ref3));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(ref4));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(ref5));
	}

};

template <typename _TyImpl, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct ParamTraits< _TyImpl, Tuple6<T1,T2,T3,T4,T5,T6> >
{
	typedef Tuple6<T1,T2,T3,T4,T5,T6> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;
	typedef typename RefType<typename param_type::reftype2>::reftype reftype2;
	typedef typename RefType<typename param_type::reftype3>::reftype reftype3;
	typedef typename RefType<typename param_type::reftype4>::reftype reftype4;
	typedef typename RefType<typename param_type::reftype5>::reftype reftype5;
	typedef typename RefType<typename param_type::reftype6>::reftype reftype6;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
        reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
        reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
        reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
        reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
        reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);

        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        write_offset += GetSize<reftype2>::Size(ref2);
        write_offset += GetSize<reftype3>::Size(ref3);
        write_offset += GetSize<reftype3>::Size(ref4);
        write_offset += GetSize<reftype3>::Size(ref5);
        write_offset += GetSize<reftype3>::Size(ref6);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, p.ref2_,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, p.ref3_,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, p.ref4_,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, p.ref5_,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, p.ref6_,  param_type::size6);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(p.ref2_));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(p.ref3_));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(p.ref4_));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(p.ref5_));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(p.ref6_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);

        //WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, ref2,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, ref3,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, ref4,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, ref5,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, ref6,  param_type::size6);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);

        //READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(ref2));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(ref3));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(ref4));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(ref5));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(ref6));
	}

};

template <typename _TyImpl, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct ParamTraits< _TyImpl, Tuple7<T1,T2,T3,T4,T5,T6,T7> >
{
	typedef Tuple7<T1,T2,T3,T4,T5,T6,T7> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;
	typedef typename RefType<typename param_type::reftype2>::reftype reftype2;
	typedef typename RefType<typename param_type::reftype3>::reftype reftype3;
	typedef typename RefType<typename param_type::reftype4>::reftype reftype4;
	typedef typename RefType<typename param_type::reftype5>::reftype reftype5;
	typedef typename RefType<typename param_type::reftype6>::reftype reftype6;
	typedef typename RefType<typename param_type::reftype7>::reftype reftype7;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
        reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
        reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
        reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
        reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
        reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
        reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);

        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        write_offset += GetSize<reftype2>::Size(ref2);
        write_offset += GetSize<reftype3>::Size(ref3);
        write_offset += GetSize<reftype3>::Size(ref4);
        write_offset += GetSize<reftype3>::Size(ref5);
        write_offset += GetSize<reftype3>::Size(ref6);
        write_offset += GetSize<reftype3>::Size(ref7);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, p.ref2_,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, p.ref3_,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, p.ref4_,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, p.ref5_,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, p.ref6_,  param_type::size6);
		DataProxy<reftype7, _TyImpl>::write(impl, p.ref7_,  param_type::size7);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(p.ref2_));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(p.ref3_));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(p.ref4_));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(p.ref5_));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(p.ref6_));
		DataProxy<reftype7, _TyImpl>::read(impl, const_cast<reftype7>(p.ref7_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
		reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);

        //WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, ref2,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, ref3,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, ref4,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, ref5,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, ref6,  param_type::size6);
		DataProxy<reftype7, _TyImpl>::write(impl, ref7,  param_type::size7);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
		reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);

        //READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(ref2));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(ref3));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(ref4));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(ref5));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(ref6));
		DataProxy<reftype7, _TyImpl>::read(impl, const_cast<reftype7>(ref7));
	}

};

template <typename _TyImpl, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct ParamTraits< _TyImpl, Tuple8<T1,T2,T3,T4,T5,T6,T7,T8> >
{
	typedef Tuple8<T1,T2,T3,T4,T5,T6,T7,T8> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;
	typedef typename RefType<typename param_type::reftype2>::reftype reftype2;
	typedef typename RefType<typename param_type::reftype3>::reftype reftype3;
	typedef typename RefType<typename param_type::reftype4>::reftype reftype4;
	typedef typename RefType<typename param_type::reftype5>::reftype reftype5;
	typedef typename RefType<typename param_type::reftype6>::reftype reftype6;
	typedef typename RefType<typename param_type::reftype7>::reftype reftype7;
	typedef typename RefType<typename param_type::reftype8>::reftype reftype8;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
        reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
        reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
        reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
        reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
        reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
        reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);
        reftype8 ref8 = OffSetPtr<reftype8>::GetPtr(ptr, p.ref8_);

        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        write_offset += GetSize<reftype2>::Size(ref2);
        write_offset += GetSize<reftype3>::Size(ref3);
        write_offset += GetSize<reftype3>::Size(ref4);
        write_offset += GetSize<reftype3>::Size(ref5);
        write_offset += GetSize<reftype3>::Size(ref6);
        write_offset += GetSize<reftype3>::Size(ref7);
        write_offset += GetSize<reftype3>::Size(ref8);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, p.ref2_,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, p.ref3_,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, p.ref4_,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, p.ref5_,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, p.ref6_,  param_type::size6);
		DataProxy<reftype7, _TyImpl>::write(impl, p.ref7_,  param_type::size7);
		DataProxy<reftype8, _TyImpl>::write(impl, p.ref8_,  param_type::size8);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(p.ref2_));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(p.ref3_));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(p.ref4_));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(p.ref5_));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(p.ref6_));
		DataProxy<reftype7, _TyImpl>::read(impl, const_cast<reftype7>(p.ref7_));
		DataProxy<reftype8, _TyImpl>::read(impl, const_cast<reftype8>(p.ref8_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
		reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);
		reftype8 ref8 = OffSetPtr<reftype8>::GetPtr(ptr, p.ref8_);

        //WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, ref2,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, ref3,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, ref4,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, ref5,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, ref6,  param_type::size6);
		DataProxy<reftype7, _TyImpl>::write(impl, ref7,  param_type::size7);
		DataProxy<reftype8, _TyImpl>::write(impl, ref8,  param_type::size8);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
		reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);
		reftype8 ref8 = OffSetPtr<reftype8>::GetPtr(ptr, p.ref8_);

        //READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(ref2));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(ref3));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(ref4));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(ref5));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(ref6));
		DataProxy<reftype7, _TyImpl>::read(impl, const_cast<reftype7>(ref7));
		DataProxy<reftype8, _TyImpl>::read(impl, const_cast<reftype8>(ref8));
	}

};

template <typename _TyImpl, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ParamTraits< _TyImpl, Tuple9<T1,T2,T3,T4,T5,T6,T7,T8,T9> >
{
	typedef Tuple9<T1,T2,T3,T4,T5,T6,T7,T8,T9> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;
	typedef typename RefType<typename param_type::reftype2>::reftype reftype2;
	typedef typename RefType<typename param_type::reftype3>::reftype reftype3;
	typedef typename RefType<typename param_type::reftype4>::reftype reftype4;
	typedef typename RefType<typename param_type::reftype5>::reftype reftype5;
	typedef typename RefType<typename param_type::reftype6>::reftype reftype6;
	typedef typename RefType<typename param_type::reftype7>::reftype reftype7;
	typedef typename RefType<typename param_type::reftype8>::reftype reftype8;
	typedef typename RefType<typename param_type::reftype9>::reftype reftype9;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
        reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
        reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
        reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
        reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
        reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
        reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);
        reftype8 ref8 = OffSetPtr<reftype8>::GetPtr(ptr, p.ref8_);
        reftype9 ref9 = OffSetPtr<reftype9>::GetPtr(ptr, p.ref9_);

        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        write_offset += GetSize<reftype2>::Size(ref2);
        write_offset += GetSize<reftype3>::Size(ref3);
        write_offset += GetSize<reftype3>::Size(ref4);
        write_offset += GetSize<reftype3>::Size(ref5);
        write_offset += GetSize<reftype3>::Size(ref6);
        write_offset += GetSize<reftype3>::Size(ref7);
        write_offset += GetSize<reftype3>::Size(ref8);
        write_offset += GetSize<reftype3>::Size(ref9);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, p.ref2_,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, p.ref3_,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, p.ref4_,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, p.ref5_,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, p.ref6_,  param_type::size6);
		DataProxy<reftype7, _TyImpl>::write(impl, p.ref7_,  param_type::size7);
		DataProxy<reftype8, _TyImpl>::write(impl, p.ref8_,  param_type::size8);
		DataProxy<reftype9, _TyImpl>::write(impl, p.ref9_,  param_type::size9);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(p.ref2_));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(p.ref3_));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(p.ref4_));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(p.ref5_));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(p.ref6_));
		DataProxy<reftype7, _TyImpl>::read(impl, const_cast<reftype7>(p.ref7_));
		DataProxy<reftype8, _TyImpl>::read(impl, const_cast<reftype8>(p.ref8_));
		DataProxy<reftype9, _TyImpl>::read(impl, const_cast<reftype9>(p.ref9_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
		reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);
		reftype8 ref8 = OffSetPtr<reftype8>::GetPtr(ptr, p.ref8_);
		reftype9 ref9 = OffSetPtr<reftype9>::GetPtr(ptr, p.ref9_);

        //WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, ref2,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, ref3,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, ref4,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, ref5,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, ref6,  param_type::size6);
		DataProxy<reftype7, _TyImpl>::write(impl, ref7,  param_type::size7);
		DataProxy<reftype8, _TyImpl>::write(impl, ref8,  param_type::size8);
		DataProxy<reftype9, _TyImpl>::write(impl, ref9,  param_type::size9);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
		reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);
		reftype8 ref8 = OffSetPtr<reftype8>::GetPtr(ptr, p.ref8_);
		reftype9 ref9 = OffSetPtr<reftype9>::GetPtr(ptr, p.ref9_);

        //READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(ref2));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(ref3));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(ref4));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(ref5));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(ref6));
		DataProxy<reftype7, _TyImpl>::read(impl, const_cast<reftype7>(ref7));
		DataProxy<reftype8, _TyImpl>::read(impl, const_cast<reftype8>(ref8));
		DataProxy<reftype9, _TyImpl>::read(impl, const_cast<reftype9>(ref9));
	}

};

template <typename _TyImpl, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
struct ParamTraits< _TyImpl, Tuple10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> >
{
	typedef Tuple10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> param_type;
	typedef typename RefType<typename param_type::reftype1>::reftype reftype1;
	typedef typename RefType<typename param_type::reftype2>::reftype reftype2;
	typedef typename RefType<typename param_type::reftype3>::reftype reftype3;
	typedef typename RefType<typename param_type::reftype4>::reftype reftype4;
	typedef typename RefType<typename param_type::reftype5>::reftype reftype5;
	typedef typename RefType<typename param_type::reftype6>::reftype reftype6;
	typedef typename RefType<typename param_type::reftype7>::reftype reftype7;
	typedef typename RefType<typename param_type::reftype8>::reftype reftype8;
	typedef typename RefType<typename param_type::reftype9>::reftype reftype9;
	typedef typename RefType<typename param_type::reftype10>::reftype reftype10;

    static inline size_t GetWriteSize(_TyImpl& impl, const param_type& p, const void* ptr)
    {
        reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
        reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
        reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
        reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
        reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
        reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
        reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);
        reftype8 ref8 = OffSetPtr<reftype8>::GetPtr(ptr, p.ref8_);
        reftype9 ref9 = OffSetPtr<reftype9>::GetPtr(ptr, p.ref9_);
        reftype10 ref10 = OffSetPtr<reftype10>::GetPtr(ptr, p.ref10_);

        size_t write_offset = 0;
        write_offset += GetSize<reftype1>::Size(ref1);
        write_offset += GetSize<reftype2>::Size(ref2);
        write_offset += GetSize<reftype3>::Size(ref3);
        write_offset += GetSize<reftype3>::Size(ref4);
        write_offset += GetSize<reftype3>::Size(ref5);
        write_offset += GetSize<reftype3>::Size(ref6);
        write_offset += GetSize<reftype3>::Size(ref7);
        write_offset += GetSize<reftype3>::Size(ref8);
        write_offset += GetSize<reftype3>::Size(ref9);
        write_offset += GetSize<reftype3>::Size(ref10);
        return write_offset;
    }

	static size_t GetReadSize(_TyImpl& impl)
	{
		return DataProxy<reftype1, _TyImpl>::read_head(impl);
	}

	static inline void write(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::write(impl, p.ref1_,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, p.ref2_,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, p.ref3_,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, p.ref4_,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, p.ref5_,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, p.ref6_,  param_type::size6);
		DataProxy<reftype7, _TyImpl>::write(impl, p.ref7_,  param_type::size7);
		DataProxy<reftype8, _TyImpl>::write(impl, p.ref8_,  param_type::size8);
		DataProxy<reftype9, _TyImpl>::write(impl, p.ref9_,  param_type::size9);
		DataProxy<reftype10, _TyImpl>::write(impl, p.ref10_,  param_type::size10);
	}

	static inline void read(_TyImpl& impl, const param_type& p)
	{
		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(p.ref1_));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(p.ref2_));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(p.ref3_));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(p.ref4_));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(p.ref5_));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(p.ref6_));
		DataProxy<reftype7, _TyImpl>::read(impl, const_cast<reftype7>(p.ref7_));
		DataProxy<reftype8, _TyImpl>::read(impl, const_cast<reftype8>(p.ref8_));
		DataProxy<reftype9, _TyImpl>::read(impl, const_cast<reftype9>(p.ref9_));
		DataProxy<reftype10, _TyImpl>::read(impl, const_cast<reftype10>(p.ref10_));
	}

	static inline void write_ptr(_TyImpl& impl, const param_type& p, const void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
		reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);
		reftype8 ref8 = OffSetPtr<reftype8>::GetPtr(ptr, p.ref8_);
		reftype9 ref9 = OffSetPtr<reftype9>::GetPtr(ptr, p.ref9_);
		reftype10 ref10 = OffSetPtr<reftype10>::GetPtr(ptr, p.ref10_);

        //WRITE_PREDEF

		DataProxy<reftype1, _TyImpl>::write(impl, ref1,  param_type::size1);
		DataProxy<reftype2, _TyImpl>::write(impl, ref2,  param_type::size2);
		DataProxy<reftype3, _TyImpl>::write(impl, ref3,  param_type::size3);
		DataProxy<reftype4, _TyImpl>::write(impl, ref4,  param_type::size4);
		DataProxy<reftype5, _TyImpl>::write(impl, ref5,  param_type::size5);
		DataProxy<reftype6, _TyImpl>::write(impl, ref6,  param_type::size6);
		DataProxy<reftype7, _TyImpl>::write(impl, ref7,  param_type::size7);
		DataProxy<reftype8, _TyImpl>::write(impl, ref8,  param_type::size8);
		DataProxy<reftype9, _TyImpl>::write(impl, ref9,  param_type::size9);
		DataProxy<reftype10, _TyImpl>::write(impl, ref10,  param_type::size10);
	}

	static inline void read_ptr(_TyImpl& impl, const param_type& p, void* ptr)
	{
		reftype1 ref1 = OffSetPtr<reftype1>::GetPtr(ptr, p.ref1_);
		reftype2 ref2 = OffSetPtr<reftype2>::GetPtr(ptr, p.ref2_);
		reftype3 ref3 = OffSetPtr<reftype3>::GetPtr(ptr, p.ref3_);
		reftype4 ref4 = OffSetPtr<reftype4>::GetPtr(ptr, p.ref4_);
		reftype5 ref5 = OffSetPtr<reftype5>::GetPtr(ptr, p.ref5_);
		reftype6 ref6 = OffSetPtr<reftype6>::GetPtr(ptr, p.ref6_);
		reftype7 ref7 = OffSetPtr<reftype7>::GetPtr(ptr, p.ref7_);
		reftype8 ref8 = OffSetPtr<reftype8>::GetPtr(ptr, p.ref8_);
		reftype9 ref9 = OffSetPtr<reftype9>::GetPtr(ptr, p.ref9_);
		reftype10 ref10 = OffSetPtr<reftype10>::GetPtr(ptr, p.ref10_);

        //READ_PREDEF

		DataProxy<reftype1, _TyImpl>::read(impl, const_cast<reftype1>(ref1));
		DataProxy<reftype2, _TyImpl>::read(impl, const_cast<reftype2>(ref2));
		DataProxy<reftype3, _TyImpl>::read(impl, const_cast<reftype3>(ref3));
		DataProxy<reftype4, _TyImpl>::read(impl, const_cast<reftype4>(ref4));
		DataProxy<reftype5, _TyImpl>::read(impl, const_cast<reftype5>(ref5));
		DataProxy<reftype6, _TyImpl>::read(impl, const_cast<reftype6>(ref6));
		DataProxy<reftype7, _TyImpl>::read(impl, const_cast<reftype7>(ref7));
		DataProxy<reftype8, _TyImpl>::read(impl, const_cast<reftype8>(ref8));
		DataProxy<reftype9, _TyImpl>::read(impl, const_cast<reftype9>(ref9));
		DataProxy<reftype10, _TyImpl>::read(impl, const_cast<reftype10>(ref10));
	}
};


//////////////////////////////////////////////////////////////////////////
template <typename _TyImpl, typename _P>
static inline bool WriteParam(_TyImpl& buffer, const _P& p)
{
	typedef typename SimilarTypeTraits<_P>::Type Type;
	ParamTraits<_TyImpl, Type>::write(buffer, static_cast<const Type&>(p));
	return false;
}

template <typename _TyImpl, typename _P>
static inline bool ReadParam(_TyImpl& impl, _P& p)
{
	typedef typename SimilarTypeTraits<_P>::Type Type;
	ParamTraits<_TyImpl, Type>::read(impl, static_cast<Type&>(p));
	return false;
}

template <typename _P>
static inline bool WriteParam(ShareMemoryWrap& impl, _P& p, bool needinit = true)
{
    typedef typename SimilarTypeTraits<_P>::Type Type;

	if (needinit)
	{
		size_t size = ParamTraits<ShareMemoryWrap, Type>::GetWriteSize(impl, static_cast<Type&>(p));
		impl.RequestWrite(size);
		DataProxy< Type,ShareMemoryWrap>::write_head( impl, size);
	}
    ParamTraits<ShareMemoryWrap, Type>::write(impl, static_cast<Type&>(p));
    return false;
}

template <typename _P>
static inline bool ReadParam(ShareMemoryWrap& impl, _P& p, bool needinit = true)
{
	typedef typename SimilarTypeTraits<_P>::Type Type;

	if (needinit)
	{
		impl.InitRead();
		//size_t read_offset = 0;
		size_t read_offset = ParamTraits<ShareMemoryWrap, Type>::GetReadSize(impl); 
		impl.RequestRead(read_offset);
	}
    
    ParamTraits<ShareMemoryWrap, Type>::read(impl, static_cast<Type&>(p));
    return false;
}

#endif

