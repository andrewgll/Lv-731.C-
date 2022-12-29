#pragma once 
#include "MyList.h"

void ListShow(char** list)
{
	if (!list)
	{
		return;
	}
	while (list)
	{
		printf("%s\n", list[0]);
		list = (char**)list[1];
	}
}

void StringListInit(char*** list)
{
	if (!list)
	{
		return;
	}
	*list = (char**)calloc(2, sizeof(char*));

	if (!(*list))
	{
		return;
	}
}

void StringListAdd(char** list, char* str)
{
	if (!list || !str)
	{
		return;
	}
	if (!list[0])
	{
		list[0] = (char*)calloc(strlen(str) + 1, sizeof(char));
		if (!list[0])
		{
			return;
		}
		strcpy_s(list[0], strlen(str) + 1, str);
	}
	else
	{
		while (list[1])
		{
			list = (char**)list[1];
		}
		list[1] = (char*)calloc(2, sizeof(char*));

		if (!list[1])
		{
			return;
		}
		list = (char**)list[1];
		list[0] = (char*)calloc(strlen(str) + 1, sizeof(char));

		if (!list[0])
		{
			return;
		}
		strcpy_s(list[0], strlen(str) + 1, str);
	}
}

void StringListRemove(char*** list, char* str)
{
	if (!list || !str)
	{
		return;
	}
	while ((*list) && !strcmp(**list, str))
	{
		char** temp = *list;
		*list = (char**)(*list)[1];

		free(*temp);
		free(temp);
		temp = NULL;
	}
	if ((*list) && (*list)[1])
	{
		char** previousNode = *list;
		char** currentNode = (char**)(*list)[1];

		while (previousNode[1])
		{
			if (!strcmp(*currentNode, str))
			{
				previousNode[1] = currentNode[1];
				free(*currentNode);
				free(currentNode);
				currentNode = (char**)previousNode[1];
			}
			else
			{
				previousNode = (char**)previousNode[1];
				currentNode = (char**)currentNode[1];
			}
		}
	}
}

int StringListSize(char** list)
{
	if (!list)
	{
		return 0;
	}
	int counter = 0;

	while (list)
	{
		++counter;
		list = (char**)list[1];
	}
	return counter;
}

void StringListDestroy(char*** list)
{
	if (!list)
	{
		return;
	}
	char** nextNode = (char**)(*list)[1];

	while (*list)
	{
		free(*(list)[0]);
		free(*list);
		*list = NULL;

		if (nextNode)
		{
			*list = nextNode;
			nextNode = (char**)nextNode[1];
		}
	}
}

int StringListIndexOf(char** list, char* str)
{
	if (!list || !str)
	{
		return -1;
	}
	int index = 0;

	while (list)
	{
		if (!strcmp(list[0], str))
		{
			return index;
		}
		++index;
		list = (char**)list[1];
	}
	return -1;
}

void StringListRemoveDuplicates(char** list)
{
	if (!list || StringListSize(list) < 2)
	{
		return;
	}
	while (list)
	{
		char** previousNode = list;
		char** nextNode = (char**)list[1];

		while (nextNode)
		{
			if (!strcmp(*list, *nextNode))
			{
				previousNode[1] = nextNode[1];
				free(*nextNode);
				free(nextNode);
				nextNode = (char**)previousNode[1];
			}
			else
			{
				previousNode = (char**)previousNode[1];
				nextNode = (char**)nextNode[1];
			}
		}
		list = (char**)list[1];
	}
}

void StringListSort(char** list)
{
	if (!list || StringListSize(list) < 2)
	{
		return;
	}
	while (list)
	{
		char** nextNode = (char**)list[1];

		while (nextNode)
		{
			if (strcmp(*list, *nextNode) > 0) {
				char* temp = *nextNode;
				*nextNode = *list;
				*list = temp;
				nextNode = (char**)nextNode[1];
			}
			else
			{
				nextNode = (char**)nextNode[1];
			}
		}
		list = (char**)list[1];
	}
}

void StringListReplaceInStrings(char** list, char* before, char* after)
{
	if (!list || !before || !after)
	{
		return;
	}
	if (!strcmp(before, after))
	{
		return;
	}
	while (list)
	{
		if (!strcmp(*list, before))
		{
			free(*list);
			list[0] = (char*)calloc(strlen(after) + 1, sizeof(char));
			if (!list[0])
			{
				return;
			}
			strcpy_s(*list, strlen(after) + 1, after);
		}
		list = (char**)list[1];
	}
}