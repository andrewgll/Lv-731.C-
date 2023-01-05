// by Oleh Klepatskyi
#include "pch.h"
#include "stdlib.h"
#include "string.h"

// this constant is used to determine
// whether the cell in the list is empty or not
static const char* const FREE_CELL = "";

template<typename T>
void swap(T& lhs, T& rhs)
{
	T temp = lhs;
	lhs = rhs;
	rhs = temp;
}

/* Initializes list */
void StringListInit(char**& list)
{
	list = static_cast<char**>(malloc(sizeof(char*)));
	if (list == nullptr)
		throw "StringListInit: Allocation error";
	list[0] = nullptr; // list is terminated by 0x0
}

/* Destroy list and set pointer to NULL. */
void StringListDestroy(char**& list)
{
	if (list == nullptr) return;
	char** iter = list;
	while (*iter != nullptr && *iter != FREE_CELL)
	{
		free(*iter);
		iter++;
	}
	free(list);
	list = nullptr;
}

// create new array of size (2*prev_size+1)
// and copy previous elements to start of the array
// other cells are initialized with FREE_CELL
// the last cell is always nullptr to represent the end of the list
void StringListRealloc(char**& list)
{
	int size = StringListSize(list);
	size_t newSize = 2 * size + 1;
	char** newList = (char**) realloc(list, (newSize + 1) * sizeof(char*));
	if (newList == nullptr)
		throw "StringListRealloc: Reallocation error";
	for (int i = size; i < newSize; i++)
		newList[i] = (char*) FREE_CELL;
	newList[newSize] = nullptr;
	list = newList;
}

/* Inserts value at the end of the list. */
void StringListAdd(char**& list, const char* str)
{
	if (str == nullptr) return;
	int size = StringListSize(list);
	if (list[size] == nullptr)
		StringListRealloc(list);
	size_t strSize = strlen(str);
	void* ptr = malloc((strSize + 1) * sizeof(char));
	char* newStr = (char*) ptr;
	if (newStr == nullptr)
		throw "StringAddList: allocation error";
	strcpy_s(newStr, strSize + 1, str);
	list[size] = newStr;
}

// sorts out all cells with value FREE_CELL that were
// deteleted during removal of item(s)
void moveEmptyCells(char** list)
{
	int j = 0, k = 0;
	while (list[j] != FREE_CELL) j++;
	k = j;
	while (list[k] == FREE_CELL) k++;
	while (list[k] != nullptr)
	{
		while (list[k] != FREE_CELL)
		{
			swap(list[j], list[k]);
			j++; k++;
		}
		while (list[k] == FREE_CELL) k++;
	}
}

/* Removes all occurrences of str in the list. */
void StringListRemoveAll(char** list, const char* str)
{
	if (list == nullptr) return;
	int size = StringListSize(list);
	for (int i = 0; i < size; i++)
	{
		if (strcmp(str, list[i]) == 0)
		{
			free(list[i]);
			list[i] = (char*) FREE_CELL;
		}
	}
	moveEmptyCells(list);
}

void StringListRemove(char** list, const char* str)
{
	if (list == nullptr) return;
	int size = StringListSize(list);
	for (int i = 0; i < size; i++)
	{
		if (strcmp(str, list[i]) == 0)
		{
			free(list[i]);
			list[i] = (char*) FREE_CELL;
			break;
		}
	}
	moveEmptyCells(list);
}

/* Returns the number of items in the list. */
int StringListSize(char** list)
{
	if (list == nullptr) return -1;
	int i = 0;
	while (list[i] != FREE_CELL && list[i] != nullptr) i++;
	return i;
}

/* Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf(char** list, const char* str)
{
	if (list == nullptr || str == nullptr) return -1;
	int i = 0;
	int size = StringListSize(list);
	while (strcmp(list[i], str) != 0 && i < size) i++;
	return i < size ? i : -1;
}

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char** list)
{
	if (list == nullptr) return;
	int i = 0;
	while(list[i] != FREE_CELL && list[i] != nullptr)
	{
		StringListRemoveAll(list+i+1, list[i]);
		i++;
	}
}

/* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
void StringListReplaceInStrings(char** list, const char* before, const char* after)
{
	if (list == nullptr || before == nullptr || after == nullptr) return;
	int size = StringListSize(list);
	for (int i = 0; i < size; i++)
	{
		char* old = list[i];
		list[i] = replace(old, before, after);
		free(old);
	}
}

int partition(char** array, int low, int high)
{
	const char* pivot = array[high];
	int i = (low - 1);
	for (int j = low; j < high; j++) {
		if (strcmp(array[j], pivot) <= 0) {
			i++;
			swap(array[i], array[j]);
		}
	}
	swap(array[i + 1], array[high]);
	return (i + 1);
}

void quickSort(char** array, int low, int high)
{
	if (low < high) {
		int pi = partition(array, low, high);
		quickSort(array, low, pi - 1);
		quickSort(array, pi + 1, high);
	}
}

/* Sorts the list of strings in ascending order */
void StringListSort(char** list)
{
	if (list == nullptr) return;
	quickSort(list, 0, StringListSize(list) - 1);
}
