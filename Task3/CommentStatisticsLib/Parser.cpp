// by Klepatskyi Oleh

#include "Parser.h"
#include <fstream>
#include <cctype>

class Parser::ParseStream {
private:
	std::ifstream _ifs;
public:
	ParseStream() = default;
	~ParseStream() {
		close();
	}

	inline void open(const char* filepath)
	{
		if (filepath == nullptr)
			throw ParseError("Path cannot be nullptr.");
		close();
		_ifs.open(filepath);
	}

	inline bool nextLine(std::string& str)
	{
		return (bool) std::getline(_ifs, str);
	}

	inline bool eof()
	{
		return !_ifs;
	}

	inline void close()
	{
		if (_ifs.is_open())
			_ifs.close();
	}
};

Parser::Parser() : _ps(new ParseStream()) {}
Parser::~Parser() { delete _ps; }

void Parser::start(const char* filepath)
{
	_ps->open(filepath);
	_cursor = 0;
	_lineNumber = 0;
	_ps->nextLine(_currentLine);
}

char Parser::next()
{
	if (_ps->eof())
		return END_OF_FILE;
	if (_cursor == _currentLine.size())
	{
		nextLine();
		return END_OF_LINE;
	}
	return _currentLine[_cursor++];
}

void Parser::nextLine()
{
	if (_ps->nextLine(_currentLine))
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