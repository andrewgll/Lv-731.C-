// by Klepatskyi Oleh
#include "pch.h"
#include "CommentStat.h"
TEST(CommentStatTest, CorrectlyParsesFile)
{
	const char* path = SOLUTION_DIR "test/test1.cpp";
	FileCommentStat expected = { 1, 12, 4 };
	FileCommentStat actual;
	auto lines = getFileLines(path);
	CommentCounter counter(lines, actual);
	EXPECT_NO_THROW(counter.start());
	ASSERT_EQ(expected, actual);
}
TEST(CommentStatTest, CorrectlyParsesWithCommentStartInStringLiteral)
{
	const char* path = SOLUTION_DIR "test/test2.cpp";
	FileCommentStat expected = { 1, 4, 1 };
	FileCommentStat actual;
	auto lines = getFileLines(path);
	CommentCounter counter(lines, actual);
	EXPECT_NO_THROW(counter.start());
	ASSERT_EQ(expected, actual);
}