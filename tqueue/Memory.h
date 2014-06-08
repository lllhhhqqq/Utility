#ifndef MEMORY_H_V1_0
#define MEMORY_H_V1_0

#include <list>
#include <string>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "Type_Cast.hpp"

class MemoryRead 
{
public:
    MemoryRead():read_offset(0),write_offset(0) { 
        buffer = new char[1024]; 
        memset(buffer,0,sizeof(buffer));
    }
    ~MemoryRead() { 
        delete []buffer;
    }

    inline void WritePos(size_t size)
    {
        memcpy(buffer + write_offset, (void*)&size, sizeof(size_t));
        write_offset += sizeof(size_t);
    }

	template <typename T>
    inline void write(typename RefType<T>::const_reftype val_write, size_t size)
    {
        WritePos(size);

        memcpy(buffer + write_offset, (void*)(&val_write), size);
        write_offset += size;
    }

    inline size_t ReadPos()
    {
        size_t length;
        memcpy((void*)&length, buffer+read_offset, sizeof(size_t));
        read_offset += sizeof(size_t);

        return length;
    }

    template <typename T>
    inline void read(typename RefType<T>::reftype val_read)
    {
        size_t length = ReadPos();

        memcpy((void*)&val_read, buffer+read_offset, length);
        read_offset += length;
    }

public:
    class Iterator
    {
    public:
        Iterator();
        ~Iterator();

    private:

    };

private:
    char* buffer;
    size_t read_offset;
    size_t write_offset;
};

template <>
inline void MemoryRead::write<std::string&>(const std::string& val_write, size_t size)
{
	WritePos(val_write.length());

	memcpy(buffer + write_offset, (void*)val_write.c_str(), val_write.length()+1);
	write_offset += val_write.length()+1;
}

template <>
inline void MemoryRead::write<char*>(const char* val_write, size_t size)
{
	WritePos(size);

	memcpy(buffer + write_offset, (void*)val_write, size);
	write_offset += size;
}

template <>
inline void MemoryRead::read<std::string&>(std::string& val_read)
{

	size_t length = ReadPos();

	//val_read = std::string(buffer+read_offset,length);
	val_read.append(buffer+read_offset,length);
	read_offset += length + 1;
}

template <>
inline void MemoryRead::read<char*>(char* val_read)
{
	size_t length = ReadPos();
	memcpy((void*)val_read, buffer+read_offset, length);
	read_offset += length;
}

//////////////////////////////////////////////////////////////////////////
//insert help,? to support map set hashmap?
template <typename T,typename Container>
struct InsertHelp
{
    typedef Container container_type;

    static inline void Insert(Container& c,T& value)
    {
        //static_assert(false,"not support this type");
    }
};

template <typename T>
struct InsertHelp<T, std::list<T>>
{
    typedef std::list<T> container_type;

    static inline void Insert(std::list<T>& c,T& value)
    {
        //c.insert(value);
		c.push_back(value);
    }
};

template <typename T>
struct InsertHelp<T, std::vector<T>>
{
    typedef std::vector<T> container_type;

    static inline void Insert(std::vector<T>& c,T& value)
    {
        c.push_back(value);
    }
};
//////////////////////////////////////////////////////////////////////////

template <typename T, typename _TyImpl>
struct DataProxy;

template <typename T, typename _TyImpl>
struct DataProxy
{
	static inline void write_head(_TyImpl& impl, size_t size)
	{
		impl.WritePos(size);
	}

	static inline size_t read_head(_TyImpl& impl)
	{
		size_t size = impl.ReadPos();
		return size;
	}

    static inline void write(_TyImpl& impl, const T& valwrite, size_t size)
    {
        //默认采用结构体自己的方法来构造，读写序列
        WriteParam(impl, valwrite, false);
    }

    static inline void read(_TyImpl& impl, T& valread)
    {
        //默认采用结构体自己的方法来构造，读写序列
        ReadParam(impl, valread, false);
    }
};

template <typename T, typename _TyImpl>
struct DataProxy< std::vector<T>&, _TyImpl >
{
    typedef InsertHelp<T, std::vector<T> > InsertType;
    typedef typename InsertType::container_type ContainerType;
	typedef typename RefType<T>::reftype reftype;

	static inline void write_head(_TyImpl& impl, size_t size)
	{
		impl.WritePos(size);
	}

	static inline size_t read_head(_TyImpl& impl)
	{
		size_t size = impl.ReadPos();
		return size;
	}

    static inline void write(_TyImpl& impl, const ContainerType& valwrite, size_t size)
    {
        size = valwrite.size();

        impl.WritePos(size);

        for (auto begin = valwrite.begin(); begin != valwrite.end(); ++begin)
        {
            //TODO: not call DataProxy, to call Param,makeparam need innerdata;
            DataProxy<reftype, _TyImpl>::write(impl,*begin,sizeof(T));
        }
    }

