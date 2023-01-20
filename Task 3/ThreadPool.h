#pragma once
#include <iostream>
#include <mutex>
#include <queue>
#include <vector>
#include <functional>
#include "StatisticManager.h"

using namespace std;

class ThreadPool {
private:
	void ThreadLoop();

	bool should_terminate = true;
	mutex queue_mutex;
	condition_variable mutex_condition;
	
	queue<pair<pair<string*, StatisticManager*>,
		function<void(string*, StatisticManager*)>>> jobs;

public:
	void Start(ThreadPool& thread_pool, vector<thread>& threads);
	void QueueJob(function<void(string*, StatisticManager*)> func,
		string* file, StatisticManager* statistics);
	void Stop();
	void busy(vector<thread>& threads);
};