#include <iostream>
#include <windows.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <chrono>

std::string getCurrentDir();
bool isRequiredExtension(std::filesystem::__cxx11::directory_entry entry); // Check if taken file if suitable for requirements
void CalculateLines(std::filesystem::__cxx11::path fpath);
void PrintToFile(std::filesystem::__cxx11::path fpath, const int blank_lines, const int comment_lines, const int physical_lines);

// Global variable for starting time of the program
std::chrono::_V2::system_clock::time_point start, stop, start2, stop2;

int main()
{
    // Get starting timepoint
    start = std::chrono::high_resolution_clock::now();

    std::string path_to_dir = getCurrentDir();
    for (const auto &entry : std::filesystem::directory_iterator(path_to_dir))
    {
        // Executing Lines Calculating func for eack suitable file
        auto fpath = entry.path();
        if (isRequiredExtension(entry))
        {
            start2 = std::chrono::high_resolution_clock::now();

            CalculateLines(fpath);
        }
    }
    // Get entire program runtime
    stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    std::cout << "Time taken for analyzing all files: " << duration << " microseconds\n";
    return 0;
}

std::string getCurrentDir()
{
    char buff[MAX_PATH];
    GetModuleFileName(NULL, buff, MAX_PATH);
    std::string::size_type position = std::string(buff).find_last_of("\\/");
    return std::string(buff).substr(0, position);
}

bool isRequiredExtension(std::filesystem::__cxx11::directory_entry entry)
{
    std::string extensions[4] = {".c", ".h", ".cpp", ".hpp"};
    for (int i = 0; i < 4; i++)
    {
        if (std::filesystem::path(entry).extension() == extensions[i])
        {
            return true;
        }
    }
    return false;
}

void CalculateLines(std::filesystem::__cxx11::path fpath)
{
    std::ifstream fin;
    std::string temp_str;
    bool still_comment = false, still_text = false, still_physical = false;
    int blank_lines = 0, comment_lines = 0, physical_lines = 0; 
    fin.open(fpath);
    if (fin)
    {
        while (!fin.eof())
        {
            std::getline(fin, temp_str);
            still_physical = false; // Restart lines blank tate for each line
            for (int index = 0; index < temp_str.length(); index++)
            {
                // Skip spaces and tab symbols.
                if (temp_str[index] == ' ' || temp_str[index] == '\t')
                {
                    continue;
                }
                // Check if were there any symbols before '//'. If yes, count one more comment line.
                else if (!still_text && !still_physical && (temp_str[index] == '/' && temp_str[index + 1] == '/'))
                {
                    comment_lines++;
                    blank_lines--;
                    break;
                }
                // Skip '\"' symbol.
                else if (temp_str[index - 1] == '\\' && temp_str[index] == '\"')
                {
                    continue;
                }
                // Control when pointer is inside of "text".
                else if (temp_str[index] == '\"')
                {
                    still_text = !still_text;
                    continue;
                }
                // Control the beginning of multiline comment.
                else if (!still_text && (temp_str[index] == '/' && temp_str[index + 1] == '*'))
                {
                    still_comment = true;
                    continue;
                }
                // Control the end of multiline comment.
                else if (!still_text && (temp_str[index] == '*' && temp_str[index + 1] == '/'))
                {
                    // If earlier there were no physical symbols, but multiline comment ends, comment_lines++.
                    if (!still_physical && temp_str[index + 2] == '\0')
                    {
                        still_comment = false;
                        comment_lines++;
                        blank_lines--;
                        break;
                    }
                    // If earlier there wes at least one physical symbol, but multiline comment ends don`t add anything to comment lines counter.
                    else if (still_physical && temp_str[index + 2] == '\0')
                    {
                        still_comment = false;
                        break;
                    }
                }
                // If current symbol is not '\0' and all multiline comments ended.
                else if (!still_comment && temp_str[index] != '\0')
                {
                    still_physical = true;
                }
            }
            // Concludint previous results.
            if (still_physical == true)
            {
                physical_lines++;
            }
            else if (!still_physical && still_comment == true)
            {
                comment_lines++;
            }
            else
            {
                blank_lines++;
            }
        }
        // Writes down info about each separate file after its calculation
        PrintToFile(fpath, blank_lines, comment_lines, physical_lines);
    }
    else
    {
        std::cout << "File wasn`t opened.";
    }
    fin.close();
}

void PrintToFile(std::filesystem::__cxx11::path fpath, const int blank_lines, const int comment_lines, const int physical_lines)
{
    std::ofstream fout;
    fout.open("Programm results.txt", std::ios::app);
    if (!fout.is_open())
    {
        std::cout << "File wasn`t created.";
    }
    else
    {
        // Writing down all geathered info about each file
        fout << "\nIn file " << fpath;
        fout << "\nBlank lines: " << blank_lines << " Comment lines: " << comment_lines << " Physical lines: " << physical_lines << "\n";
        // Get duration time of calculating each specific file
        stop2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2).count();
        fout << "Time taken for analyzing this file: " << duration2 << " microseconds\n";
        fout.close();
    }
}