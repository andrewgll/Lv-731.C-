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

void writeToFile(CommentStatisticsMap& map, const std::vector<std::string> files, const std::string& path)
{
	std::ofstream os(path, std::ios_base::out);
	os << "===== Total:\n";
	os << map.total(files) << std::endl;
	for (auto const& file : files)
	{
		os << "==== File: " << file << std::endl;
		os << map.getFileStat(file);
	}
	os << std::flush;
	os.close();
	std::cout << "File was saved to " << path << std::endl;
}
