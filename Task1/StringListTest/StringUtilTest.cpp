// by Oleh Klepatskyi
#include "pch.h"
#include "StringUtil.h"
#include "MemoryLeakDetector.h"
TEST(StringUtilFind, ReturnsMinusOneOnEmptyStrings)
{
	EXPECT_EQ(find("", ""), -1);
	EXPECT_EQ(find("", "a"), -1);
	EXPECT_EQ(find("a", ""), -1);
}
TEST(StringUtilFind, ReturnsMinusOneIfSubstringIsBigger)
{
	EXPECT_EQ(find("a", "ab"), -1);
	EXPECT_EQ(find("ab", "cda", 2), -1);
}

TEST(StringUtilFind, CorrectlyFindsSubstringInTheEnd)
{
	EXPECT_EQ(find("zzza", "a"), 3);
}
TEST(StringUtilFind, ReturnsFirstIndexOfSubstring)
{
	EXPECT_EQ(find("aaaaaa", "a"), 0);
	EXPECT_EQ(find("aaaaaa", "a", 1), 1);
	EXPECT_EQ(find("babcabc", "abc"), 1);
}

TEST(StringUtilFind, ReturnsMinusOneIfSubstringIsNotFound)
{
	EXPECT_EQ(find("babab", "abc"), -1);
	EXPECT_EQ(find("babcab", "abc", 2), -1);
}

void testReplace(const char* initial, const char* before, const char* after, const char* expected)
{
	MemoryLeakDetector d;
	char* actual = replace(initial, before, after);
	EXPECT_STR_EQ(expected, actual);
	free(actual);
}
TEST(StringUtilReplace, NoChangesAppliedIfSubstringIsNotFound)
{
	testReplace("abc", "d", "a", "abc");
}

TEST(StringUtilReplace, EmptySubstringAppliesNoChanges)
{
	testReplace("abc", "", "z", "abc");
}

TEST(StringUtilReplace, ReplacesEachOccurrenceOfOneSymbolCorrectly)
{
	testReplace("aaaabaaaa", "a", "b", "bbbbbbbbb");
}

TEST(StringUtilReplace, RemoveAllOccurrencesCorrectly)
{
	testReplace("abababab", "a", "", "bbbb");
}

TEST(StringUtilReplace, ReplaceWithLongerStringCorrectly)
{
	testReplace("acaca", "a", "bb", "bbcbbcbb");
}

TEST(StringUtilReplace, ReplaceWithShorterStringCorrectly)
{
	testReplace("acaca", "ac", "a", "aaa");
}

TEST(StringUtilReplace, ReplaceStringCorrectly)
{
	testReplace("abcxxxabcxxxabcab", "abc", "yyy", "yyyxxxyyyxxxyyyab");
}
