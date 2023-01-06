#include "ThreadPool.h"

void ThreadPool::pushThreads(ThreadPool& thread_pool, std::vector<std::thread>& threads)
{
	int num_threads = std::thread::hardware_concurrency() - 2;
	for (int i = 0; i < num_threads; i++)
	{
		threads.push_back(std::thread(&ThreadPool::infiniteLoopFunc, &thread_pool));
	}
}

void ThreadPool::push(std::function<void(std::string*, AllStatistics*)> func,
	std::string* file, AllStatistics* statistics)
{
	std::unique_lock<std::mutex> lock(m_lock);
	std::pair<std::string*, AllStatistics*> data{ file, statistics };
	std::pair<std::pair <std::string*, AllStatistics*>, std::function <void(std::string*, AllStatistics*)>> temp{ data, func };

	m_function_queue.push(temp);
	// when we send the nofification immediately, the consumer will try to get the lock, so unlock asap
	lock.unlock();
	m_data_condition.notify_one();
}

void ThreadPool::done()
{
	std::unique_lock<std::mutex> lock(m_lock);
	m_accept_functions = false;
	lock.unlock();
	// when we send the notification immediately, the consumer will try to get the lock , so unlock asap
	m_data_condition.notify_all();
	//notify all waiting threads.
}

void ThreadPool::wait(std::vector<std::thread>& threads)
{
	for (unsigned int i = 0; i < threads.size(); i++)
	{
		threads.at(i).join();
	}
}

void ThreadPool::infiniteLoopFunc()
{
	std::function<void(std::string*, AllStatistics*)> func;
	std::string* file;
	AllStatistics* statistics;

	while (true)
	{
		std::unique_lock<std::mutex> lock(m_lock);
		m_data_condition.wait(lock, [this]() {return !m_function_queue.empty() || !m_accept_functions; });
		if (!m_accept_functions && m_function_queue.empty())
		{
			//lock will be release automatically.
			//finish the thread loop and let it join in the main thread.
			return;
		}
		auto data = m_function_queue.front();
		m_function_queue.pop();
		func = data.second;
		file = data.first.first;
		statistics = data.first.second;
		//release the lock
		func(file, statistics);
	}
}