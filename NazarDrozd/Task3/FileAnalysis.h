#pragma once
#pragma once
#include "AllStatistics.h"

FileAnalysis Analysis(std::ifstream& file)
{
	FileAnalysis analysis;

	enum class State
	{
		Code,
		String,
		SingleLineComment,
		MultiLineComment
	};
	State state = State::Code;

	bool is_current_line_blank = true;
	bool line_has_code = false;

	char previous;
	if (file.get(previous))
	{
		if (previous == '\n')
		{
			++analysis.blank_lines;
		}
		if (!std::isspace(previous))
		{
			is_current_line_blank = false;
			if (previous != '/')
			{
				line_has_code = true;
			}
		}
		if (previous == '"')
		{
			state = State::String;
			line_has_code = true;
		}
	}

	char current;
	while (file.get(current))
	{
		if (!std::isspace(current))
		{
			is_current_line_blank = false;
		}
		switch (state)
		{
		case State::Code:
			if (previous == '\n' && !std::isspace(current) && current != '/')
			{
				line_has_code = true;
			}
			if (!isspace(previous) && !std::isspace(current) && !(previous == '/' && current == '/')
				&& !(previous == '/' && current == '*') && previous != '\n' && previous != '\t')
			{
				line_has_code = true;
			}
			if (current == '\n')
			{
				if (is_current_line_blank)
				{
					++analysis.blank_lines;
				}
				if (line_has_code)
				{
					++analysis.code_lines;
				}
				is_current_line_blank = true;
				line_has_code = false;
			}
			if (previous == '/' && current == '/')
			{
				state = State::SingleLineComment;
			}
			if (previous == '/' && current == '*')
			{
				state = State::MultiLineComment;
			}
			if (current == '"')
			{
				state = State::String;
				line_has_code = true;
			}
			break;

		case State::String:
			if (previous != '\\' && current == '"')
			{
				state = State::Code;
			}
			if (current == '\n')
			{
				++analysis.code_lines;
				line_has_code = false;
				is_current_line_blank = true;
			}
			break;

		case State::SingleLineComment:
			if (current == '\n')
			{
				++analysis.comment_lines;
				if (previous != '\\')
				{
					state = State::Code;
				}
				if (line_has_code)
				{
					++analysis.code_lines;
				}
				line_has_code = false;
				is_current_line_blank = true;
			}
			break;

		case State::MultiLineComment:
			if (previous == '*' && current == '/')
			{
				state = State::Code;
				++analysis.comment_lines;
			}
			if (previous != '\\' && current == '\n')
			{
				if (is_current_line_blank)
				{
					++analysis.blank_lines;
				}
				if (line_has_code)
				{
					++analysis.code_lines;
				}
				++analysis.comment_lines;
				is_current_line_blank = true;
				line_has_code = false;
			}
			break;
		}
		previous = current;
	}
	if (is_current_line_blank)
	{
		++analysis.blank_lines;
	}
	else
	{
		switch (state)
		{
		case State::Code:
			analysis.code_lines++;
			break;
		case State::String:
			analysis.code_lines++;
			break;
		case State::SingleLineComment:
			analysis.comment_lines++;
			break;
		case State::MultiLineComment:
			analysis.comment_lines++;
			break;
		}
	}
	return analysis;
}