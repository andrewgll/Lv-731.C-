// by Klepatskyi Oleh
#include "CommentStatCore.h"
#include "CommentStat.h"
#include "Parser.h"
#include "Timer.h"
#include "FileUtil.h"

#include <future>
#include <iostream>

void addFileStat(CommentStatisticsMap& map, const std::string& file)
{
	Timer t;
	try {
		std::vector<std::string> lines = getFileLines(file.c_str());
		CommentCounter counter(lines);
		FileCommentStat stat = counter.start();
		map.addRecord(file, stat);
	}
	catch (const std::exception& ex)
	{
		FileCommentStat s;
		s.setErrMsg(ex.what());
		map.addRecord(file, s);
	}
}

void getCommentStatAsync(CommentStatisticsMap& map, const std::vector<std::string>& files)
{
	std::vector<std::future<void>> futures;

	for (auto const& path : files)
	{
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
}

void getCommentStat(CommentStatisticsMap& map, const std::vector<std::string>& files)
{
	for (auto const& path : files)
	{
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
	std::cout << "Total: =====\n";
	std::cout << map.total(files) << std::endl;
}