/** 
 * @file alloc.h
 * @brief ��˵��
 * @sa �ο�����
 * @author Luhaoqing 
 * @date 17/5/2013
 *
 * ��ϸ˵��   
 */
/*

//����һ��ShareMemory����ָ��
SMHandle CreateShareMemory(SMKey Key, int nSize);

//��һ���Ѿ����ڵ�ShareMemory����ָ��
SMHandle OpenShareMemory(SMKey pKey, int nSize);

//�õ�ָ����ShareMemory����ָ��ӳ��
char* MapShareMemory(SMHandle handle);

//�ر�ָ����ShareMemory����ָ��ӳ��
void UnMapShareMemory(char* pData);

void CloseSharememory(SMHandle handle);*/

/** 
 * @brief �ڴ��������ģ����
 * @sa �ο�����
 * @author ����
 *
 * ��ϸ˵��
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
