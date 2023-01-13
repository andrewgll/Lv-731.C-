// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_COMMENT_STAT_CORE_H_
#define _KLEPATSKYI_COMMENT_STAT_CORE_H_

#include "CommentStatisticsMap.h"

#include <string>

void addFileStat(CommentStatisticsMap& map, const std::string& file);

void getCommentStatAsync(CommentStatisticsMap& map, const std::vector<std::string>& files);

void getCommentStat(CommentStatisticsMap& map, const std::vector<std::string>& files);

void write(std::ostream& os, CommentStatisticsMap& map, const std::vector<std::string> files, std::time_t exectime);

#endif // _KLEPATSKYI_COMMENT_STAT_CORE_H_
