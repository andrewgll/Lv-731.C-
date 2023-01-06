#include "PathToFolder.h"

void PathToFolder::enterDirectory()
{
	std::cout << "Enter a directory: (D:\\Visual projects\\C++\\)\n"; //D:\Visual projects\C++\TestFolder
	std::getline(std::cin, m_path);
}

void PathToFolder::getPathToFilesFromDirectory()
{
	enterDirectory();
	const std::regex check_expr(".+\\.((h)|(c)|(hpp)|(cpp))");

	for (const auto& entry : fs::recursive_directory_iterator(m_path))
	{
		if (std::regex_match(entry.path().string(), check_expr))
		{
			m_path_to_files.push_back(entry.path().string());
		}
	}
}