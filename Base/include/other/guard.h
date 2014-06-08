/** 
 * @file guard.h
 * @brief 
 * @author Luhaoqing 
 * @date 2013/11/22
 */
#ifndef SCOPEGUARD_DEF_H
#define SCOPEGUARD_DEF_H

#include <define.h>
#include <functional>

class ScopeGuard
{
public:
    explicit ScopeGuard(std::function<void()> exit_scope)
        : exit_scpoe_(exit_scope)
        , dismissed_(false)
    { }

    ~ScopeGuard()
    {
        if (!dismissed_) exit_scpoe_();
    }

    void Dismiss()
    {
        dismissed_ = true;
    }

private:
    std::function<void()> exit_scpoe_;
    bool dismissed_;

private: // noncopyable
    DISALLOW_COPY_ASSIGN(ScopeGuard)
};

#endif
