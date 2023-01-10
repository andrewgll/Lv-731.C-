// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_PARSER_H_
#define _KLEPATSKYI_PARSER_H_

#include <stdexcept>
#include <string>
#include <vector>

const char END_OF_FILE = 26;
const char END_OF_LINE = '\n';

class ParseError : public std::runtime_error {
public:
	ParseError(const char* msg = "Parser occurred an error.") 
		: std::runtime_error(msg)
	{}
};

class Parser {
private:
	const std::vector<std::string>& _lines;
	size_t _cursor;
	size_t _lineNumber;
public:
	Parser(const std::vector<std::string>& lines);
	Parser(const Parser&) = delete;
	Parser& operator=(const Parser&) = delete;

	void start();
	char next();
	void nextLine();
	char skipBlank();
	inline size_t getLine() const { return _lineNumber; }
	inline size_t getCol() const { return _cursor; }
};

std::vector<std::string> getFileLines(const char* path);

#endif // _KLEPATSKYI_PARSER_H_