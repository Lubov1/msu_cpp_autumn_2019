#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <iostream>
#include <queue>
#include <thread>

#include <cstddef>
#include "Threads.h"
using Task = std::function<void()>;


Threads::~Threads(){
	working = false;
	var.notify_all();
	for (auto& thread : all_threads)
		thread.join();
}
Threads::Threads(size_t poolSize): working(true){
	for (size_t i = 0; i < poolSize; ++i){
		all_threads.emplace_back(
			[this](){
			while(working){
				std::unique_lock<std::mutex> lock(mutex_);
				if(!tasks.empty()){
					auto task = tasks.front();
					tasks.pop();
					lock.unlock();
					task();
				}
				else{
					var.wait(lock);
				}
			}
		});
	}
}