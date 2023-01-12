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
	long long _cursor;
	size_t _lineNumber;
public:
	Parser(const std::vector<std::string>& lines);
	Parser(const Parser&) = delete;
	Parser& operator=(const Parser&) = delete;

	/* resets parser */
	void start();

	/* 
	   moves cursor to next symbol and returns it.
	   if current line has no more symbols,
	   moves cursor to the next line and returns line separator.
	*/
	char next();

	/* returns char under the cursor */
	char current() const;

	/* moves cursor to the next line and returns first symbol */
	char nextLine();

	/* moves cursor to the end of current line */
	void skipLine();

	/* returns first symbol in current line that is not a space symbol. (see isspace()) */
	char skipBlank();

	inline size_t getLine() const { return _lineNumber; }
	inline size_t getCol() const { return _cursor; }
	
};

std::vector<std::string> getFileLines(const char* path);

#endif // _KLEPATSKYI_PARSER_H_