#include "ThreadPool.h"

void ThreadPool::ThreadLoop() {
	function<void(std::string*, StatisticManager*)> job;
	string* file;
	StatisticManager* statistics;

	while (true) {
		unique_lock<mutex> lock(queue_mutex);
		mutex_condition.wait(lock, [this]() {
			return !jobs.empty() || !should_terminate;
			});
		if (!should_terminate && jobs.empty()) {
			return;
		}
		auto data = jobs.front();
		jobs.pop();
		job = data.second;
		file = data.first.first;
		statistics = data.first.second;
		job(file, statistics);
	}
}

void ThreadPool::Start(ThreadPool& thread_pool, std::vector<std::thread>& threads) {
	const int num_threads = thread::hardware_concurrency() - 2;

	for (int i = 0; i < num_threads; i++) {
		threads.push_back(thread(&ThreadPool::ThreadLoop, &thread_pool));
	}
}

void ThreadPool::QueueJob(const function<void(string*, StatisticManager*)> func,
	string* file, StatisticManager* statistics) {
	unique_lock<mutex> lock(queue_mutex);
	pair<string*, StatisticManager*> data {
		file, statistics 
	};
	pair<pair <string*, StatisticManager*>, function <void(string*, StatisticManager*)>> temp {
		data, func
	};
	jobs.push(temp);
	lock.unlock();
	mutex_condition.notify_one();
}

void ThreadPool::Stop() {
	std::unique_lock<std::mutex> lock(queue_mutex);
	should_terminate = false;
	lock.unlock();
	mutex_condition.notify_all();
}

void ThreadPool::busy(vector<thread>& threads) {
	for (auto i = 0; i < threads.size(); i++) {
		threads[i].join();
	}
}