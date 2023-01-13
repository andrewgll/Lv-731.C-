// by Klepatskyi Oleh

#include "FileUtil.h"
#include "CommentStatCore.h"

#include <iostream>
#include <string>

using namespace std;

static const char* g_default_path = SOLUTION_DIR "test";
static const std::vector<std::string> g_extensions = { ".hpp", ".cpp", ".h", ".c" };

int main()
{
	std::string path;
	std::cout << "Enter path to root folder (or leave empty to default '..\\SOLUTION_DIR\\test\\'): ";
	std::getline(std::cin, path);
	
	if (path.empty())
		path = g_default_path;
	std::cout << path << std::endl;
	try {
		auto files = getAllFilesWithExtension(path, g_extensions);
		CommentStatisticsMap map;
		getCommentStatAsync(map, files);
		printStat(map, files);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error occurred: " << ex.what() << std::endl;
	}
	return 0;
}