// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_FILE_COMMENT_STAT_H
#define _KLEPATSKYI_FILE_COMMENT_STAT_H

#include <iostream>

class FileCommentStat {
public:
	size_t blank_lines = 0;
	size_t code_lines = 0;
	size_t comment_lines = 0;
	size_t code_with_comments_lines = 0;
	std::time_t execution_time = 0;
	char* err_msg = nullptr;

	FileCommentStat() = default;
	
	FileCommentStat(size_t blank, size_t code, size_t comment, size_t code_comment) :
		blank_lines(blank),
		code_lines(code),
		comment_lines(comment),
		code_with_comments_lines(code_comment),
		err_msg(nullptr),
		execution_time(0)
	{}

	FileCommentStat(size_t blank, size_t code, size_t comment, size_t code_comment, std::time_t time) :
		blank_lines(blank),
		code_lines(code),
		comment_lines(comment),
		code_with_comments_lines(code_comment),
		err_msg(nullptr),
		execution_time(time)
	{}

	~FileCommentStat()
	{
		delete err_msg;
	}

	FileCommentStat(const FileCommentStat& other):
		blank_lines(other.blank_lines),
		code_lines(other.code_lines),
		comment_lines(other.comment_lines),
		code_with_comments_lines(other.code_with_comments_lines),
		execution_time(other.execution_time),
		err_msg(nullptr)
	{
		if (other.err_msg != nullptr)
		{
			size_t size = strlen(other.err_msg) + 1;
			err_msg = new char[size];
			strcpy_s(err_msg, size, other.err_msg);
		}
	}

	FileCommentStat& operator=(const FileCommentStat& other)
	{
		if (this == &other)
			return *this;
		blank_lines = other.blank_lines;
		code_lines = other.code_lines;
		comment_lines = other.comment_lines;
		code_with_comments_lines = other.code_with_comments_lines;
		execution_time = other.execution_time;
		if (other.err_msg != nullptr)
		{
			copyErrMsg(other.err_msg);
		}
		return *this;
	}

	void setErrMsg(const char* str)
	{
		copyErrMsg(str);
	}

	size_t blank() const { return blank_lines; }
	size_t code() const { return code_lines; }
	size_t comment() const { return comment_lines; }
	size_t codeWithComment() const { return code_with_comments_lines; }
	size_t total() const { return blank_lines + code_lines + comment_lines + code_with_comments_lines; }
	char* error() { return err_msg; }

private:
	inline void copyErrMsg(const char* str)
	{
		delete err_msg;
		size_t size = strlen(str) + 1;
		err_msg = new char[size];
		strcpy_s(err_msg, size, str);
	}
};

// used for testing results of algorithm
inline bool operator==(const FileCommentStat& lhs, const FileCommentStat& rhs)
{
	return lhs.blank_lines == rhs.blank_lines &&
		lhs.code_lines == rhs.code_lines &&
		lhs.comment_lines == rhs.comment_lines &&
		lhs.code_with_comments_lines == rhs.code_with_comments_lines;
}

inline FileCommentStat operator+(const FileCommentStat& lhs, const FileCommentStat& rhs)
{
	return {
		lhs.blank_lines + rhs.blank_lines,
		lhs.code_lines + rhs.code_lines,
		lhs.comment_lines + rhs.comment_lines,
		lhs.code_with_comments_lines + rhs.code_with_comments_lines,
		lhs.execution_time + rhs.execution_time
	};
}

inline std::ostream& operator<<(std::ostream& os, const FileCommentStat& stat)
{
	if (stat.err_msg == nullptr)
	{
		os  << "blank lines:             " << stat.blank() << "\n"
			<< "code lines:              " << stat.code() << "\n"
			<< "comment lines:           " << stat.comment() << "\n"
			<< "code with comment lines: " << stat.codeWithComment() << "\n"
			<< "total number of lines:   " << stat.total() << "\n";
	}
	else
	{
		os  << "Error:                   " << stat.err_msg << std::endl;
	}
	os      << "Execution time:          " << stat.execution_time / 1000.0 << " ms\n" << std::endl;
	return os;
};

#endif
