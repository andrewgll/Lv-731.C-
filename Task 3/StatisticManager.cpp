#include "StatisticManager.h"

void StatisticManager::AnalyseLines(const Lines& lines) {
	lock_guard<mutex> lg(mtx);

	sm_blank_lines += lines.blank_lines;
	sm_code_lines += lines.code_lines;
	sm_comment_lines += lines.comment_lines;
}

void StatisticManager::FileWriter(const StatisticManager& statistics, const RootFolder& root) {
	sm_num_files = root.root_path_files.size();
	end = chrono::high_resolution_clock::now();
	chrono::duration<float> total = end - begin;
	time = total.count();

	ConsoleWriter(statistics);

	ofstream out;
	out.open(root.getPath() + "TotalLines.txt");
	if (out.is_open()) {
		out << "================|Results|================" << endl;
		out << "Total number of processed files: " << statistics.sm_num_files << endl;
		out << "Blank lines: " << statistics.sm_blank_lines << endl;
		out << "Code lines: " << statistics.sm_code_lines << endl;
		out << "Comment lines: " << statistics.sm_comment_lines << endl;
		out << "Time: " << statistics.time << "s" << endl;
	}
	out.close();
}

void StatisticManager::ConsoleWriter(const StatisticManager& statistics) {
	cout << endl << "================|Results|================" << endl;
	cout << "Total number of processed files: " << statistics.sm_num_files << endl;
	cout << "Blank lines: " << statistics.sm_blank_lines << endl;
	cout << "Code lines: " << statistics.sm_code_lines << endl;
	cout << "Comment lines: " << statistics.sm_comment_lines << endl;
	cout << "Time: " << statistics.time << "s" << endl;
}