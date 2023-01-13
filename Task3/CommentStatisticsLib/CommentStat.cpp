// by Klepatskyi Oleh

#include "CommentStat.h"
#include "Parser.h"

CommentCounter::CommentCounter(const std::vector<std::string>& lines)
	: _parser(new Parser(lines)), _fileStat()
{}

CommentCounter::~CommentCounter()
{
	delete _parser;
}

FileCommentStat CommentCounter::start()
{
	_parser->start();
	_lineHasCode = false;
	_lineHasComment = false;
	while (parseLine());
	return _fileStat;
}

bool CommentCounter::parseLine()
{
	bool hasSkippedChar = false;
	_cursor = _parser->skipBlank();
	while (_cursor != END_OF_LINE)
	{
		if (_cursor == END_OF_FILE)
		{
			return false;
		}
		
		if (_cursor == '/')
		{
			hasSkippedChar = parseComment();
		}
		else
		{
			_lineHasCode = true;
			if (_cursor == '\"' || _cursor == '\'')
			{
				parseLiteral(_cursor);
			}
		}
		if (!hasSkippedChar)
		{
			_cursor = _parser->skipBlank();
		}
		else
		{
			_cursor = _parser->current();
		}
		hasSkippedChar = false;
	}
	countLine();
	return true;
}

bool CommentCounter::parseComment()
{
	_cursor = _parser->next();
	if (_cursor == '/')
	{
		parseOneLineComment();
		return true;
	}

	if (_cursor == '*')
	{
		parseMultilineComment();
		return false;
	}

	_lineHasCode = true;
	return true;
}

void CommentCounter::parseOneLineComment()
{
	_lineHasComment = true;
	_parser->skipLine();
}

void CommentCounter::parseMultilineComment()
{
	_lineHasComment = true;
	bool hasSkippedChar = false;
	while (true)
	{
		if (!hasSkippedChar)
		{
			_cursor = _parser->skipBlank();
		}
		hasSkippedChar = false;
		if (_cursor == '*')
		{
			_cursor = _parser->next();
			if (_cursor == '/')
			{
				break;
			}
			hasSkippedChar = true;
		}
		else if (_cursor == END_OF_LINE)
		{
			countLine();
			_lineHasComment = true;
		}
		else if (_cursor == END_OF_FILE)
		{
			throw ParseError("Expected '*/' but got end of file.");
		}
	}
}

void CommentCounter::countLine()
{
	if (_lineHasComment && _lineHasCode)
	{
		_fileStat.code_with_comments_lines++;
	}
	else if (_lineHasCode)
	{
		_fileStat.code_lines++;
	}
	else if (_lineHasComment)
	{
		_fileStat.comment_lines++;
	}
	else
	{
		_fileStat.blank_lines++;
	}

	_lineHasComment = false;
	_lineHasCode = false;
}

void CommentCounter::parseLiteral(char paren)
{
	while ((_cursor = _parser->skipBlank()) != paren)
	{
		if (_cursor == '\\')
		{
			// skip the escaped char
			_cursor = _parser->next();
			if (_cursor == END_OF_LINE)
				countLine();
			_lineHasCode = true;
		}
		else if (_cursor == END_OF_LINE || _cursor == END_OF_FILE)
		{
			throw ParseError("Expected string parenthesis but got end of line");
		}
	}
}