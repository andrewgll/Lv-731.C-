#include "pch.h"
#include "../Threads/RootFolder.h"
#include "../Threads/ThreadPool.h"
#include "../Threads/StatisticManager.h"
#include "../Threads/LinesCounter.h"

TEST(LinesCounter, TestFile1) {
	string root = "C:\\Users\\l\\source\\repos\\Testing\\1.cpp";
    Lines expected_data = { 3, 18, 9 };
	Lines resulted_data = Counter(root);

	EXPECT_EQ(resulted_data.blank_lines, expected_data.blank_lines);
	EXPECT_EQ(resulted_data.code_lines, expected_data.code_lines);
	EXPECT_EQ(resulted_data.comment_lines, expected_data.comment_lines);
}

TEST(LinesCounter, TestFile2) {
	string root = "C:\\Users\\l\\source\\repos\\Testing\\2.cpp";
	Lines expected_data = { 5, 10, 9 };
	Lines resulted_data = Counter(root);

	EXPECT_EQ(resulted_data.blank_lines, expected_data.blank_lines);
	EXPECT_EQ(resulted_data.code_lines, expected_data.code_lines);
	EXPECT_EQ(resulted_data.comment_lines, expected_data.comment_lines);
}

TEST(LinesCounter, TestFile3) {
	string root = "C:\\Users\\l\\source\\repos\\Testing\\3.cpp";
	Lines expected_data = { 3, 10, 4 };
	Lines resulted_data = Counter(root);

	EXPECT_EQ(resulted_data.blank_lines, expected_data.blank_lines);
	EXPECT_EQ(resulted_data.code_lines, expected_data.code_lines);
	EXPECT_EQ(resulted_data.comment_lines, expected_data.comment_lines);
}