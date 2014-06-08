#include <iostream>

#include <design_pattern/Singleton.h>
#include <Lock/Lock.h>
#include <vector>

using namespace std;

class NullLock;

class TA : public base::Singleton<TA, base::NULL_LOCK>
{
private:
    TA()
    {
        m = 0;
    }

    int m;

public:
    int Getm() { return m; }

    friend Singleton<TA, base::NULL_LOCK>;
};

/*
template<typename _Tp>
inline typename std::remove_reference<_Tp>::type&&
move(_Tp&& __t)
{
    return static_cast<typename std::remove_reference<_Tp>::type&&>(__t);
}*/

struct X { int a; };

X&& test(X tmp)
{
    return std::move(tmp);
}

X& ref(X& tmp)
{
    return tmp;
}

template<typename _Tp>
inline typename std::remove_reference<_Tp>::type&&
move_(_Tp&& __t)
{
    return static_cast<typename std::remove_reference<_Tp>::type&&>(__t);
}

/*
template<typename _Tp>
inline typename std::remove_reference<_Tp>::type&
move_(_Tp& __t)
{
    return static_cast<typename std::remove_reference<_Tp>::type&>(__t);
}*/

template <typename _Tp>
_Tp& ref_(_Tp& _t)
{
    return _t;
}

template <typename _Tp>
_Tp& ref2_(_Tp _t)
{
    return _t;
}

void Move_TEst()
{
    X a;
    a.a = 3;
    X&& b = std::move(a);
    X&& b1 = test(a);
    X& b2 = ref(a);
    X&& c = std::move(X());

    int&& v = move_((2 + 3));
    int&& v２ = move_((2 + 3));
    //int& y1 = ref2_((2 + 3));
}

// is_convertible_to.cpp
#include <stdio.h>
struct S {};
struct T : public S {};

void testRight2(std::vector<int> v)
{
    v.push_back(1);
    v.push_back(2);
}



template<typename T>
void swap1(T& a, T& b)
{
    T t(move_(a));  // a为空，t占有a的初始数据
    a = move_(b); //  b为空， a占有b的初始数据
    b = move_(t); // t为空，b占有a的初始数据
 }

class A
{
public:
    A() {
        std::cout << "Default constructor." << std::endl;
        m_p = NULL;
    }

    ~A() {
        std::cout << "Destructor." << std::endl;
        delete m_p;
    }

    explicit A(const int n) {
        std::cout << "Unary constructor." << std::endl;
        m_p = new int(n);
    }

    A(const A& other) {
        std::cout << "Copy constructor." << std::endl;
        if (other.m_p) {
            m_p = new int(*other.m_p);
        }
        else {
            m_p = NULL;
        }
    }

    A(A&& other) {
        std::cout << "Move constructor." << std::endl;
        m_p = other.m_p;
        other.m_p = NULL;
    }

    A& operator=(const A& other) {
        std::cout << "Copy assignment operator." << std::endl;
        if (this != &other) {
            delete m_p;
            if (other.m_p) {
                m_p = new int(*other.m_p);
            }
            else {
                m_p = NULL;
            }
        }
        return *this;
    }

    A& operator=(A&& other) {
        std::cout << "Move assignment operator." << std::endl;
        if (this != &other) {
            delete m_p;
            m_p = other.m_p;
            other.m_p = NULL;
        }
        return *this;
    }

    int get() const {
        return m_p ? *m_p : 0;
    }

private:
    int * m_p;
};

template <typename Type> void Swap2(Type&& sb1, Type&& sb2)
{
    Type sb(sb1);
    sb1 = sb2;
    sb2 = sb;
}

class MAT
{
public:
    MAT() :a_("") {}

    MAT(std::string &val) : a_(val)
    {}

    MAT(std::string &&right_val) : a_(right_val)
    {
    }


    std::string a_;
};

#include "test_linq.h"

#include <windows.h>
#include <DbgHelp.h>

LONG WINAPI ExpFilter(struct _EXCEPTION_POINTERS *pExp)
{
    HANDLE hFile = ::CreateFile(
        "e:\\123.dmp",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (INVALID_HANDLE_VALUE != hFile)
    {
        MINIDUMP_EXCEPTION_INFORMATION einfo;
        einfo.ThreadId = ::GetCurrentThreadId();
        einfo.ExceptionPointers = pExp;
        einfo.ClientPointers = FALSE;

        ::MiniDumpWriteDump(
            ::GetCurrentProcess(),
            ::GetCurrentProcessId(),
            hFile,
            MiniDumpWithFullMemory,
            &einfo,
            NULL,
            NULL);
        ::CloseHandle(hFile);
    }

    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char** argv)
{
    ::SetUnhandledExceptionFilter(ExpFilter);

    int i = 0;
    i = i / i;

    cout << "end !" << endl;

    featureTest();
    functionTest();

    __try{

    }
    __finally{

    }
    ;
    //MAT xst("sss");
    /*A a(1);
    A b(2);
    Swap2(a, b);
    std::cout << a.get() << " " << b.get() << std::endl;*/


    /*int a = 3, b = 4;
    swap1(a, b);
    S * s = new S;
    T * t = new T;
    //s = t;
    __is_convertible_to(T, S) == true ?
        printf("true\n") : printf("false\n");
   // int t = A::Ins()->Getm();
    vector<int> mt;
    testRight2(mt);*/
    
    return 0;
}