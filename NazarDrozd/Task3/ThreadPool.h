#pragma once
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>
#include "AllStatistics.h"
		  
class ThreadPool
{
public:
	ThreadPool()
		: m_function_queue(), m_lock(), m_data_condition(), m_accept_functions(true) {}
	~ThreadPool() {}

	void pushThreads(ThreadPool& thread_pool, std::vector<std::thread>& threads);
	void push(std::function<void(std::string*, AllStatistics*)> func,
		std::string* file, AllStatistics* statistics);
	void done();
	void wait(std::vector<std::thread>& threads);
	void infiniteLoopFunc();
private:
	std::queue<std::pair<std::pair<std::string*, AllStatistics*>,
		std::function<void(std::string*, AllStatistics*)>>> m_function_queue;
	std::mutex m_lock;
	std::condition_variable m_data_condition;
	std::atomic<bool> m_accept_functions;
};