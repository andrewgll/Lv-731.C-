#include <iostream>
#include <cstring>
#include <fstream>

int main() // skip
{
    int blank_lines = 0, comment_lines = 0, physical_lines = 0; /* */
    std::ifstream fin;
    std::string fpath = "D:\\CPP\\FirstChair\\Test\\test.cpp";
    std::string temp_str;
    fin.open(fpath);
    if (fin)
    {
        bool still_comment = false, still_text = false, still_physical = false;
        while (!fin.eof())
        {
            std::getline(fin, temp_str);
            still_physical = false;
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
        std::cout << "In file " << fpath;
        std::cout << "\nBlank lines: " << blank_lines << " Comment lines: " << comment_lines << " Physical lines: " << physical_lines;
    }
    else
    {
        std::cout << "File wasn`t opened.";
    }
}