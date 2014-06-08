/** 
 * @file worker_pool.h
 * @brief ��˵��
 * @sa �ο�����
 * @author Luhaoqing 
 * @date 5/6/2013
 *
 * ��ϸ˵��   
 */

#ifndef WORKER_POLL_H
#define WORKER_POLL_H

#include <list>
#include <vector>
#include <Windows.h>

#include "lock_impl.h"
#include "lock.h"
#include "event.h"

struct RunParam
{
    void Run() 
    {

    }
};

class WorkerImpl;
class ParamList;
class BaseFunc;
//struct RunParam;

//inwindows it can impl by iocp, how is works in linux?
//Ŀǰ��һ���̳߳� ���ǽ��̳���ôȥ��
//���л� �����л��Ŀ���Ѿ����� 
//���� n�������ڴ��ͨ��
//����������,ʹ��iocp�Ĳ���Ҫ�����ȥ
//template <typename PoolContainer = std::vector<Worker*> >
class WorkerPool
{
public:
    typedef long long InnerHandle;
    //param attrib
    struct ParamInternal
    {
        InnerHandle handle;
        RunParam* param;
    };
    //can use list only
    typedef std::vector<WorkerImpl*> PoolContainer;
    typedef std::list<ParamInternal*> ParamList;
    typedef PoolContainer::iterator Iterator;
    typedef PoolContainer::const_iterator ConstIterator;
    
    WorkerPool();
    ~WorkerPool();

    void start();
    //��ʼ��
    bool init();

    //����
    bool unInit();

    //��ͣ
    void pause();

    //ֹͣ
    bool stop();

    //Job Part
    bool addJob(RunParam* param);
    //need iterator, how it works, need different dispatch, how to dispatch ? or there need a different way

   

private:
    // the func to bind
    void dispatch();

    //Job Part
    bool getJob(ParamInternal*& inner_param);

    bool deleteRunParam(ParamInternal* internal_param);

    //Worker Part
    void addWorker(WorkerImpl* worker);

    WorkerImpl* FindWorker(unsigned long work_id);

    //
    InnerHandle getHandle() const; 

    void NotifyIdle();

private:
    //ִ����
    PoolContainer excuteor_; 

    //ִ�ж���
    ParamList param_list_;

    //disallow copy and assign
    volatile unsigned int inner_handle_;

    HANDLE io_handler_;
    //�ٽ������������б�

    Lock<LockImpl> lock_;

    //�����ź���
    Event idle_evnet_;

    //����߳���
    unsigned int max_threads;

    //�����߳��˳�
    bool exit_thread_;	
};
#endif