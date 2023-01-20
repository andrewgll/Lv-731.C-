#include "RootFolder.h"

void RootFolder::EnterRootPath() {
	cout << "Enter root path: ";
	getline(cin, root);
}

void RootFolder::getFilesByExpansions() {
	EnterRootPath();
	const regex check_expansions(".+\\.((h)|(c)|(hpp)|(cpp))");

	try {
		for (const auto& entry : fs::recursive_directory_iterator(root)) {
			if (regex_match(entry.path().string(), check_expansions)) {
				root_path_files.push_back(entry.path().string());
			}
		}
	}
	catch (exception& ex) {
		cout << "Incorrect directory. Please, try again.\n\n";
		getFilesByExpansions();
	}
}