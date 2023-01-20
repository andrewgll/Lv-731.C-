#pragma once
#include "StatisticManager.h"

Lines Counter(const string& path) {
	Lines lines;
	ifstream in(path);

	bool isBlank = true;
	bool isIdentify = false;

	char ch;
	while (in.get(ch)) {
		if (ch == '\n' && isBlank == true) {
			lines.blank_lines++;
		}
		else if (ch == '\n') {
			isIdentify = false;
			isBlank = true;
		}
		else if (ch == '/' && isIdentify == false) {
			isBlank = false;
			in.get(ch);
			if (ch == '/') {
				lines.comment_lines++;
				isIdentify = true;
			}
			else if (ch == '*') {
				while (in.get(ch)) {
					if (ch == '*') {
						in.get(ch);
						if (ch == '/') {
							lines.comment_lines++;
							break;
						}
					}
					else if (ch == '\n') {
						lines.comment_lines++;
					}
				}
			}
			else {
				lines.code_lines++;
				isIdentify = true;
			}
		}
		else if (ch == '/' && isIdentify == true) {
			in.get(ch);
			if (ch == '/') {
				lines.comment_lines++;
				while (in.get(ch)) {
					if (ch == '\n') {
						isIdentify = false;
						isBlank = true;
						break;
					}
				}
			}
			else if (ch == '*') {
				lines.comment_lines++;
				while (in.get(ch)) {
					if (ch == '*') {
						in.get(ch);
						if (ch == '/') {
							isIdentify = false;
							break;
						}
					}
					if (ch == '\n') {
						lines.comment_lines++;
					}
				}
			}
		}
		else if (ch != ' ' && ch != '\t' && isIdentify == false) {
			lines.code_lines++;
			isBlank = false;
			isIdentify = true;
		}
	}

	return lines;
}