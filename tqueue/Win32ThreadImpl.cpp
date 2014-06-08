#include "Win32ThreadImpl.h"
#include <process.h>
#include <assert.h>

//try catch
    //pimpl->secdule_->Dispatch(pimpl);

    /*if (pimpl->Init())
    {
        ::ResetEvent(pimpl->thread_attrib_->tmpsig_);

        do 
        {
            try {
                pimpl->closure_();
            }
            catch(...) {
                //debugmsg("FAILED__  Caught a exception in OnCall in CThread::WorkThread.");
            }

        } while (WaitForSingleObject(pimpl->thread_attrib_->stopsig_,pimpl->thread_attrib_->interval_)
            == WAIT_TIMEOUT);

        //end do
        pimpl->UnInit();

        SetEvent(pimpl->thread_attrib_->tmpsig_);
    }*/

// The information on how to set the thread name comes from
// a MSDN article: http://msdn2.microsoft.com/en-us/library/xcb2z8hs.aspx
const DWORD kVCThreadNameException = 0x406D1388;

typedef struct tagTHREADNAME_INFO {
    DWORD dwType;  // Must be 0x1000.
    LPCSTR szName;  // Pointer to name (in user addr space).
    DWORD dwThreadID;  // Thread ID (-1=caller thread).
    DWORD dwFlags;  // Reserved for future use, must be zero.
} THREADNAME_INFO;

// This function has try handling, so it is separated out of its caller.
void SetNameInternal(UINT thread_id, const char* name) {
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = name;
    info.dwThreadID = thread_id;
    info.dwFlags = 0;

    __try {
        RaiseException(kVCThreadNameException, 0, sizeof(info)/sizeof(DWORD),
            reinterpret_cast<DWORD_PTR*>(&info));
    } __except(EXCEPTION_CONTINUE_EXECUTION) {
    }
}

UINT WINAPI Win32ThreadImpl::WorkFunc( LPVOID lpParam )
{
    Win32ThreadImpl* pimpl = static_cast<Win32ThreadImpl*>(lpParam);

    assert(NULL != pimpl);
    ::ResetEvent(pimpl->thread_attrib_->tmpsig_);

    do 
    {
        try
        {
            pimpl->closure_();
        }
        catch(...)
        {
            //Log Error
            return -1;
        }

    } while (WaitForSingleObject(pimpl->thread_attrib_->stopsig_,pimpl->thread_attrib_->interval_)
        == WAIT_TIMEOUT);

    //end do
    pimpl->UnInit();

    SetEvent(pimpl->thread_attrib_->tmpsig_);
    

    return 0;
}

Win32ThreadImpl::Win32ThreadImpl(Closure& closure, const char* name)
    :closure_(closure)
    ,thread_attrib_(new ThreadAttribute())
    ,thread_info_(name)
{

}

Win32ThreadImpl::Win32ThreadImpl( Closure& closure )
    :closure_(closure)
    ,thread_attrib_(new ThreadAttribute())
    ,thread_info_()
{

}

Win32ThreadImpl::~Win32ThreadImpl()
{
    if (thread_attrib_->stopsig_ != INVALID_HANDLE_VALUE)
        ::CloseHandle(thread_attrib_->stopsig_);

    ::CloseHandle(thread_attrib_->tmpsig_);
}

bool Win32ThreadImpl::Init( )
{
    return true;
}

bool Win32ThreadImpl::Start()
{
    if ((thread_attrib_->thread_ = (HANDLE)_beginthreadex(NULL,0, 
        &WorkFunc, (LPVOID)this, 0, &thread_info_.id_)) != NULL)
    {
        //SetNameInternal(thread_info_.id_, thread_info_.name_.c_str());
        if (thread_info_.name_ != "")
            SetName(thread_info_.id_, thread_info_.name_.c_str());

        return true;
    }

    return false;
}

bool Win32ThreadImpl::Stop()
{
    SetEvent(thread_attrib_->stopsig_);
    Pause();
    return FALSE;
}

bool Win32ThreadImpl::Pause()
{
    WaitForSingleObject(thread_attrib_->tmpsig_,INFINITE);
    return false;
}

bool Win32ThreadImpl::UnInit()
{
    return false;
}

const char* Win32ThreadImpl::GetName() const
{
    return thread_info_.name_.c_str();
}

void Win32ThreadImpl::SetName( unsigned int id, const char* name )
{
    SetNameInternal(id, name);
}

int Win32ThreadImpl::GetId() const
{
    return thread_info_.id_;
}

HANDLE Win32ThreadImpl::GetHandle() const
{
    return thread_attrib_->thread_;
}

