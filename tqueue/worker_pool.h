/** 
 * @file worker_pool.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 5/6/2013
 *
 * 详细说明   
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
//目前是一个线程池 考虑进程池怎么去做
//序列化 反序列化的框架已经存在 
//创建 n个共享内存的通道
//加锁的问题,使用iocp的部分要抽象出去
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
    //初始化
    bool init();

    //清理
    bool unInit();

    //暂停
    void pause();

    //停止
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
    //执行者
    PoolContainer excuteor_; 

    //执行队列
    ParamList param_list_;

    //disallow copy and assign
    volatile unsigned int inner_handle_;

    HANDLE io_handler_;
    //临界区保护任务列表

    Lock<LockImpl> lock_;

    //空闲信号量
    Event idle_evnet_;

    //最大线程数
    unsigned int max_threads;

    //服务线程退出
    bool exit_thread_;	
};
#endif