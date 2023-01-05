// by Oleh Klepatskyi
#include "pch.h"
#include "StringList.h"
#include "MemoryLeakDetector.h"

TEST(StringList, CreatesEmptyList)
{
	MemoryLeakDetector d;
	char** list;
	StringListInit(list);
	EXPECT_EQ(StringListSize(list), 0);
	StringListDestroy(list);
}

TEST(StringList, CorrectlyAddsItem)
{
	MemoryLeakDetector d;
	char** list;
	const char* item = "item";
	StringListInit(list);
	StringListAdd(list, item);
	EXPECT_STR_EQ(item, list[0]);
	StringListDestroy(list);
}
TEST(StringList, RemovesFirstOccurrenceOfItem)
{
	MemoryLeakDetector d;
	char** list;
	const char* item = "item";
	const char* other = "other";
	StringListInit(list);
	StringListAdd(list, other);
	for (int i = 0; i < 5; i++)
		StringListAdd(list, item);
	size_t size = StringListSize(list);
	StringListRemove(list, item);
	EXPECT_STR_EQ(other, list[0]);
	EXPECT_EQ(StringListSize(list), size - 1);
	StringListDestroy(list);
}

TEST(StringList, RemovesAllOccurrencesInList)
{
	MemoryLeakDetector d;
	char** list;
	const char* item = "item";
	const char* other = "other";
	const int s = 5;
	StringListInit(list);
	for (int i = 0; i < s; i++)
	{
		StringListAdd(list, item);
		StringListAdd(list, other);
	}
	size_t size = StringListSize(list);
	StringListRemoveAll(list, item);
	EXPECT_STR_EQ(other, list[0]);
	EXPECT_EQ(StringListSize(list), size - s);
	StringListRemoveAll(list, other);
	EXPECT_EQ(StringListSize(list), 0);
	StringListDestroy(list);
}

TEST(StringList, CorrectlyDisplaysSize)
{
	MemoryLeakDetector d;
	char** list;
	const char* item = "item";
	
	const int created = 5;
	const int deleted = 2;
	StringListInit(list);
	for (int i = 0; i < created; i++)
	{
		StringListAdd(list, item);
	}
	for (int i = 0; i < deleted; i++)
		StringListRemove(list, item);
	EXPECT_EQ(StringListSize(list), created - deleted);
	StringListDestroy(list);
}

TEST(StringList, FindsFirstOccurrence)
{
	MemoryLeakDetector d;
	char** list;
	const char* item = "item";
	const char* other = "other";
	const int created = 5;
	const int index = 3;
	StringListInit(list);
	for (int i = 0; i < created; i++)
	{
		if (i == index)
			StringListAdd(list, item);
		StringListAdd(list, other);
	}
	EXPECT_EQ(StringListIndexOf(list, item), index);
	StringListDestroy(list);
}

TEST(StringList, RemovesDuplicateItemsFromList)
{
	MemoryLeakDetector d;
	char** list;
	const size_t size = 25;
	const char* data[size] = {
		"a", "a", "a", "a", "aaa",
		"ab", "abc", "b", "b", "b",
		"b", "b", "bbb", "c", "c",
		"c", "c", "c", "a", "bbb",
		"abc", "c", "aaa", "ab", "b"
	};
	const size_t expected_size = 7;
	const char* expected[expected_size] = {
		"a", "aaa", "ab", "abc", "b", "bbb", "c"
	};
	StringListInit(list);
	for (int i = 0; i < size; i++)
	{
		StringListAdd(list, data[i]);
	}
	StringListRemoveDuplicates(list);
	for (int i = 0; i < expected_size; i++)
	{
		EXPECT_STR_EQ(list[i], expected[i]);
	}
	StringListDestroy(list);
}

TEST(StringList, CorrectlyReplace_a_d)
{
	MemoryLeakDetector d;
	char** list;
	const size_t size = 7;
	const char* data[size] = {
		"a", "aaa", "ab", "abc", "b", "bbb", "c"
	};
	const char* expected[size] = {
		"d", "ddd", "db", "dbc", "b", "bbb", "c"
	};
	StringListInit(list);
	for (int i = 0; i < size; i++)
	{
		StringListAdd(list, data[i]);
	}
	StringListReplaceInStrings(list, "a", "d");
	for (int i = 0; i < size; i++)
	{
		EXPECT_STR_EQ(list[i], expected[i]);
	}
	StringListDestroy(list);
}

TEST(StringList, CorrectlyReplace_dd_e)
{
	MemoryLeakDetector d;
	char** list;
	const size_t size = 7;
	const char* data[size] = {
		"d", "ddd", "db", "dbc", "b", "bbb", "c"
	};
	const char* expected[size] = {
		"d", "ed", "db", "dbc", "b", "bbb", "c"
	};
	StringListInit(list);
	for (int i = 0; i < size; i++)
	{
		StringListAdd(list, data[i]);
	}
	StringListReplaceInStrings(list, "dd", "e");
	for (int i = 0; i < size; i++)
	{
		EXPECT_STR_EQ(list[i], expected[i]);
	}
	StringListDestroy(list);
}

TEST(StringList, CorrectlyReplace_bb_fff)
{
	MemoryLeakDetector d;
	char** list;
	const size_t size = 7;
	const char* data[size] = {
		"d", "ed", "db", "dbc", "b", "bbb", "c"
	};
	const char* expected[size] = {
		"d", "ed", "db", "dbc", "b", "fffb", "c"
	};
	StringListInit(list);
	for (int i = 0; i < size; i++)
	{
		StringListAdd(list, data[i]);
	}
	StringListReplaceInStrings(list, "bb", "fff");
	for (int i = 0; i < size; i++)
	{
		EXPECT_STR_EQ(list[i], expected[i]);
	}
	StringListDestroy(list);
}

TEST(StringList, CorrectlySorts)
{
	MemoryLeakDetector d;
	char** list;
	const size_t size = 18;
	const char* data[size] = { "aaa", "bbb", "abc", "b", "c", "a", "b", "c", "a", "b", "c", "a", "b", "c", "a", "b", "c", "ab" };
	const char* expected[size] = {
		"a", "a", "a", "a", "aaa",
		"ab", "abc", "b", "b", "b",
		"b", "b", "bbb", "c", "c",
		"c", "c", "c" };

	StringListInit(list);
	for (int i = 0; i < size; i++)
	{
		StringListAdd(list, data[i]);
	}
	StringListSort(list);
	for (int i = 0; i < size; i++)
	{
		EXPECT_STR_EQ(list[i], expected[i]);
	}
	StringListDestroy(list);
}