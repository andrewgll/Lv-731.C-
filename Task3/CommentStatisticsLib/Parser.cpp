// by Klepatskyi Oleh

#include "Parser.h"
#include <fstream>
#include <cctype>
#include <cassert>
#include <iostream>
#include <mutex>

Parser::Parser(const std::vector<std::string>& lines)
: _lines(lines), _cursor(0), _lineNumber(0)
{}

void Parser::start()
{
	//static std::mutex _mutex;
	_cursor = -1;
	_lineNumber = 0;
	//std::lock_guard<std::mutex> lg(_mutex);
	/*for (const auto& s : _lines)
	{
		std::cout << s << std::endl;
	}*/
}

char Parser::next()
{
	if (_lineNumber == _lines.size())
		return END_OF_FILE;
	_cursor++;
	if (_cursor == _lines[_lineNumber].size())
	{
		return END_OF_LINE;
	}
	if (_cursor > _lines[_lineNumber].size())
	{
		return nextLine();
	}
	return _lines[_lineNumber][_cursor];
}

char Parser::current() const
{
	if (_cursor == -1)
	{
		throw ParseError("Cursor is not at the start. Call next() first.");
	}
	if (_lineNumber == _lines.size())
		return END_OF_FILE;
	if (_cursor == _lines[_lineNumber].size())
	{
		return END_OF_LINE;
	}
	return _lines[_lineNumber][_cursor];
}

char Parser::nextLine()
{
    _lineNumber++;
	_cursor = 0;
	return current();
}

void Parser::skipLine()
{
	_cursor = _lines[_lineNumber].size();
}

char Parser::skipBlank()
{
	char c = next();
	while (isspace(c) && c != END_OF_LINE && c != END_OF_FILE)
		c = next();
	return c;
}

std::vector<std::string> getFileLines(const char* path)
{
	std::ifstream _ifs(path);
	std::vector<std::string> lines;
	std::string str;
	while (std::getline(_ifs, str))
	{
		lines.push_back(str);
	}
	return lines;
}
