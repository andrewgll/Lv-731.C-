#include <iostream>
#include "MyList.h"

int main()
{
	char** node = NULL;

	char str0[10] = "string0";
	char str1[10] = "string1";
	char str2[10] = "string2";

	StringListInit(&node);
	StringListAdd(node, str0);
	StringListAdd(node, str1);
	StringListAdd(node, str2);

	std::cout << "List size =  " << StringListSize(node) << "\n\n";
	StringListShow(node);

	StringListReplaceInStrings(node, str1, str2);

	std::cout << "\nList size =  " << StringListSize(node) << "\n\n";
	StringListShow(node);

	std::cout << "\nList destroy\n";
	StringListDestroy(&node);
	std::cout << "List size =  " << StringListSize(node) << "\n\n";
	StringListShow(node);

	return 0;
}