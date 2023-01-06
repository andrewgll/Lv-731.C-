#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <regex>
#include <fstream>

namespace fs = std::filesystem;

class PathToFolder
{
public:
	void getPathToFilesFromDirectory();
	std::vector<std::string> m_path_to_files;
	std::string getPath() const { return m_path; }
private:
	std::string m_path;
	void enterDirectory();
};