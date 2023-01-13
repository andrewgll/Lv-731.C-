// by Klepatskyi Oleh
#include "CommentStatisticsMap.h"

#include <unordered_map>
#include <mutex>

class CommentStatisticsMap::CommentStatisticsMapImpl {
private:
	std::unordered_map<std::string, FileCommentStat> _map;
	std::mutex _mutex;
public:
	inline void addRecord(const std::string& filename, const FileCommentStat& stat)
	{
		std::lock_guard<std::mutex> lg(_mutex);
		_map.insert({ filename, stat });
	}

	inline const FileCommentStat& getFileStat(const std::string& path)
	{
		std::lock_guard<std::mutex> lg(_mutex);
		return _map.at(path);
	}
};

CommentStatisticsMap::CommentStatisticsMap()
	: _impl(new CommentStatisticsMapImpl())
{}

CommentStatisticsMap::~CommentStatisticsMap()
{
	delete _impl;
}

void CommentStatisticsMap::addRecord(const std::string& filename, const FileCommentStat& stat)
{
	return _impl->addRecord(filename, stat);
}

const FileCommentStat& CommentStatisticsMap::getFileStat(const std::string& path)
{
	return _impl->getFileStat(path);
}