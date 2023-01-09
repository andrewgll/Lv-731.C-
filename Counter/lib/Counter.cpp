#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <map>
#include <algorithm>
#include <future>
#include <string.h>
#include <dirent.h>
#include <queue>
#include "../lib/timer.h"
class Counter
{
public:
    Counter(int argc, char **argv)
    {
        Init(argc, argv);
    }

private:
    enum class CommandOption
    {
        kBlankLines = 0, // count of blank lines
        kCodeLines = 1,  // count of lines with code
        kComments = 2,   // count of lines with comments
        kInputPath = 3,
        kOutputPath = 4, // specify folder to output stats
        kHelpMenu = 5
    };

    enum class LineState
    {
        kEmptyLine = 0,
        kCode = 1,
        kSingleComment = 2,
        kMultiCommentStart = 3,
        kMultiCommentEnd = 4,
        kNone = 10
    };

    std::mutex statsMutex;
    std::string inputPath;
    std::string outputPath;
    std::vector<CommandOption> options;
    std::vector<std::string_view> formats = {"hpp", "h", "cpp", "c"};
    std::map<std::string, std::vector<int>> stats;
    std::vector<std::future<int>> futures;
    std::vector<std::function<LineState(const std::string &str, LineState state)>> comparators = {
        // line
        [&](const std::string &str, LineState state)
        {
            if (str.length() == 0 && state != LineState::kMultiCommentStart)
                return LineState::kEmptyLine;
            return state;
        },
        // code
        [&](const std::string &str, LineState state)
        {
            if (state == LineState::kMultiCommentStart)
            {
                return state;
            }
            int ch = 0;
            int i = 1;
            for (int comment = 0; i < str.size(); i++)
            {
                if (str[i] == ' ')
                {
                    continue;
                }
                if (str[i] == '/' && str[i - 1] == '*')
                {
                    comment++;
                }
                else if (str[i] == '*' && str[i - 1] == '/')
                {
                    comment--;
                }
                else if (str[i] == '/' && str[i - 1] == '/')
                {
                    break;
                }
                else if (!comment)
                {
                    ch++;
                    break;
                }
            }
            if (ch == 1)
            {
                return LineState::kCode;
            }
            return LineState::kNone;
        },
        // comments .+//.+
        [&](const std::string &str, LineState state)
        {
            for (int i = 1, quote = 0, singlequote = 0; i < str.size(); i++)
            {
                if (str[i - 1] == '\\' && (str[i] == '"' || str[i] == '\''))
                {
                    continue;
                }
                else if (str[i] == '"' && quote)
                {
                    quote--;
                }
                else if (str[i] == '\'' && singlequote)
                {
                    singlequote--;
                }
                else if (str[i] == '\'')
                {
                    singlequote++;
                }
                else if (str[i] == '"')
                {
                    quote++;
                }
                else if (!quote && !singlequote)
                {
                    if (str[i - 1] == '/' && str[i] == '/' && state != LineState::kMultiCommentStart)
                    {
                        return LineState::kSingleComment;
                    }
                    else if (str[i - 1] == '/' && str[i] == '*')
                    {
                        state = LineState::kMultiCommentStart;
                    }
                    else if (str[i - 1] == '*' && str[i] == '/')
                    {
                        state = LineState::kMultiCommentEnd;
                    }
                }
            }
            return state;
        },
    };

    void PrintUsage()
    {
        printf("usage: counter -h\nusage: counter -i {path} -o {path}\nusage: counter -i {path} -{ a | f | b | c | l | o {path} }\n");
    }

    CommandOption HandleOptions(const std::string &argument)
    {
        if (argument[1] == 'i')
        {
            return CommandOption::kInputPath;
        }
        else if (argument[1] == 'o')
        {
            return CommandOption::kOutputPath;
        }
        else if (argument[1] == 'b')
        {
            return CommandOption::kBlankLines;
        }
        else if (argument[1] == 'c')
        {
            return CommandOption::kComments;
        }
        else if (argument[1] == 'l')
        {
            return CommandOption::kCodeLines;
        }
        else if (argument[1] == 'h')
        {
            return CommandOption::kHelpMenu;
        }
        throw "ERROR: Unknown argument: " + argument + "\n";
    }
    void HandleFilePath(const std::string &filePath)
    {
        std::ifstream ifile;
        ifile.open(filePath);
        std::string *temp;
        if (options.back() == CommandOption::kOutputPath)
        {
            // Skip check for output directory
            options.pop_back();
            outputPath = filePath;
            return;
        }
        else if (options.back() == CommandOption::kInputPath)
        {
            options.pop_back();
            temp = &inputPath;
        }
        else
        {
            throw "ERROR: Incorrect argument: " + filePath + "\n";
        }
        if (!ifile)
        {
            throw "ERROR: incorrect filepath: " + filePath + "\n";
        }
        *temp = filePath;
    }
    void HandleArguments(int argc, char **argv)
    {
        if (argc == 2 && strcmp(argv[1], "-h") == 0)
        {
            printf("Welcome to Counter - program to count different stuff in your files.\nUsage:\n-h\tHelp menu\n-i\t{directory}\tspecify directory to work with;\n-a\tcount everything Counter can;\n-f\tcount files only;\n-b\tcount blank lines;\n-c\tcount comments\n-l\tlines of code\n-o\t{filepath}\tspecify output file path.\n");
            printf("Example:\ncounter -i \"./myprogram\" -l -f -b -c -o \"./myoutput\"\n");
            throw "";
        }
        else if (argc < 5)
        {
            throw "ERROR: Please specify arguments\n";
        }
        char **temp = argv;
        temp++;
        while (*temp)
        {
            if (**temp == '-')
            {
                std::string argument = {*temp};
                options.push_back(HandleOptions(argument));
            }
            else if (options.size() == 0)
            {
                throw "ERROR: Please specify correct arguments\n";
            }
            else
            {
                HandleFilePath(*temp);
            }
            temp++;
        }
        if (inputPath.length() == 0)
        {
            throw "ERROR: Please specify input filepath\n";
        }
        if (outputPath.length() == 0)
        {
            throw "ERROR: Please specify output filepath\n";
        }
        if (options.size() == 0)
        {
            options.push_back(CommandOption::kBlankLines);
            options.push_back(CommandOption::kCodeLines);
            options.push_back(CommandOption::kComments);
        }
    }

