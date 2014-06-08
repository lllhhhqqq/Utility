#ifndef SHARE_MEMORY_WRAP_H
#define SHARE_MEMORY_WRAP_H

#include <string>
#include "ShareMemoryImpl.h"

using namespace share_memory;

using namespace std;

class ShareMemoryWrap
{
public:
	ShareMemoryWrap() :buffer_(NULL),read_offset(0),write_offset(0) 
	{
        queue_ = TQueue<char[1024], ShareMemoryImpl, 256>::GetInstance();
		//queue_.init();
	}
	~ShareMemoryWrap() {}

	bool RequestWrite(size_t size)
	{
		//todo size is provider by tuple
		SetWriteSize(size);

		return queue_->Write(*this);
	}

    bool InitRead()
    {
        return queue_->InitRead(*this);
    }

	bool RequestRead(size_t size)
	{
		return queue_->Read(*this, size);
	}

	void SetWriteSize(size_t size)
	{
		write_size_ = size;
	}

	size_t GetWriteSize()
	{
		return write_size_;
	}

	//改用callback来初始化数据，初始化数据头和中段数据 这个数据理论上是不会溢出的，
	//环形队列其实应该成为环形内存分配器
	void InitBuffer(char* bufferptr)
	{
		buffer_ = bufferptr;
	}

	inline void WritePos(size_t size)
	{
		memcpy(buffer_ + write_offset, (void*)&size, sizeof(size_t));
		write_offset += sizeof(size_t);
	}

	inline size_t ReadPos()
	{
		size_t length;
		memcpy((void*)&length, buffer_+read_offset, sizeof(size_t));
		read_offset += sizeof(size_t);

		return length;
	}

	template <typename T>
	inline void write(typename RefType<T>::const_reftype val_write, size_t size)
	{
		WritePos(size);

		memcpy(buffer_ + write_offset, (void*)(&val_write), size);
		write_offset += size;
	}

	template <typename T>
	inline void read(typename RefType<T>::reftype val_read)
	{
		size_t length = ReadPos();

		memcpy((void*)&val_read, buffer_+read_offset, length);
		read_offset += length;
	}

private:
	char* buffer_;
	size_t first_length_;

	size_t write_offset;
	size_t read_offset;
	size_t write_size_;

	TQueue<char[1024], ShareMemoryImpl, 256> *queue_;
};

template <>
inline void ShareMemoryWrap::write<std::string&>(const std::string& val_write, size_t size)
{
	WritePos(val_write.length());

	memcpy(buffer_ + write_offset, (void*)val_write.c_str(), val_write.length());
	write_offset += val_write.length();
}

template <>
inline void ShareMemoryWrap::write<char*>(const char* val_write, size_t size)
{
	WritePos(size);

	memcpy(buffer_ + write_offset, (void*)val_write, size);
	write_offset += size;
}

template <>
inline void ShareMemoryWrap::read<std::string&>(std::string& val_read)
{

	size_t length = ReadPos();

	val_read.append(buffer_+read_offset,length);
	read_offset += length;
}

template <>
inline void ShareMemoryWrap::read<char*>(char* val_read)
{
	size_t length = ReadPos();
	memcpy((void*)val_read, buffer_+read_offset, length);
	read_offset += length;
}

#endif