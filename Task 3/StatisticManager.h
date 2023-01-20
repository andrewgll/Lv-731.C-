#pragma once
#include <iostream>
#include <mutex>
#include <chrono>
#include "RootFolder.h"

using namespace std;

struct Lines {
	size_t blank_lines = 0;
	size_t code_lines = 0;
	size_t comment_lines = 0;
};

class StatisticManager {
private:
	mutex mtx;
	chrono::time_point<chrono::steady_clock> begin, end;
	double time;
	size_t sm_blank_lines = 0;
	size_t sm_code_lines = 0;
	size_t sm_comment_lines = 0;
	size_t sm_num_files = 0;


public:
	StatisticManager() {
		begin = chrono::high_resolution_clock::now();
	}

	void AnalyseLines(const Lines& lines);
	void FileWriter(const StatisticManager& statistics, const RootFolder& root);
	void ConsoleWriter(const StatisticManager& statistics);
};