    std::vector<std::string> FindFiles(const std::string& path)
    {    
        std::vector<std::string> files;
        try {
            for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(path)){
                if(dirEntry.is_regular_file())
                    files.push_back(std::filesystem::absolute(dirEntry.path()).string());
            }
        }
        catch(...){
            throw "ERROR: Invalid file \"" + path + "\" should be a directory";
        }
        return files;
    }
    bool HandleFileFormat(const std::string &file)
    {
        int len = file.length();
        for (auto format : formats)
        {
            int len2 = format.length();
            std::string_view fileFormat(file.c_str() + len - len2, len2);
            if (fileFormat == format)
            {
                return true;
            }
        }
        return false;
    }
    LineState AnalyzeString(const std::string &str, std::vector<int> &file_stats, LineState state)
    {

        for (auto option : options)
        {

            state = comparators[(int)option](str, state);

            if (state == LineState::kMultiCommentEnd)
            {
                file_stats[2]++;
                return LineState::kNone;
            }
            if (state == LineState::kEmptyLine)
            {
                file_stats[0]++;
                return LineState::kNone;
            }
            if (state != LineState::kMultiCommentStart)
            {
                file_stats[(int)state]++;
                state = LineState::kNone;
            }
        }

        if (state == LineState::kMultiCommentStart)
        {
            file_stats[2]++;
        }
        return state;
    }
    int AnalyzeFile(std::string file_str)
    {   
        Timer timer;
        try {
        std::vector<int> file_stats(4);
        std::ifstream file(file_str);
        std::string str;
        LineState state = LineState::kNone;
        while (std::getline(file, str))
        {
           
            state = AnalyzeString(str, file_stats, state);
        }
        file_stats[3] = timer.Stop();
        statsMutex.lock();
        stats[file_str] = file_stats;
        statsMutex.unlock();
        }
        catch(const char* ex){
            return 1;
        }
        return 0;

    }
    void ScanFiles(const std::vector<std::string> &files)
    {
        for (auto file : files)
        {
            if (HandleFileFormat(file))
            {
                futures.push_back(std::async(std::launch::async, &Counter::AnalyzeFile, this, file));
            }
        }
    }

    void WriteStats(int time){
        int files = 0;
        std::ofstream openFile;
        openFile.open(outputPath);
        if(!openFile){
            throw "ERROR: Cannot write to " + outputPath;
        }
        
        for (auto file : stats)
        {
            files++;
            openFile << file.first << "\n";
            int i = 0;
            for (auto stat : file.second)
            {
                if (i == 0)
                    openFile << "Blank lines " << stat << "\n";
                else if (i == 1)
                    openFile << "Code lines " << stat << "\n";
                else if (i == 2)
                    openFile << "Comments lines " << stat << "\n";
                else if (i == 3)
                    openFile << "Done in: " << stat * 0.001 << "ms"<< "\n\n"; 
                i++;
            }
        }
        openFile << "Total statistics:\n";
        for (size_t i = 0; i < 3; i++)
        {
            if(i == 0)
                openFile << "Files processed: " << files << "\n";
            else if(i == 2)
                openFile << "Program execution time: " << time * 0.001 << "ms" << "\n";
        }
        
    }

    void Init(int argc, char **argv)
    {
        Timer time;
        try
        {
            HandleArguments(argc, argv);
            std::sort(options.begin(), options.end());
            std::vector<std::string> files = FindFiles(inputPath);
            ScanFiles(files);

            for(auto& future: futures){
                if(future.get() != 0){
                    throw "ERROR: Something went wrong during counting\n";
                }
            }
            WriteStats(time.Stop());

           
        }
        catch (std::string msg)
        {
            PrintUsage();
            std::cerr << msg;
        }
        catch (const char *msg)
        {
            PrintUsage();
            std::cerr << msg;
        }
    }
};