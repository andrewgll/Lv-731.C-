// by Klepatskyi Oleh
#include "CommentStatCore.h"
#include "CommentStat.h"
#include "Parser.h"
#include "FileFilter.h"

#ifndef _NDEBUG
#include "Timer.h"
#endif // _NDEBUG

#include <future>
#include <iostream>

void addFileStat(CommentStatisticsMap& map, const std::string& file)
{
	std::vector<std::string> lines = getFileLines(file.c_str());
	CommentCounter counter(lines);
	FileCommentStat stat = counter.start();
	map.addRecord(file, stat);
}

void getCommentStatAsync(CommentStatisticsMap& map, const std::vector<std::string>& files)
{
	std::vector<std::future<void>> futures;

	for (auto& const path : files)
	{
		Timer t;
		t.stop();
		auto f = std::async(std::launch::async,
			addFileStat,
			std::ref(map),
			std::ref(path));

		futures.push_back(std::move(f));
	}

	for (auto& f : futures)
	{
		f.wait();
	}

	for (auto const& file : files)
	{
		const FileCommentStat& stat = map.getFileStat(file);
		std::cout << file << " ============\n";
		std::cout << stat << "\n";
	}
}

void getCommentStat(CommentStatisticsMap& map, const std::vector<std::string>& files)
{
	for (auto& const path : files)
	{
		Timer t;
		t.stop();
		addFileStat(map, path);
	}
}

void printStat(CommentStatisticsMap& map, const std::vector<std::string> files)
{
	for (auto const& file : files)
	{
		const FileCommentStat& stat = map.getFileStat(file);
		std::cout << file << " ============\n";
		std::cout << stat << "\n";
	}
}