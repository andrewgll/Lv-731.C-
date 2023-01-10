// by Klepatskyi Oleh

#include "Parser.h"
#include <fstream>
#include <cctype>

Parser::Parser(const std::vector<std::string>& lines)
: _lines(lines), _cursor(0), _lineNumber(0)
{}

void Parser::start()
{
	_cursor = 0;
	_lineNumber = 0;
}

char Parser::next()
{
	if (_lineNumber == _lines.size())
		return END_OF_FILE;
	if (_cursor == _lines[_lineNumber].size())
	{
		nextLine();
		return END_OF_LINE;
	}
	return _lines[_lineNumber][_cursor++];
}

void Parser::nextLine()
{
    _lineNumber++;
	_cursor = 0;
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