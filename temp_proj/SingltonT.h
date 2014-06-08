//
//  SingltonT.h
//

#ifndef SingltonT_h
#define SingltonT_h
#include <iostream>
#include <memory>

using namespace std;
using namespace std::tr1;

template <typename T>
class Singlton {
public:
    static T* instance();
    ~Singlton() {
        cout << "destruct singlton" << endl;
    }
protected:
    Singlton();
    //private:
protected:
    static std::tr1::shared_ptr<T> s_instance;
    //Singlton();
};

template <typename T>
std::tr1::shared_ptr<T> Singlton<T>::s_instance;

template <typename T>
Singlton<T>::Singlton() {
    cout << "construct singlton" << endl;
}

template <typename T>
T* Singlton<T>::instance() {
    if (!s_instance.get())
        s_instance.reset(new T);
    return s_instance.get();
}

#endif