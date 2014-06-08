#include "ShareMemoryImpl.h"
#include <assert.h>

namespace share_memory
{

ShareMemoryImpl::ShareMemoryImpl( SMKey key )
    :key_(key)
    ,buffer_(NULL)
    ,handle_(SHARE_MEM_INVALID_HANDLE)
    ,size_(0)
{
    assert(NULL != key_);
}

ShareMemoryImpl::~ShareMemoryImpl()
{
    Free();
}

char* ShareMemoryImpl::Alloc( size_t size )
{
    if (SHARE_MEM_INVALID_HANDLE == handle_)
    {
        handle_ = CreateShareMemory(key_, size);

        //Create Failed,Then Try to OPEN
        if (handle_ == SHARE_MEM_INVALID_HANDLE)
            handle_ = OpenShareMemory(key_, size);

        if (handle_ != SHARE_MEM_INVALID_HANDLE)
        {
            buffer_ = MapShareMemory(handle_);
            size_ = size;
        }
    }

    return buffer_;
}

char* ShareMemoryImpl::ReAlloc( size_t size )
{
    if (size > size_)
    {
        Free();
        Alloc(size);
    }

    return buffer_;
}

void ShareMemoryImpl::Free()
{
    if (SHARE_MEM_INVALID_HANDLE != handle_)
    {
        UnMapShareMemory(buffer_);
        CloseSharememory(handle_);
    }
    size_ = 0;
    handle_ = SHARE_MEM_INVALID_HANDLE;
    buffer_ = NULL;
}

const size_t ShareMemoryImpl::GetSize() const
{
    return size_;
}

} //namespace share_memory
