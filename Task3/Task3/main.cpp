// by Klepatskyi Oleh
#include "CommentStat.h" 
#include "FileFilter.h"

#include <iostream>
#include <string>

using namespace std;

void printFileStat(const std::string& path)
{
	
	FileCommentStat stat;
	CommentCounter counter(path.c_str(), stat);
	cout << "blank: " << stat.blank_lines << endl;
	cout << "code: " << stat.code_lines << endl;
	cout << "comment: " << stat.comment_lines << endl;
	cout << "total: " << (stat.blank_lines + stat.code_lines + stat.comment_lines) << endl;
}

int main()
{
	const char* path = "D:\\Study\\softserve\\lv-731\\task3\\Task3-Files\\test\\test1.txt";
	const char* project_path = "D:\\Study\\softserve\\lv-731\\task_repo\\Lv-731.C-\\Task3";

	const std::vector<std::string> vector = {".hpp", ".cpp", ".h", ".c"};
	std::vector<std::string> result = getAllFilesWithExtension(project_path, vector);

	for (auto& s : result)
	{
		std::cout << s << std::endl;
		printFileStat(s);
	}
	return 0;
}