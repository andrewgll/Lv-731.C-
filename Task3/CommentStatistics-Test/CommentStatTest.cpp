// by Klepatskyi Oleh
#include "pch.h"
#include "CommentStat.h"
TEST(CommentStatTest, CorrectlyParsesFile)
{
	const char* path = SOLUTION_DIR "test/test1.cpp";
	FileCommentStat expected = { 1, 12, 4 };
	FileCommentStat actual;
	auto lines = getFileLines(path);
	CommentCounter counter(lines);
	EXPECT_NO_THROW(actual = counter.start());
	ASSERT_EQ(expected, actual);
}
TEST(CommentStatTest, CorrectlyParsesWithCommentStartInStringLiteral)
{
	const char* path = SOLUTION_DIR "test/test2.cpp";
	FileCommentStat expected = { 1, 4, 1 };
	FileCommentStat actual;
	auto lines = getFileLines(path);
	CommentCounter counter(lines);
	EXPECT_NO_THROW(actual = counter.start());
	ASSERT_EQ(expected, actual);
}

TEST(CommentStatTest, LiteralTest)
{
	const char* path = SOLUTION_DIR "test/test3.cpp";
	FileCommentStat expected = {0, 3, 1 };
	FileCommentStat actual;
	auto lines = getFileLines(path);
	CommentCounter counter(lines);
	EXPECT_NO_THROW(actual = counter.start());
	ASSERT_EQ(expected, actual);
}

TEST(CommentStatTest, CorrectlyParsesAllTheLines)
{
	const char* path = SOLUTION_DIR "test/sqlite3.c";
	FileCommentStat actual;
	auto lines = getFileLines(path);
	CommentCounter counter(lines);
	EXPECT_NO_THROW(actual = counter.start());
	ASSERT_EQ(241619, actual.total());
}