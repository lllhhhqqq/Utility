/** 
 * @file alloc.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 17/5/2013
 *
 * 详细说明   
 */
/*

//创建一个ShareMemory对象指针
SMHandle CreateShareMemory(SMKey Key, int nSize);

//打开一个已经存在的ShareMemory对象指针
SMHandle OpenShareMemory(SMKey pKey, int nSize);

//得到指定的ShareMemory对象指针映射
char* MapShareMemory(SMHandle handle);

//关闭指定的ShareMemory对象指针映射
void UnMapShareMemory(char* pData);

void CloseSharememory(SMHandle handle);*/

/** 
 * @brief 内存分配器的模板类
 * @sa 参考对象
 * @author 作者
 *
 * 详细说明
 */

#ifndef ALLOC_H
#define ALLOC_H

template <typename _TyAllocImpl>
class Allocer
{
public:
    inline char* Alloc(size_t size) {
        return alloc_.Alloc(size);
    }

    inline void Free() {
        alloc_.Free();
    }

    inline char* Realloc(size_t size) {
        return alloc_.Realloc(size);
    }
private:
    _TyAllocImpl alloc_;
};

template <typename _TyAllocImpl>
class AttachAllocer
{
public:
    inline explicit AttachAllocer(_TyAllocImpl& alloc)
        :alloc_(alloc)
    {

    }

    inline ~AttachAllocer() {}

    inline char* Alloc(size_t size) {
        return alloc_.Alloc(size);
    }

    inline void Free() {
        alloc_.Free();
    }

    inline char* Realloc(size_t size) {
        return alloc_.Realloc(size);
    }
private:
    _TyAllocImpl& alloc_;
};

#endif
