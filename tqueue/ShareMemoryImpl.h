/** 
 * @file ShareMemoryImpl.h
 * @brief ��˵��
 * @sa �ο�����
 * @author Luhaoqing 
 * @date 17/5/2013
 *
 * ��ϸ˵��   
 */
#ifndef SHARE_MEMORY_IMPL_H
#define SHARE_MEMORY_IMPL_H

#include "sharememory.h"

namespace share_memory
{

class ShareMemoryImpl
{
public:
    explicit ShareMemoryImpl(SMKey key);

    ~ShareMemoryImpl();

    char* Alloc(size_t size);

    char* ReAlloc(size_t size);

    void Free();

    const size_t GetSize() const;

private:
    SMKey key_;

    SMHandle handle_;

    char* buffer_;

    size_t size_;
};

} //share_memory

#endif