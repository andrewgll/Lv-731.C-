// by Klepatskyi Oleh
#include "CommentStat.h"
#include "Parser.h"
#include "FileFilter.h"
#include "Timer.h"

#include <iostream>
#include <string>
#include <map>
#include <future>
#include <mutex>
#include <memory>

using namespace std;

void printFileStat(const std::string& path)
{
	FileCommentStat stat;
	Timer t;
	auto lines = getFileLines(path.c_str());
	t.stop();
	CommentCounter counter(lines);
	stat = counter.start();
	cout << "blank: " << stat.blank() << endl;
	cout << "code: " << stat.code() << endl;
	cout << "comment: " << stat.comment() << endl;
	cout << "total: " << stat.total() << endl;
}

void task(std::map<std::string, FileCommentStat>& map,
	const std::string& file,
	std::shared_ptr<std::vector<std::string>> lines)
{
	static std::mutex _mutex;

	CommentCounter counter(*lines);
	FileCommentStat stat = counter.start();
	std::lock_guard<std::mutex> lg(_mutex);
	map.insert({ file,  stat });
}

void parallel(const std::vector<std::string>& files)
{
	std::map<std::string, FileCommentStat> map;
	std::vector<std::shared_ptr<std::vector<std::string>>> vectorOfLines;
	std::vector<std::future<void>> futures;

	for (auto& const path : files)
	{
		Timer t;
		vectorOfLines.emplace_back(std::make_shared<std::vector<std::string>>(getFileLines(path.c_str())));
		t.stop();
		auto f = std::async(std::launch::async,
			task,
			std::ref(map),
			std::ref(path),
			vectorOfLines.back());
		
		futures.push_back(std::move(f));
	}

	for (auto& f : futures)
	{
		f.wait();
	}

	for (auto const& [file, stat] : map)
	{
		std::cout << file << " ============\n";
		cout << "blank: " << stat.blank() << endl;
		cout << "code: " << stat.code() << endl;
		cout << "comment: " << stat.comment() << endl;
		cout << "code with comment: " << stat.comment() << endl;
		cout << "total: " << stat.total() << endl;
	}
}

int main()
{
	const char* path = SOLUTION_DIR "test";
	const std::vector<std::string> vector = {".hpp", ".cpp", ".h", ".c"};
	std::vector<std::string> result = getAllFilesWithExtension(path, vector);
	for (int i = 0; i < 5; i++)
		result.push_back(SOLUTION_DIR "test/sqlite3.c");
	Timer t1;
	for (auto& s : result)
	{
		std::cout << s << std::endl;
		try {
			printFileStat(s);
		}
		catch (const std::runtime_error& ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}
	t1.stop();
	Timer t2;
	parallel(result);
	t2.stop();
	return 0;
}