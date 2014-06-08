#ifndef _RWLOCK_H_
#define _RWLOCK_H_

#define LOCK(q) while (__sync_lock_test_and_set(&(q)->lock,1)) {}
#define UNLOCK(q) __sync_lock_release(&(q)->lock);

struct rwlock {
    int write;
    int read;
};

static inline void
rwlock_init(struct rwlock *lock) {
    lock->write = 0;
    lock->read = 0;
}

static inline void
rwlock_rlock(struct rwlock *lock) {
    for (;;) {//����ѭ����ֱ���Զ��������ۼӳɹ�
        while (lock->write) {
            //__sync_synchronize();
        }
        //__sync_add_and_fetch(&lock->read, 1);
        if (lock->write) {//������д��ʱ����ȥ������������
            //__sync_sub_and_fetch(&lock->read, 1);
        }
        else {
            break;
        }
    }
}

static inline void
rwlock_wlock(struct rwlock *lock) {
    //__sync_lock_test_and_set(&lock->write, 1); 
    while (lock->read) {
        //http://blog.itmem.com/?m=201204
        //http://gcc.gnu.org/onlinedocs/gcc-4.6.2/gcc/Atomic-Builtins.html
        //__sync_synchronize();//����Ҫ�����ȥ����g++ -O3 �Ż����������ɵĳ�����������
    }
}

static inline void
rwlock_wunlock(struct rwlock *lock) {
    //__sync_lock_release(&lock->write);
}

static inline void
rwlock_runlock(struct rwlock *lock) {
    //__sync_sub_and_fetch(&lock->read, 1);
}

#endif