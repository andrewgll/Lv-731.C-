// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_FILE_FILTER_H_
#define _KLEPATSKYI_FILE_FILTER_H_

#include <vector>
#include <string>

/* Returns all files that have extension that is contained in provided vector,
starting from root folder and recursively searching files in subfolders. */
std::vector<std::string> getAllFilesWithExtension(const std::string path, const std::vector<std::string> extensions);

/* Opens file for read and reads line by line in string vector. */
std::vector<std::string> getFileLines(const char* path);

std::string getOutputFileName();

#endif // _KLEPATSKYI_FILE_FILTER_H_
