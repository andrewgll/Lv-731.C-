// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_FILE_COMMENT_STAT_H
#define _KLEPATSKYI_FILE_COMMENT_STAT_H

#include <iostream>

struct FileCommentStat {
	size_t blank_lines = 0;
	size_t code_lines = 0;
	size_t comment_lines = 0;
	size_t code_with_comments_lines = 0;

	size_t blank() const { return blank_lines; }
	size_t code() const { return code_lines; }
	size_t comment() const { return comment_lines; }
	size_t codeWithComment() const { return code_with_comments_lines; }
	size_t total() const { return blank_lines + code_lines + comment_lines + code_with_comments_lines; }
};

inline bool operator==(const FileCommentStat& lhs, const FileCommentStat& rhs)
{
	return lhs.blank_lines == rhs.blank_lines &&
		lhs.code_lines == rhs.code_lines &&
		lhs.comment_lines == rhs.comment_lines &&
		lhs.code_with_comments_lines == rhs.code_with_comments_lines;
}

inline std::ostream& operator<<(std::ostream& os, const FileCommentStat& stat)
{
	os << "blank: " << stat.blank() << "\n"
	 << "code: " << stat.code() << "\n"
	 << "comment: " << stat.comment() << "\n"
	 << "code with comment: " << stat.comment() << "\n"
	 << "total: " << stat.total() << "\n";
	return os;
}



#endif
