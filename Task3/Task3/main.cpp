// by Klepatskyi Oleh

#include "FileUtil.h"
#include "CommentStatCore.h"
#include "Timer.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static const char* g_default_path = SOLUTION_DIR "test";
static const std::vector<std::string> g_extensions = { ".hpp", ".cpp", ".h", ".c" };

void writeToFileTask(CommentStatisticsMap& map, const std::vector<std::string>& files, std::time_t exectime)
{
	try {
		std::string path = getOutputFileName();
		std::ofstream os(path, std::ios_base::out);
		write(os, map, files, exectime);
		os << std::flush;
		os.close();
		std::cout << "File was saved to " << path << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cerr << "There was an error writing to file : " << ex.what() << std::endl;
	}
}

void output(std::string option, CommentStatisticsMap& map, const std::vector<std::string>& files, std::time_t exectime)
{
	if (option.starts_with("a"))
	{
		writeToFileTask(map, files, exectime);
		write(std::cout, map, files, exectime);
	}
	else if (option.starts_with("f"))
	{
		writeToFileTask(map, files, exectime);
	}
	else if (option.starts_with("c"))
	{
		write(std::cout, map, files, exectime);
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

	try {
		auto files = getAllFilesWithExtension(path, g_extensions);
		CommentStatisticsMap map;
		TimerMicro timer;
		getCommentStatAsync(map, files);
		output(answer, map, files, timer.stop());
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error occurred: " << ex.what() << std::endl;
	}
	return 0;
}