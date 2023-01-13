// by Klepatskyi Oleh

#include "FileFilter.h"
#include "CommentStatCore.h"

#include <iostream>

using namespace std;

static const char* path = SOLUTION_DIR "test";
static const std::vector<std::string> g_extensions = { ".hpp", ".cpp", ".h", ".c" };

int main()
{
	auto files = getAllFilesWithExtension(path, g_extensions);
	CommentStatisticsMap map;
	getCommentStatAsync(map, files);
	printStat(map, files);
	return 0;
}