// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_COMMENT_STAT_H_
#define _KLEPATSKYI_COMMENT_STAT_H_
#include "Parser.h"

#include <unordered_map>
#include <string>
#include <mutex>

struct FileCommentStat {
	size_t blank_lines = 0;
	size_t code_lines = 0;
	size_t comment_lines = 0;
};

class CommentStatistics {	
private:
	std::unordered_map<std::string, FileCommentStat> _map;
	std::mutex _mutex;
public:
	CommentStatistics() = default;

	inline void addRecord(const char* filename, const FileCommentStat& stat)
	{
		std::lock_guard<std::mutex> lg(_mutex);
		_map.insert({ filename, stat });
	}

	// todo add statistics methods
};

class Parser;

class CommentCounter {
private:
	Parser* const _parser;
	FileCommentStat& _fileStat;
	bool _lineHasComment;
	bool _lineHasCode;
public:
	CommentCounter(const char* filename, FileCommentStat& fileStat);
	~CommentCounter();
	CommentCounter(const CommentCounter&) = delete;
	CommentCounter& operator=(const CommentCounter&) = delete;
private:
	void parseLineFromStart();
	void parseLine();
	char parseComment();
	void parseOneLineComment();
	char parseMultilineComment();
	void assignComment();
	void assignCode();
};

#endif
