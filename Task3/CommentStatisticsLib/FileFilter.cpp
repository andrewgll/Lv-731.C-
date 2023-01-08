// by Klepatskyi Oleh
#include "FileFilter.h"
#include <filesystem>
#include <unordered_set>
#include <iostream>

namespace fs = std::filesystem;

std::vector<std::string> getAllFilesWithExtension(const std::string path, const std::vector<std::string> extensions)
{
    std::unordered_set<std::string> ext(extensions.begin(), extensions.end());
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