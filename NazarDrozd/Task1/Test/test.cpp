#include "pch.h"
#include "../MyList.h"
#include "../MyList.cpp"

TEST(MyList, MyListInit)
{
	char** list = NULL;
	StringListInit(&list);
	EXPECT_EQ(0, StringListSize(list));
	StringListDestroy(&list);
}

TEST(MyList, MyListAddElement)
{
	char** list = NULL;
	StringListInit(&list);

	StringListAdd(list, "TestStr0");
	StringListAdd(list, "TestStr1");
	StringListAdd(list, "TestStr2");
	StringListAdd(list, "TestStr3");
	StringListAdd(list, "TestStr4");

	EXPECT_EQ(5, StringListSize(list));
	StringListDestroy(&list);
}

TEST(MyList, MyListAddEmptyElement)
{
	char** list = NULL;
	StringListInit(&list);

	StringListAdd(list, nullptr);

	EXPECT_EQ(0, StringListSize(list));
	StringListDestroy(&list);
}

TEST(MyList, MyListRemoveElement)
{
	char** list = NULL;
	StringListInit(&list);

	StringListAdd(list, "TestStr0");
	StringListAdd(list, "TestStr1");
	StringListAdd(list, "TestStr2");
	StringListAdd(list, "TestStr3");
	StringListAdd(list, "TestStr4");
	EXPECT_EQ(5, StringListSize(list));

	StringListRemove(&list, "TestStr0");
	StringListRemove(&list, "TestStr1");
	StringListRemove(&list, "TestStr2");
	StringListRemove(&list, "TestStr3");
	StringListRemove(&list, "TestStr4");

	EXPECT_EQ(0, StringListSize(list));
	StringListDestroy(&list);
}

TEST(MyList, MyListRemoveInvalidElement)
{
	char** list = NULL;
	StringListInit(&list);

	StringListAdd(list, "TestStr0");
	StringListAdd(list, "TestStr1");

	StringListRemove(&list, "TestStr2");
	StringListRemove(&list, nullptr);

	EXPECT_EQ(2, StringListSize(list));
	StringListDestroy(&list);
}

TEST(MyList, MyListSize)
{
	char** list = NULL;
	StringListInit(&list);
	EXPECT_EQ(0, StringListSize(list));

	StringListAdd(list, "TestStr0");
	EXPECT_EQ(1, StringListSize(list));

	StringListAdd(list, "TestStr1");
	EXPECT_EQ(2, StringListSize(list));

	StringListRemove(&list, "TestStr0");
	EXPECT_EQ(1, StringListSize(list));

	StringListAdd(list, "TestStr2");
	StringListAdd(list, "TestStr3");
	StringListAdd(list, "TestStr4");
	EXPECT_EQ(4, StringListSize(list));

	StringListRemove(&list, "TestStr1");
	StringListRemove(&list, "TestStr2");
	StringListRemove(&list, "TestStr3");
	EXPECT_EQ(1, StringListSize(list));

	StringListDestroy(&list);
	EXPECT_EQ(0, StringListSize(list));
}

TEST(MyList, MyListDestroy)
{
	char** list = NULL;
	StringListInit(&list);

	StringListAdd(list, "TestStr0");
	StringListAdd(list, "TestStr1");
	EXPECT_EQ(2, StringListSize(list));
	StringListDestroy(&list);
	EXPECT_EQ(0, StringListSize(list));
}

TEST(MyList, MyListDestroyEmpty)
{
	char** list = NULL;
	StringListInit(&list);
	StringListDestroy(&list);
	EXPECT_EQ(0, StringListSize(list));
}

TEST(MyList, MyListIndexOf)
{
	char** list = NULL;
	StringListInit(&list);

	EXPECT_EQ(-1, StringListIndexOf(list, "TestStr0"));

	StringListAdd(list, "TestStr0");
	EXPECT_EQ(0, StringListIndexOf(list, "TestStr0"));

	StringListAdd(list, "TestStr1");
	EXPECT_EQ(1, StringListIndexOf(list, "TestStr1"));

	StringListAdd(list, "TestStr2");
	EXPECT_EQ(2, StringListIndexOf(list, "TestStr2"));

	StringListAdd(list, "TestStr3");
	StringListAdd(list, "TestStr4");
	EXPECT_EQ(4, StringListIndexOf(list, "TestStr4"));

	StringListRemove(&list, "TestStr4");
	EXPECT_EQ(-1, StringListIndexOf(list, "TestStr4"));
	StringListDestroy(&list);
}

TEST(MyList, MyListRemoveDublicates)
{
	char** list = NULL;
	StringListInit(&list);

	StringListAdd(list, "TestStr0");
	StringListAdd(list, "TestStr0");
	StringListAdd(list, "TestStr1");
	StringListAdd(list, "TestStr1");
	StringListAdd(list, "TestStr1");
	StringListAdd(list, "TestStr2");
	StringListAdd(list, "TestStr3");
	StringListAdd(list, "TestStr3");
	StringListAdd(list, "TestStr4");

	StringListRemoveDuplicates(list);

	EXPECT_EQ(5, StringListSize(list));
	StringListDestroy(&list);
}

TEST(MyList, MyListSort)
{
	char** list = NULL;
	StringListInit(&list);

	StringListAdd(list, "bc");
	StringListAdd(list, "bb");
	StringListAdd(list, "ba");
	StringListAdd(list, "ac");
	StringListAdd(list, "ab");
	StringListAdd(list, "aa");

	StringListSort(list);
	
	EXPECT_EQ(0, StringListIndexOf(list, "aa"));
	EXPECT_EQ(1, StringListIndexOf(list, "ab"));
	EXPECT_EQ(2, StringListIndexOf(list, "ac"));
	EXPECT_EQ(3, StringListIndexOf(list, "ba"));
	EXPECT_EQ(4, StringListIndexOf(list, "bb"));
	EXPECT_EQ(5, StringListIndexOf(list, "bc"));
	StringListDestroy(&list);
}

TEST(MyList, MyListReplaceInStrings)
{
	char** list = NULL;
	StringListInit(&list);

	StringListAdd(list, "TestStr0");
	StringListAdd(list, "TestStr1");
	StringListAdd(list, "TestStr2");

	StringListReplaceInStrings(list, "Test", "");
	
	EXPECT_STREQ("Str0", *list);
	list = (char**)list[1];
	EXPECT_STREQ("Str1", *list);
	list = (char**)list[1];
	EXPECT_STREQ("Str2", *list);
	StringListDestroy(&list);
}