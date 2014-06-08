/** 
 * @file sharememory.h
 * @brief ��˵��
 * @sa �ο�����
 * @author Luhaoqing 
 * @date 17/5/2013
 *
 * ��ϸ˵��   
 */
#ifndef SHARE_MEMORY_API_H
#define SHARE_MEMORY_API_H

//���������ڴ���API���ṩ��ƽ̨֧��
#ifdef  _WIN32
#include <stdio.h>
#include <Windows.h>
#endif

#ifdef  _LINUX
#include <stdio.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#endif

#ifdef _WIN32
#define SM_INVALID_HANDLE NULL 
#endif

#ifdef  _LINUX
#define SM_INVALID_HANDLE -1 
#endif

#define MAX_SHAREMEMORY_64  64

//�����windows���������
#ifdef _WIN32
#define INIT_HANDLE 0xFFFFFFFFFFFFFFFF
typedef HANDLE SMHandle;
typedef int    SMKey;
#endif

//�����linux���������
#ifdef  _LINUX
typedef int   SMHandle;
typedef key_t SMKey;	
#endif

#define SHARE_MEM_INVALID_HANDLE (SMHandle)-1
namespace share_memory
{
    //����һ��ShareMemory����ָ��
    SMHandle CreateShareMemory(SMKey Key, int nSize);

    //��һ���Ѿ����ڵ�ShareMemory����ָ��
    SMHandle OpenShareMemory(SMKey pKey, int nSize);

    //�õ�ָ����ShareMemory����ָ��ӳ��
    char* MapShareMemory(SMHandle handle);

    //�ر�ָ����ShareMemory����ָ��ӳ��
    void UnMapShareMemory(char* pData);

    void CloseSharememory(SMHandle handle);
} //namespace share_memory

#endif

