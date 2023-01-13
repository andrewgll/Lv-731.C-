// by Klepatskyi Oleh
#include "FileUtil.h"
#include <filesystem>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

namespace fs = std::filesystem;

std::vector<std::string> getAllFilesWithExtension(const std::string path, const std::vector<std::string> extensions)
{
    const std::unordered_set<std::string> ext(extensions.begin(), extensions.end());
    std::vector<std::string> result;
    for (auto& p : fs::recursive_directory_iterator(path))
    {
        if (ext.contains(p.path().extension().string()))
        {
            result.push_back(p.path().string());
        }
    }
    return result;
}

std::vector<std::string> getFileLines(const char* path)
{
    std::ifstream _ifs(path);
    std::vector<std::string> lines;
    std::string str;
    while (std::getline(_ifs, str))
    {
        lines.push_back(str);
    }
    return lines;
}

std::string getOutputFileName()
{
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);
    std::stringstream s;
    s << fs::current_path().string();
    s << "\\comment_stat_";
    s << std::put_time(&tm, "%F-%H-%M-%S");
    s << ".txt";
    return s.str();
}