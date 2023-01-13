// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_COMMENT_STAT_H_
#define _KLEPATSKYI_COMMENT_STAT_H_

#include "FileCommentStat.h"

#include <string>
#include <vector>

class Parser;

class CommentCounter {
private:
	Parser* const _parser;
	FileCommentStat _fileStat;
	bool _lineHasComment;
	bool _lineHasCode;
	char _cursor;
public:
	CommentCounter(const std::vector<std::string>& lines);
	~CommentCounter();

	FileCommentStat start();

	CommentCounter(const CommentCounter&) = delete;
	CommentCounter& operator=(const CommentCounter&) = delete;
private:
	bool parseLine();
	bool parseComment();
	void parseOneLineComment();
	void parseMultilineComment();
	void countLine();
	void parseLiteral(char parens);
};

#endif
