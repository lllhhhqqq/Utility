/** 
 * @file event.h
 * @brief ��˵��
 * @sa �ο�����
 * @author Luhaoqing 
 * @date 18/6/2013
 *
 * ��ϸ˵��   
 */
#ifndef EVENT_H
#define EVENT_H

#include <windows.h>

class Event
{
public:
    Event():event_(CreateEvent(0,FALSE, FALSE,0))
    {

    }
    ~Event() 
    {
        Clear();
    }

    void Set()
    {
        SetEvent(event_);
    }

    void Wait()
    {
        WaitForSingleObject(event_,INFINITE);
    }

    void Clear()
    {
        CloseHandle(event_);
    }
private:
    HANDLE event_;
};
#endif