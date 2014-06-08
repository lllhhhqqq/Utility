/** 
 * @file WorkerImpl.h
 * @brief ��˵��
 * @sa �ο�����
 * @author Luhaoqing 
 * @date 6/6/2013
 *
 * ��ϸ˵��   
 */
#ifndef WORKER_IMPL_H
#define WORKER_IMPL_H

#include "ThreadDef.h"
#include <string>


/// Worker Bind Call, call to get tasklist then call task->worker(task->param);
class WorkerImpl
{
public:
    //��ʼ������
    virtual bool Init() = 0;

    //��ʼ
    virtual bool Start() = 0;

    //����
    virtual bool Stop() = 0;

    //��ͣ
    virtual bool Pause() = 0; 

    //�ͷŶ���
    virtual bool UnInit() = 0;

    //
    virtual const char* GetName() const = 0;

    virtual int GetId() const = 0;

    virtual HANDLE GetHandle() const = 0;


    //Closure& closure_;
};

#endif // !WORKER_IMPL_H
