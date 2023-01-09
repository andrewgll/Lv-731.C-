#include "PathToFolder.h"

void PathToFolder::enterDirectory()
{
	std::cout << "(D:\\Visual projects\\C++\\)\nEnter a directory: ";
	std::getline(std::cin, m_path);
}

void PathToFolder::getPathToFilesFromDirectory()
{
	enterDirectory();
	const std::regex check_expr(".+\\.((h)|(c)|(hpp)|(cpp))");
	try
	{
		for (const auto& entry : fs::recursive_directory_iterator(m_path))
		{
			if (std::regex_match(entry.path().string(), check_expr))
			{
				m_path_to_files.push_back(entry.path().string());
			}
		}
	}
	catch (std::exception& ex)
	{

		std::cout << "Incorrect directory. Please, try again.\n\n";
		getPathToFilesFromDirectory();
	}
}