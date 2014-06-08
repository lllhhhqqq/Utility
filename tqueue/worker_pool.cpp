#include "worker_pool.h"
#include "Win32ThreadImpl.h"
#include "ThreadDef.h"
#include "param.h"
#include "worker_inner.h"


#include <algorithm>
#include <functional>
#include <cassert>

#define TEST_THREAD_COUNT 10

WorkerPool::WorkerPool()
    :io_handler_(INVALID_HANDLE_VALUE)
    ,inner_handle_(-1)
    ,exit_thread_(false)
    ,max_threads(TEST_THREAD_COUNT)
{

}

WorkerPool::~WorkerPool()
{
    unInit();
}

bool WorkerPool::init()
{
    bool ret = false;
    char buffername[128] = {0};

    //to Create two IOCP? one is secdule thread and other is worker thread;
    //原子队列？
    if ((io_handler_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 
        NULL, 0 , TEST_THREAD_COUNT )) != NULL)
    {
        //Create Thread
        //Create single thread
        //create iocp,bind iocp
        //create 10 thread
        //bind thread to iocp
        std::function<void(void)> f = std::bind(&WorkerPool::dispatch, this);

        for (unsigned int i = 0; i < max_threads; ++i)
        {
            buffername[0] = 0;
            sprintf(buffername, "test thread%d", i);
            
            WorkerImpl* work_thread = new Win32ThreadImpl(f, buffername);
            addWorker(work_thread);
        }
    } 
    return ret;
}

void WorkerPool::start()
{
    for_each(excuteor_.begin(), excuteor_.end(), [](WorkerImpl* impl){
        impl->Start();
    });
}

bool WorkerPool::unInit()
{
    for (auto impl = excuteor_.begin(); impl != excuteor_.end();
        ++impl)
    {
        (*impl)->UnInit();
        delete *impl;
    }
    excuteor_.clear();

    // now no use iocp
    ::CloseHandle(io_handler_);
    return true;
}

void WorkerPool::pause()
{
    //
    
}

bool WorkerPool::stop()
{
    exit_thread_ = true;
    //notify all thread to exit
    for (auto impl = excuteor_.begin(); impl != excuteor_.end(); ++impl)
    {
        NotifyIdle();
        //(*impl)->Stop();
    }
    
    return true;
}

bool WorkerPool::addJob( RunParam* param )
{
    //lock
    AutoLock lock(lock_);

    InnerHandle job_handle = getHandle();

    ParamInternal* param_inner = new ParamInternal();
    param_inner->handle = job_handle;
    param_inner->param = param;

    param_list_.push_back(param_inner);

    //激活等待的线程
    NotifyIdle();
    //no need to return value ?
    return true;
}

bool WorkerPool::getJob( ParamInternal*& inner_param )
{
    //lock
    bool ret = false;
    AutoLock lock(lock_);
   
    if (!param_list_.empty())
    {
        inner_param = param_list_.front();
        param_list_.pop_front();
        //inner_param = *(param_list_.erase(param_list_.begin()));
        ret = true;
    }
    return ret;
}

void WorkerPool::dispatch()
{
    //lock
    //if(get job)
    //this is a worker ,sign has work
    //else
    //set empty
    //AutoLock ato_lck(lock_);
    //线程主函数
    
    HANDLE realThread = NULL;
    unsigned long id = ::GetCurrentThreadId();
    WorkerImpl* impl = FindWorker(id);
    assert(NULL != impl);
    
    while (!exit_thread_)
    {
        //AutoLock lock(lock_);
        ParamInternal* inner;
        if (getJob(inner))
        {
            //first unlock
            //激活等待的线程
            NotifyIdle();

            inner->param->Run();
        }
        else
        {
            printf("Thread %s Wait\n",impl->GetName());
            //等待有任务或者获取任务的信号
            idle_evnet_.Wait();
        }
    }

    impl->Stop();
}

bool WorkerPool::deleteRunParam( ParamInternal* internal_param )
{
    AutoLock lock(lock_);
    // no need ?
    return false;
}

void WorkerPool::addWorker( WorkerImpl* worker )
{
    assert ( NULL != worker );
    excuteor_.push_back(worker);
}

WorkerPool::InnerHandle WorkerPool::getHandle() const
{
    ::InterlockedIncrement((volatile unsigned int*)&inner_handle_);
    return inner_handle_;
}

void WorkerPool::NotifyIdle()
{
    idle_evnet_.Set();
}

//for debug use
WorkerImpl* WorkerPool::FindWorker( unsigned long work_id )
{
    WorkerImpl* find_impl = NULL;
    for_each(excuteor_.begin(),excuteor_.end(), [&find_impl, work_id](WorkerImpl* impl){
        if (impl->GetId() == work_id)
        {
            find_impl = impl;
        }
    });

    return find_impl;
}

