// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_COMMENT_STATISTICS_MAP_H_
#define _KLEPATSKYI_COMMENT_STATISTICS_MAP_H_

#include "CommentStat.h"
#include <string>

class CommentStatisticsMap {
private:
	class CommentStatisticsMapImpl;
	CommentStatisticsMapImpl* const _impl;
public:
	CommentStatisticsMap();
	~CommentStatisticsMap();
	CommentStatisticsMap(const CommentStatisticsMap&) = delete;
	CommentStatisticsMap& operator=(const CommentStatisticsMap&) = delete;

	void addRecord(const std::string& filename, const FileCommentStat& stat);
	const FileCommentStat& getFileStat(const std::string& path);
};

#endif // _KLEPATSKYI_COMMENT_STATISTICS_MAP_H_
