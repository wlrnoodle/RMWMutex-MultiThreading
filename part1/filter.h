#pragma once

#include <atomic>
#include<memory>
#include<thread>
class mutex {
    private:
	// Give me some private variables!
	int n;
	std::unique_ptr<std::atomic<int>[]> level;
	std::unique_ptr<std::atomic<int>[]> victim;
	
	//true of there exists k !- me with level[k] >= i
	bool exist_conflict (int thread_id , int i ){
		for( int k = 0; k < n; k++){
			if (k != thread_id && level[k].load() >= i){
                 return true;                  
			}
		}
        return false;
	}
	public:
	mutex() {
        // constructor
		// keep empty or have it set n = 0.
        n = 0;

	}
	
	void init (int num_threads) {
		// Implement me!
        // make_unique : malloc (n * size of ( someshit))
        n = num_threads;
        level = std::make_unique<std::atomic<int>[]>(n);
        victim = std::make_unique<std::atomic<int>[]>(n); // uses 1 .. n-1 

        for(int i = 0; i < num_threads; i++){
            level[i].store(0);
            victim[i].store(0); // java verison doesnt but cuz its not mem safe
        }
	}
	
	void lock(int thread_id) {
		// Implement me!
		for (int i = 1; i < n ; i++){
            level[thread_id].store(i);
            victim[i].store(thread_id);

            //spin while conflicts exist
            while(exist_conflict(thread_id, i) && victim[i].load() == thread_id){std::this_thread::yield();}
        }
	}
	
	void unlock(int thread_id) {
		// Implement me!
        level[thread_id].store(0);
	}
};