    static inline void read(_TyImpl& impl, ContainerType& valread)
    {
        size_t size = impl.ReadPos();

        for (size_t i = 0; i < size; ++i)
        {
            T value;
            DataProxy<reftype, _TyImpl>::read(impl,value);
            InsertType::Insert(valread,value);
        }
    }
};

template <typename T, typename _TyImpl>
struct DataProxy< std::list<T>&, _TyImpl >
{
    typedef InsertHelp<T, std::list<T> > InsertType;
    typedef typename InsertType::container_type ContainerType;
	typedef typename RefType<T>::reftype reftype;

	static inline void write_head(_TyImpl& impl, size_t size)
	{
		impl.WritePos(size);
	}

	static inline size_t read_head(_TyImpl& impl)
	{
		size_t size = impl.ReadPos();
		return size;
	}

    static inline void write(_TyImpl& impl, const ContainerType& valwrite, size_t size)
    {
		size = valwrite.size();

        impl.WritePos(size);

        for (auto begin = valwrite.begin(); begin != valwrite.end(); ++begin)
        {
            //DataProxy<T>::write(*begin);
			DataProxy<reftype,_TyImpl>::write(impl,*begin,sizeof(T));
        }
    }

    static inline void read(_TyImpl& impl, ContainerType& valread)
    {
        size_t size = impl.ReadPos();

        for (size_t i = 0; i < size; ++i)
        {
            T value;
            DataProxy<reftype, _TyImpl>::read(impl,value);
            InsertType::Insert(valread,value);
        }
    }
};

#define HEAD_FUNC_DECLARE(Impl) \
static inline void write_head(Impl& impl, size_t size) \
{ impl.WritePos(size); } \
static inline size_t read_head(Impl& impl) \
{ \
	size_t size = impl.ReadPos(); \
	return size; \
}

#define Proxy_COMMON_DECLARE(type, Impl) \
template <typename Impl>\
struct DataProxy<type, Impl>\
{\
HEAD_FUNC_DECLARE(Impl) \
static inline void write(Impl& impl, const type& valwrite, size_t size)\
{\
    impl.write<type>(valwrite, size);\
}\
static inline void read(Impl& impl, type& valread)\
{\
    impl.read<type>(valread);\
}\
};

#define Proxy_COMMON_PTR_DEDLARE(type) \
template <typename Impl>\
struct DataProxy<type, Impl>\
{\
HEAD_FUNC_DECLARE(Impl) \
static inline void write(Impl& impl, const type valwrite, size_t size)\
{\
    impl.write<type>(valwrite, size);\
}\
static inline void read(Impl& impl, type valread)\
{\
    impl.read<type>(valread);\
}\
};

#define Proxy_COMMON_REF_DECLARE(type, Impl) \
template <typename Impl>\
struct DataProxy<type, Impl>\
{\
HEAD_FUNC_DECLARE(Impl) \
static inline void write(Impl& impl, const type valwrite, size_t size)\
{\
    impl.write<type>(valwrite, size);\
}\
static inline void read(Impl& impl, type valread)\
{\
    impl.read<type>(valread);\
}\
};

Proxy_COMMON_DECLARE(int, MemoryRead)
Proxy_COMMON_DECLARE(unsigned int, MemoryRead)
Proxy_COMMON_DECLARE(char, MemoryRead)
Proxy_COMMON_DECLARE(long, MemoryRead)
Proxy_COMMON_DECLARE(bool, MemoryRead)
Proxy_COMMON_DECLARE(long long, MemoryRead)
Proxy_COMMON_DECLARE(std::string, MemoryRead)

Proxy_COMMON_REF_DECLARE(int&, MemoryRead)
Proxy_COMMON_REF_DECLARE(unsigned int&, MemoryRead)
Proxy_COMMON_REF_DECLARE(char&, MemoryRead)
Proxy_COMMON_REF_DECLARE(long&, MemoryRead)
Proxy_COMMON_REF_DECLARE(bool&, MemoryRead)
Proxy_COMMON_REF_DECLARE(long long&, MemoryRead)
Proxy_COMMON_REF_DECLARE(std::string&, MemoryRead)

/*
template <>
struct DataProxy<std::string&>
{
static inline void write(MemoryRead& m, const std::string& valwrite, size_t size)
{
	m.write<std::string&>(valwrite, size);
}
static inline void read(MemoryRead& m, std::string& valread)
{
	m.read<std::string&>(valread);
}
};*/
//Proxy_COMMON_REF_DECLARE(std::string&)

Proxy_COMMON_PTR_DEDLARE(char*)

#endif // !MEMORY_H_V1_0
