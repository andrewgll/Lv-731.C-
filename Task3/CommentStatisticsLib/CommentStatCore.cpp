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
	TimerMicro t;
	try {
		std::vector<std::string> lines = getFileLines(file.c_str());
		CommentCounter counter(lines);
		FileCommentStat stat = counter.start();
		stat.execution_time = t.stop();
		map.addRecord(file, stat);
	}
	catch (const std::exception& ex)
	{
		FileCommentStat stat;
		stat.setErrMsg(ex.what());
		stat.execution_time = t.stop();
		map.addRecord(file, stat);
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

void write(std::ostream& os, CommentStatisticsMap& map, const std::vector<std::string> files, std::time_t exectime)
{
	os << "===== Total:\n";
	os << "Files : " << map.size() << std::endl;
	FileCommentStat total = map.total(files);
	// if we have done process in async way, sum will be the total thread time, as if we executed it sequencially
	total.execution_time = exectime;
	os << total << std::endl;
	for (auto const& file : files)
	{
		os << "==== File: " << file << std::endl;
		os << map.getFileStat(file);
	}
}
