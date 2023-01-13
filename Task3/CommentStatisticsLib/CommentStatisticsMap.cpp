// by Klepatskyi Oleh
#include "CommentStatisticsMap.h"
#include "ConcurrentUnorderedMap.h"

#include <mutex>
#include <fstream>

class CommentStatisticsMap::CommentStatisticsMapImpl {
private:
	ConcurrentUnorderedMap<std::string, FileCommentStat> _map;
public:
	inline void addRecord(const std::string& filename, const FileCommentStat& stat)
	{
		_map.insert(filename, stat);
	}

	inline const FileCommentStat& getFileStat(const std::string& path) const
	{
		return _map.at(path);
	}

	inline FileCommentStat total(const std::vector<std::string> files) const
	{
		FileCommentStat sum;
		for (auto const& file : files)
		{
			sum = sum + _map.at(file);
		}
		return sum;
	}

	inline size_t size() const
	{
		return _map.size();
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

const FileCommentStat& CommentStatisticsMap::getFileStat(const std::string& path) const
{
	return _impl->getFileStat(path);
}

FileCommentStat CommentStatisticsMap::total(const std::vector<std::string> files) const
{
	return _impl->total(files);
}

size_t CommentStatisticsMap::size() const
{
	return _impl->size();
}
