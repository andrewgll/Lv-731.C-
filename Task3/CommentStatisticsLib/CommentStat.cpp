// by Klepatskyi Oleh
#include "CommentStat.h"
#include <iostream>
using std::cout; using std::endl;

CommentCounter::CommentCounter(const std::vector<std::string>& lines, FileCommentStat& fileStat)
	: _parser(new Parser(lines)), _fileStat(fileStat)
{
	_fileStat = FileCommentStat();
	
}

CommentCounter::~CommentCounter()
{
	delete _parser;
}

void CommentCounter::start()
{
	_parser->start();
	parseLineFromStart();
}

void CommentCounter::parseLineFromStart()
{
	char cursor;
	int i = 0;
	while ((cursor = _parser->skipBlank()) != END_OF_FILE)
	{
		_lineHasCode = false;
		_lineHasComment = false;
		if (cursor == END_OF_LINE)
		{
			_fileStat.blank_lines++;
			continue;
		}
		if (cursor == '/')
		{
			cursor = parseComment();
			if (cursor != END_OF_LINE)
				parseLine();
			continue;
		}
		if (cursor == '"')
		{
			parseStringLiteral();
		}
		assignCode();
		parseLine();
	}
}

void CommentCounter::parseLine()
{
	char cursor;
	while ((cursor = _parser->skipBlank()) != END_OF_LINE)
	{
		if (cursor == '/')
		{
			cursor = parseComment();
			if (cursor == END_OF_LINE) break;
		}
		else 
		{
			assignCode();
			if (cursor == '"')
			{
				parseStringLiteral();
			}
		}
	}
}

char CommentCounter::parseComment()
{
	char cursor = _parser->next();
	if (cursor == '/')
	{
		parseOneLineComment();
		return END_OF_LINE;
	}
	else if (cursor == '*')
	{
		return parseMultilineComment();
	}
	else 
	{
		assignCode();
		return cursor;
	}
}

void CommentCounter::parseOneLineComment()
{
	assignComment();
	_parser->nextLine();
}

char CommentCounter::parseMultilineComment()
{
	char cursor;
	char temp = 0;
	while (true)
	{
		if (temp != 0)
		{
			cursor = temp;
			temp = 0;
		}
		else
		{
			cursor = _parser->next();
		}
		if (cursor == '*')
		{
			temp = _parser->next();
			if (temp == '/')
			{
				assignComment();
				break;
			}
		}
		if (cursor == END_OF_LINE)
		{
			assignComment();
			_lineHasCode = false;
			_lineHasComment = false;
		}
		else if (cursor == END_OF_FILE)
		{
			throw ParseError("Expected '*/' but got end of file.");
		}
	}
	return cursor;
}

void CommentCounter::parseStringLiteral()
{
	char cursor;
	while (true)
	{
		cursor = _parser->next();
		if (cursor == '"')
		{
			break;
		}
		else if (cursor == '\\')
		{
			// skip the escaped char
			_parser->next();
		}
		else if (cursor == END_OF_LINE || cursor == END_OF_FILE)
		{
			throw ParseError("Expected '\"' but got end of line");
		}
	}
}

void CommentCounter::assignCode()
{
	if (!_lineHasCode) {
		if (_lineHasComment)
		{
			_fileStat.comment_lines--;
			_lineHasComment = false;
		}
		_fileStat.code_lines++;
		_lineHasCode = true;
	}
}

void CommentCounter::assignComment()
{
	if (!_lineHasCode && !_lineHasComment)
	{
		_fileStat.comment_lines++;
		_lineHasComment = true;
	}
}