// by Klepatskyi Oleh
#include "CommentStat.h" 
#include "FileFilter.h"

#include <iostream>
#include <string>

using namespace std;

void printFileStat(const std::string& path)
{
	FileCommentStat stat;
	auto lines = getFileLines(path.c_str());
	CommentCounter counter(lines);
	stat = counter.start();
	cout << "blank: " << stat.blank() << endl;
	cout << "code: " << stat.code() << endl;
	cout << "comment: " << stat.comment() << endl;
	cout << "total: " << stat.total() << endl;
}

int main()
{
	const char* path = SOLUTION_DIR "test";
	const std::vector<std::string> vector = {".hpp", ".cpp", ".h", ".c"};
	std::vector<std::string> result = getAllFilesWithExtension(path, vector);

	for (auto& s : result)
	{
		std::cout << s << std::endl;
		try {
			printFileStat(s);
		}
		catch (const std::runtime_error& ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}
	return 0;
}