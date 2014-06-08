#ifndef _MAP_LRU_CACHE_H_
#define _MAP_LRU_CACHE_H_

#include <string.h>
#include <iostream>
#include "rwlock.h"
#include <stdio.h>
//#include <sys/malloc.h>
using namespace std;

namespace lru_cache {

    static const int DEF_CAPACITY = 100000;//默认缓存记录数

    typedef unsigned long long virtual_time;

    typedef struct _HashKey
    {
        NSString* key;
    }HashKey;

    typedef struct _HashValue
    {
        id value_;
        virtual_time access_;
    }HashValue;

    //仅针对HashKey比较器
    template <class key_t>
    struct hashkey_compare{
        bool operator()(key_t x, key_t y) const{
            return x < y;
        }
    };

    template <>
    struct hashkey_compare < HashKey >
    {
        bool operator()(HashKey __x, HashKey __y) const{
            string x = [__x.key UTF8String];
            string y = [__y.key UTF8String];
            return x < y;
        }
    };

    //自定义map类型
    template <typename K, typename V, typename _Compare = hashkey_compare<K>,
        typename _Alloc = std::allocator<std::pair<const K, V> > >
    class  lru_map : public map < K, V, _Compare, _Alloc > {};

    class CLRUCache
    {
    public:

        CLRUCache() : _now(0){
            _lru_list = shared_ptr<lru_map<virtual_time, HashKey> >(new lru_map<virtual_time, HashKey>);
            _hash_table = shared_ptr<lru_map<HashKey, HashValue> >(new lru_map<HashKey, HashValue>);
        }

        ~CLRUCache(){
            _lru_list->clear();
            _hash_table->clear();
        }

        int set(const HashKey& key, const id &value)
        {
            HashValue hash_value;
            hash_value.value_ = value;
            hash_value.access_ = get_virtual_time();
            pair< map<HashKey, HashValue>::iterator, bool > ret = _hash_table->insert(make_pair(key, hash_value));
            if (!ret.second){
                // key already exist
                virtual_time old_access = (*_hash_table)[key].access_;
                map<virtual_time, HashKey>::iterator iter = _lru_list->find(old_access);
                if (iter != _lru_list->end())
                {
                    _lru_list->erase(iter);
                }
                _lru_list->insert(make_pair(hash_value.access_, key));
                (*_hash_table)[key] = hash_value;
            }
            else {
                _lru_list->insert(make_pair(hash_value.access_, key));

                if (_hash_table->size() > DEF_CAPACITY)
                {
                    // get the least recently used key
                    map<virtual_time, HashKey>::iterator iter = _lru_list->begin();
                    _hash_table->erase(iter->second);
                    // remove last key from list
                    _lru_list->erase(iter);
                }
            }
            return 0;
        }

        HashValue* get(const HashKey& key)
        {
            map<HashKey, HashValue>::iterator iter = _hash_table->find(key);
            if (iter != _hash_table->end())
            {
                virtual_time old_access = iter->second.access_;
                iter->second.access_ = get_virtual_time();
                //调整当前key在LRU列表中的位置
                map<virtual_time, HashKey>::iterator it = _lru_list->find(old_access);
                if (it != _lru_list->end()) {
                    _lru_list->erase(it);
                }
                _lru_list->insert(make_pair(iter->second.access_, key));
                return &(iter->second);
            }
            else{
                return NULL;
            }
        }


        unsigned get_lru_list_size(){ return (unsigned)_lru_list->size(); }
        unsigned get_hash_table_size() { return (unsigned)_hash_table->size(); }
        virtual_time get_now() { return _now; }

    private:
        virtual_time get_virtual_time()
        {
            return ++_now;
        }

        shared_ptr<lru_map<virtual_time, HashKey> >    _lru_list;
        shared_ptr<lru_map<HashKey, HashValue> > _hash_table;
        virtual_time _now;
    };

#endif