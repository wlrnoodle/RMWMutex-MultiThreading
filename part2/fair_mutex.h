#pragma once

#include <atomic>
#include <mutex>
using namespace std;

/*
Note: You may not use any other synchronization primitives (e.g., semaphores, condition variables, etc.) in your implementation of this class. You may only use the C++ standard library's atomic operations and mutexes.

Note: As well as the .h files used in thsi c++ programming standard they dont do it like in c .h , where they act like as a template in c++ they are more like a class and can be used as a class in the main program.
Weird huh.S
*/ 

class rw_mutex {
    public:
    rw_mutex() {
        writer = false;
        num_readers = 0;
        num_writers = 0;
    }
    
    void lock_reader() {
        bool acquired = false;
        while (!acquired) {
            internal_mutex.lock();
            if (num_writers == 0 && !writer) {
                num_readers++;
                acquired = true;
            }
            internal_mutex.unlock();
        }
    }
    
    void unlock_reader() {
        internal_mutex.lock();
        num_readers--;
        internal_mutex.unlock();
    }
    
    
    void lock() {
        internal_mutex.lock();
        num_writers++;
        internal_mutex.unlock();

        bool acquired = false;
        while(!acquired){
            internal_mutex.lock();
            if (!writer && num_readers == 0){
                acquired = true;
                writer = true;
                num_writers--;
            }
            internal_mutex.unlock();
        }
    }
    
    void unlock() {
        // Implement me!
        internal_mutex.lock();
        writer = false;
        internal_mutex.unlock();
    }
    
    private:
    // Give me some private variables!
    mutex internal_mutex;
    bool writer = false;
    int num_readers;
    int num_writers;
    
};
