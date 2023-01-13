// by Klepatskyi Oleh
#include "CommentStatisticsMap.h"

#include "ConcurrentUnorderedMap.h"
#include <mutex>

class CommentStatisticsMap::CommentStatisticsMapImpl {
private:
	ConcurrentUnorderedMap<std::string, FileCommentStat> _map;
public:
	inline void addRecord(const std::string& filename, const FileCommentStat& stat)
	{
		_map.insert(filename, stat);
	}

	inline const FileCommentStat& getFileStat(const std::string& path)
	{
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