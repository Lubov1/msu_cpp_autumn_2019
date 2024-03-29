#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <iostream>
#include <queue>
#include <thread>

#include <cstddef>
using Task = std::function<void()>;


class Threads
{
	std::atomic<bool> working;
	std::queue<Task> tasks;

	std::condition_variable var;
	std::vector<std::thread> all_threads;
	std::mutex mutex_;

public:
	explicit Threads(size_t poolSize);
	template <class Func, class... Args>
	auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
		using ReturnType = decltype(func(args...));
		using PackagedType = std::packaged_task<ReturnType ()>;
		auto task = std::make_shared<PackagedType>([func, args...](){
			return func(args...);
		});
		{
			std::lock_guard<std::mutex> lock(mutex_);
			tasks.emplace(
					[task]() {
						(*task)();
					});
		}
		var.notify_one();
		return task->get_future();
	}
	~Threads();

};
