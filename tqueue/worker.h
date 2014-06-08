/** 
 * @file worker.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 5/6/2013
 *
 * 详细说明   
 */
#ifndef WORKER_H
#define WORKER_H

#include "ThreadDef.h"

///the class like thread impl, process impl
class WorkImpl;

///the class howto work
class BaseWork;

class Worker
{
public:
    Worker();
    ~Worker();

    void Run();

private:
    WorkImpl* impl_;

    Closure closure_;
    //BaseWork& inner_;
};

#endif // !WORKER_H
