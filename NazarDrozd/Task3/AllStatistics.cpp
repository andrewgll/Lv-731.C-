#include "AllStatistics.h"

void AllStatistics::addStatisticsFromAnalysis(const FileAnalysis& analysis)
{
	std::lock_guard<std::mutex> lock(m_lock);
	m_blank_lines += analysis.blank_lines;
	m_comment_lines += analysis.comment_lines;
	m_code_lines += analysis.code_lines;
}

void AllStatistics::write(const AllStatistics& statistics, const PathToFolder& path)
{
	m_total_files = path.m_path_to_files.size();
	m_end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = m_end - m_start;
	m_time = duration.count();

	std::ofstream fout;
	fout.open(path.getPath() + "Statistics.txt");
	fout << statistics;
	fout.close();
}

std::ofstream& operator<<(std::ofstream& os, const AllStatistics& statistics)
{
	os << "count of files were processed: " << statistics.m_total_files << std::endl;
	os << "blank_lines: " << statistics.m_blank_lines << std::endl;
	os << "comment_lines: " << statistics.m_comment_lines << std::endl;
	os << "code_lines: " << statistics.m_code_lines << std::endl;
	os << "duration: " << statistics.m_time << "s" << std::endl;

	return os;
}