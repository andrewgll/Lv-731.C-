#include <iostream>
#include "PathToFolder.h"
#include "AllStatistics.h"
#include "FileAnalysis.h"
#include "ThreadPool.h"


int main()
{
	ThreadPool thread_pool;
	std::vector<std::thread> threads;
	thread_pool.pushThreads(thread_pool, threads);

	PathToFolder path;
	path.getPathToFilesFromDirectory();
	AllStatistics statistics;

	//for (const auto& file : path.m_path_to_files)
	//	statistics.addStatisticsFromAnalysis(Analysis(file));

	for (int i = 0; i < path.m_path_to_files.size(); i++)
	{
		thread_pool.push([](std::string* file, AllStatistics* statistics)
			{
				statistics->addStatisticsFromAnalysis(Analysis(*file));
			}, &path.m_path_to_files[i], &statistics);
	}

	thread_pool.done();
	thread_pool.wait(threads);
	statistics.write(statistics, path);

	return 0;
}