#pragma once

#include <atomic>
#include <memory>
#include <thread>

class mutex {
    public:
    mutex() {
        // Implement me!
        n = 0; //prevent garabage values
    }
    
    void init (int num_threads) {
        // Implement me!
        n = num_threads;
        flag = std::make_unique<std::atomic<bool>[]>(n);
        label = std::make_unique<std::atomic<int>[]>(n); //malloc (n * sizeof(atomic(int)array))
        for (int i = 0; i < n; i++){
            flag[i].store(false);
            label[i].store(0);
        }
    }
    
    void lock(int thread_id) {
        // Implement me!
        flag[thread_id].store(true);
        int max_label = 0;

        //label[i] = max(label[0] .... label[n-1]) + 1
        for (int i = 0; i < n; i++){
            int l = label[i].load();
            if (l > max_label){
                max_label = l;
            }
        }
        label[thread_id].store(max_label + 1);
        //wait while there exist a k that may be bigger (2.4)
        // Note: where we compare if a ticket who has the same label which one was first , in the bakery algo
        for(int k = 0; k < n; k++){
            if (k == thread_id) continue;

            while(flag[k].load()){
                int lk = label[k].load();
                int li = label[thread_id].load();

                //compare if lk , k << ik , thread_id
                bool kAhead = (lk < li) || (lk == li && k < thread_id);
                if(!kAhead){break;} //if k is behind stop waiting on k  
                std::this_thread::yield();
            }
        }
    }
    
    void unlock(int thread_id) {
        // Implement me!
        flag[thread_id].store(false);
    }
    private:
    // Vars: flag(true) thread is being used, flag(false) thread is not being used.
    int n;
    std::unique_ptr<std::atomic<int>[]> label;
    std::unique_ptr<std::atomic<bool>[]> flag;
};