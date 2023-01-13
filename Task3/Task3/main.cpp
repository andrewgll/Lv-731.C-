// by Klepatskyi Oleh

#include "FileUtil.h"
#include "CommentStatCore.h"

#include <iostream>
#include <string>

using namespace std;

static const char* g_default_path = SOLUTION_DIR "test";
static const std::vector<std::string> g_extensions = { ".hpp", ".cpp", ".h", ".c" };

void writeToFileTask(CommentStatisticsMap& map, const std::vector<std::string>& files)
{
	try {
		writeToFile(map, files, getOutputFileName());
	}
	catch (const std::exception& ex)
	{
		std::cerr << "There was an error writing to file : " << ex.what() << std::endl;
	}
}

void output(std::string option, CommentStatisticsMap& map, const std::vector<std::string>& files)
{
	if (option.starts_with("a"))
	{
		writeToFileTask(map, files);
		printStat(map, files);
	}
	else if (option.starts_with("f"))
	{
		writeToFileTask(map, files);
	}
	else if (option.starts_with("c"))
	{
		printStat(map, files);
	}
}

int main()
{
	std::string path;
	std::string answer;
	std::cout << "Enter path to root folder (or leave empty to default '..\\SOLUTION_DIR\\test\\'): ";
	std::getline(std::cin, path);
	std::cout << "Output to file/console/all/none? (f/c/a/n):";
	std::getline(std::cin, answer);
	
	if (path.empty())
		path = g_default_path;
	std::cout << path << std::endl;
	try {
		auto files = getAllFilesWithExtension(path, g_extensions);
		CommentStatisticsMap map;
		getCommentStatAsync(map, files);
		output(answer, map, files);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error occurred: " << ex.what() << std::endl;
	}
	return 0;
}