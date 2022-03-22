#pragma once

#include <pthread.h>

class spin_lock {
public:
    spin_lock() { 
        pthread_spin_init(&lock_, 0);
    }
    ~spin_lock() {
        pthread_spin_destroy(&lock_);
    }
    spin_lock(const spin_lock&) = delete;

    void lock() {
        pthread_spin_lock(&lock_);
    }
    void unlock() {
        pthread_spin_unlock(&lock_);
    }

private:
    pthread_spinlock_t lock_;
};
