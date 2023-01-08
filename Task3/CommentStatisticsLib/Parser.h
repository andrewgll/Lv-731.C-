// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_PARSER_H_
#define _KLEPATSKYI_PARSER_H_

#include <stdexcept>
#include <string>

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
	class ParseStream;
	ParseStream* const _ps;
	std::string _currentLine;
	size_t _cursor;
	size_t _lineNumber;
public:
	Parser();
	~Parser();
	Parser(const Parser&) = delete;
	Parser& operator=(const Parser&) = delete;

	void start(const char* filepath);
	char next();
	void nextLine();
	char skipBlank();
	inline size_t getLine() { return _lineNumber; }
};


#endif // _KLEPATSKYI_PARSER_H_