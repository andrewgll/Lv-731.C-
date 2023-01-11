#pragma once
#include <iostream>
#include <mutex>
#include "PathToFolder.h"
#include <chrono>

struct FileAnalysis
{
	size_t blank_lines = 0;
	size_t comment_lines = 0;
	size_t code_lines = 0;
};

class AllStatistics
{
public:
	AllStatistics() { m_start = std::chrono::high_resolution_clock::now(); }
	void addStatisticsFromAnalysis(const FileAnalysis& analysis);
	void write(const AllStatistics& statistics, const PathToFolder& path);
	friend std::ofstream& operator<<(std::ofstream& os, const AllStatistics& statistics);

private:
	std::mutex m_lock;
	std::chrono::time_point<std::chrono::steady_clock> m_start, m_end;
	float m_time;
	size_t m_blank_lines = 0;
	size_t m_comment_lines = 0;
	size_t m_code_lines = 0;
	size_t m_total_files = 0;
};