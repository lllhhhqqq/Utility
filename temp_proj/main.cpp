#include <iostream>

//#include "SingltonT.h"
//#include "rwlock.h"
//#include "lru_cache.h"
//
//#include <memory>
//
//using namespace std;
//
//using namespace lru_cache;
//class DZCache : public Singlton < DZCache >
//{
//    friend  class Singlton < DZCache > ;
//private:
//    shared_ptr<CLRUCache> clu_cache;
//    rwlock *lock;
//    DZCache(){
//        lock = (rwlock*)malloc(sizeof(rwlock));
//        rwlock_init(lock);
//        clu_cache = shared_ptr<CLRUCache>(new CLRUCache());
//        cout << "construct JobList" << endl;
//    }
//
//    DZCache * Instance() {
//        return s_instance.get();
//    }
//
//public:
//
//    ~DZCache(){
//        free(lock);
//    }
//
//    static DZCache& getInstance(){
//        return *instance();
//    }
//
//    void set(NSString* key, id value){
//        //加锁
//        rwlock_wlock(lock);
//        HashKey hash_key;
//        hash_key.key = key;
//        clu_cache->set(hash_key, value);
//        rwlock_wunlock(lock);
//    }
//
//    id get(NSString* key){
//        HashKey hash_key;
//        hash_key.key = key;
//        HashValue* value = clu_cache->get(hash_key);
//        if (value == NULL){
//            return nil;
//        }
//        else{
//            return value->value_;
//        }
//    }
//};
//
//void testLRUCache(){
//    //指针方式
//    DZCache::instance()->set(@"name", @"daizhj");//设置
//    NSString* name = (NSString*)DZCache::instance()->get(@"name");//获取
//    std::cout << [name UTF8String] << endl;
//
//    NSNumber * age = [NSNumber numberWithInt : 123123];
//    DZCache::instance()->set(@"age", age);
//    age = (NSNumber*)DZCache::instance()->get(@"age");
//
//    //对象方式
//    DZCache::getInstance().set(@"name", @"daizhenjun");
//    name = (NSString*)DZCache::getInstance().get(@"name");
//    std::cout << [name UTF8String] << endl;
//
//    age = [NSNumber numberWithInt : 123456];
//    DZCache::getInstance().set(@"age", age);
//    age = (NSNumber*)DZCache::getInstance().get(@"age");
//}


int main(int argc, char ** argv)
{
    return 0;
}