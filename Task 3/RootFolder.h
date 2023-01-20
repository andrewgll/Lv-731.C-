#pragma once

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;
namespace fs = experimental::filesystem;

class RootFolder {
private:
	string root;

	void EnterRootPath();

public:
	vector<string> root_path_files;

	void getFilesByExpansions();
	string getPath() const { 
		return root;
	}
};