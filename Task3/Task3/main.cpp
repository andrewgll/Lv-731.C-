#include "CommentStat.h"
#include "CommentStat.cpp"
#include "Parser.cpp" // todo

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	const char* path = "D:\\Study\\softserve\\lv-731\\task3\\Task3-Files\\test\\test1.txt";
	FileCommentStat stat;
	CommentCounter counter(path, stat);
	cout << "blank: " << stat.blank_lines	<< endl;
	cout << "code: " << stat.code_lines	<< endl;
	cout << "comment: " << stat.comment_lines << endl;
	cout << "total: " << (stat.blank_lines + stat.code_lines + stat.comment_lines) << endl;
}