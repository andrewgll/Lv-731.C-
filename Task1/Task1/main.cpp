// by Oleh Klepatskyi
#include "StringList.h"
#include "StringUtil.h"

#include <iostream>
using namespace std;

void printStringList(char** list)
{
	int size = StringListSize(list);
	cout << "StringList (size=" << size << ")[";
	if (size == 0) cout << "]";
	else for (int i = 0; i < size; i++)
		cout << list[i] << (i == size - 1 ? "]" : ", ");
	cout << endl;
}

// Usage example
int main()
{
	char** list = nullptr;
	StringListInit(list);
	cout << "Init list\n";
	printStringList(list);
	StringListAdd(list, "aaa");
	cout << "Added 'aaa'\n";
	printStringList(list);
	StringListAdd(list, "bbb");
	cout << "Added 'bbb'\n";
	printStringList(list);
	StringListAdd(list, "abc");
	cout << "Added 'abc'\n";
	printStringList(list);
	for (int i = 0; i < 5; i++)
	{
		StringListAdd(list, "a");
		StringListAdd(list, "b");
		StringListAdd(list, "c");
	}
	cout << "Added strings 'a', 'b', 'c' 5 times\n";
	printStringList(list);
	StringListRemove(list, "a");
	cout << "Removed 'a'\n";
	printStringList(list);
	StringListAdd(list, "ab");
	cout << "Added 'ab'\n";
	printStringList(list);
	cout << "Index of 'abc': " << StringListIndexOf(list, "abc") << endl;
	StringListSort(list);
	cout << "Sorted list:\n";
	printStringList(list);
	cout << "Index of 'abc': " << StringListIndexOf(list, "abc") << endl;
	StringListRemoveDuplicates(list);
	cout << "Removed duplicates:\n";
	printStringList(list);
	StringListReplaceInStrings(list, "a", "d");
	cout << "Replaced substring 'a' -> 'd':\n";
	printStringList(list);
	StringListReplaceInStrings(list, "dd", "e");
	cout << "Replaced substring 'dd' -> 'e':\n";
	printStringList(list);
	StringListReplaceInStrings(list, "bb", "fff");
	cout << "Replaced substring 'bb' -> 'fff':\n";
	printStringList(list);
	StringListDestroy(list);
	return 0;
}
