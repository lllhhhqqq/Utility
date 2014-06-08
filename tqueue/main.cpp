#include <iostream>
//#include <atomic>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iostream>

#include "Type_Cast.hpp"
#include "ShareMemoryImpl.h"
#include "tqueue.h"
#include "ShareMemoryWrap.h"
#include "Memory.h"
#include "Param_Trait.hpp"
#include "alloc.h"
#include "serial_macro.hpp"

#include "Win32ThreadImpl.h"
#include "worker_pool.h"

using namespace std;
using namespace share_memory;

//////////////////////////////////////////////////////////////////////////


struct tmptest1
{
	int a;
	int b;
	std::string x;
	static size_t GetWriteSize(ShareMemoryWrap& impl,const tmptest1* pThis)
	{
		return tmptest1::inn_.inner_call_->GetWriteSize(impl, pThis);
	}
	static size_t GetReadSize(ShareMemoryWrap& impl)
	{
		return tmptest1::inn_.inner_call_->GetReadSize(impl);
	}
	static void WriteBuff(ShareMemoryWrap& impl,const tmptest1* pThis)
	{
	tmptest1::inn_.inner_call_->WriteBuff(impl,pThis);
	}
	static void ReadBuff(ShareMemoryWrap& impl,tmptest1* pThis)
	{
	tmptest1::inn_.inner_call_->ReadBuff(impl,pThis);
	}
	struct Inner{ 
		Inner():inner_call_(NULL) 
	{
	METHOD_PROLOGUE_INNER(tmptest1,Inner);
	auto tuple = MakeTuple(pThis->a,pThis->b,pThis->x);
	inner_call_ = Make_Inner_Call(tuple);
		}
		~Inner()
	{
	delete inner_call_;
	}
	Inner_Call_BaseT<ShareMemoryWrap>* inner_call_;
	};
public:
	   static Inner inn_;
	   }; tmptest1::Inner tmptest1::inn_;

BEGIN_SERIAL(testa)
	std::vector<int> a;
	char b[20];
	int c;
	std::string d;
	int e;
DECLARE_SERIAL_5(testa,a,b,c,d,e)
END_SERIAL(testa)

BEGIN_SERIAL(testc)
	int i;
	std::string m;
	int n;
	testa a_;
	std::list<std::string> str_list_;
DECLARE_SERIAL_5(testc,i,m,n,a_,str_list_)
END_SERIAL(testc)

void TestSerial()
{
    ShareMemoryImpl impl(1000);
    //AttachAllocer<ShareMemoryImpl> alloc(impl);
    //char* buffer = alloc.Alloc(1024*1024*500);
    //strcpy(buffer,"dasfdsadfsdafawerwerwerasdasdfasd");
    //TQueue<char[1024], ShareMemoryImpl, 256> queue;
	//queue.init();
    TQueue<char[1024], ShareMemoryImpl, 256>::GetInstance()->init();
    
	/*tmptest1 tmp,t2;
	tmp.a = 1;
	tmp.b = 2;
	tmp.x = "this is adadfsadsfweweqrwerwer";*/
	//MemoryRead m;
    time_t start_time,end_time;
	testa c,d;
	c.a.push_back(1);
	c.a.push_back(2);
	strcpy(c.b,"sdsad");
	c.c = 5;
	c.d = "dsddfse";
	c.e = 9;

	testc g,h,i;
	g.i = 3;
	g.m = "sdfdsafdasdf";
	g.n = 900;
	g.a_.a.push_back(5);
	g.a_.a.push_back(508);
	strcpy(g.a_.b,"hello!");
	g.a_.c = 65323;
	g.a_.d = "this is internal";
	g.a_.e = 23;
	g.str_list_.push_back("sdfds");
	g.str_list_.push_back("sdfds2");

    start_time = clock();
    for (int i = 0; i < 100000; ++i)
    {
	ShareMemoryWrap wrap,wrap2;
	WriteParam(wrap,g);
	ReadParam(wrap2,h);
    }
    end_time = clock();

    std::cout<< "time is " << end_time - start_time << std::endl;

	std::cout << h.i << std::endl;

	ShareMemoryWrap m;
	WriteParam(m,g);
	ReadParam(m,i);

	std::cout<< "i.i is "<< i.i << std::endl;
	std::cout<< "i.m is "<< i.m << std::endl;
	std::cout<< "i.n is "<< i.n << std::endl;
	std::cout<< "i.a_.a is "<< std::endl;
	for(size_t count = 0; count < i.a_.a.size(); ++count)
	{
		std::cout<< i.a_.a[count]<< std::endl;
	}
	std::cout<< "i.a_.b is "<< i.a_.b << std::endl;
	std::cout<< "i.a_.c is "<< i.a_.c << std::endl;
	std::cout<< "i.a_.d is "<< i.a_.d << std::endl;
	std::cout<< "i.a_.e is "<< i.a_.e << std::endl;
	std::cout<< "i.str_list is"<< std::endl;
	for (auto begin = i.str_list_.begin();begin != i.str_list_.end(); ++begin)
	{
		std::cout<<*begin<< std::endl;
	}
}

void testbind()
{
    std::cout << "this is a bind test" << std::endl;
}

void TestWorkPool()
{
    /*std::function<void(void)> f = std::bind(&testbind);
    Win32ThreadImpl threadimpl(f,"test");

    threadimpl.Start();*/
    WorkerPool pool;
    pool.init();
    pool.start();
    int count = 0;
    while (count < 5)
    {
        ++count;
        Sleep(500);
        for (int i = 0; i < 5000; i++)
        {
            RunParam* tmpparam = new RunParam();
            pool.addJob(tmpparam);
        }
    }

    pool.stop();
}

int main(int argc, char **argv)
{
    TestWorkPool();

    
    return 0;
}
