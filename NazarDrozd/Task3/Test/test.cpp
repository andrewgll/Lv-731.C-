#include "pch.h"
#include "../AllStatistics.h"
#include "../AllStatistics.cpp"
#include "../FileAnalysis.h"
#include "../PathToFolder.h"
#include "../PathToFolder.cpp"
#include "../ThreadPool.h"
#include "../ThreadPool.cpp"

// Test1 
// blank_lines 5, comment_lines 5, code_lines 10
//
// Test2
// blank_lines 1, comment_lines 9, code_lines 10
// 
// Test3
// blank_lines 3, comment_lines 5, code_lines 6

// Total_lines
// blank_lines 9, comment_lines 19, code_lines 26

//D:\Visual Projects\C++\Task3\Task3 - test\TestFiles

TEST(FileAnalysis, Analysis1)
{
	std::string path = "D:\\Visual Projects\\C++\\Task3\\Task3-test\\TestFiles\\Test1.cpp";
	FileAnalysis expected = { 5, 5, 10 };
	FileAnalysis result = Analysis(path);	
	EXPECT_EQ(result.blank_lines, expected.blank_lines);
	EXPECT_EQ(result.comment_lines, expected.comment_lines);
	EXPECT_EQ(result.code_lines, expected.code_lines);
}

TEST(FileAnalysis, Analysis2)
{
	std::string path = "D:\\Visual Projects\\C++\\Task3\\Task3-test\\TestFiles\\Test2.cpp";
	FileAnalysis expected = { 1, 9, 10 };
	FileAnalysis result = Analysis(path);
	EXPECT_EQ(result.blank_lines, expected.blank_lines);
	EXPECT_EQ(result.comment_lines, expected.comment_lines);
	EXPECT_EQ(result.code_lines, expected.code_lines);
}

TEST(FileAnalysis, Analysis3)
{
	std::string path = "D:\\Visual Projects\\C++\\Task3\\Task3-test\\TestFiles\\Test3.cpp";
	FileAnalysis expected = { 3, 5, 6 };
	FileAnalysis result = Analysis(path);
	EXPECT_EQ(result.blank_lines, expected.blank_lines);
	EXPECT_EQ(result.comment_lines, expected.comment_lines);
	EXPECT_EQ(result.code_lines, expected.code_lines);
}
