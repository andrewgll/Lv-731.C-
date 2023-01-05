// by Oleh Klepatskyi
#include "pch.h"
#include "stdlib.h"
#include "string.h"

int find(const char* str, const char* substr, size_t start)
{
	size_t strSize = strlen(str);
	size_t substrSize = strlen(substr);

	if (strSize == 0 || substrSize == 0)
		return -1;

	for (size_t i = start; i < strSize - substrSize + 1; i++)
	{
		int j = 0;
		while (str[i + j] == substr[j] && substr[j] != '\0')
			j++;
		if (substr[j] == '\0')
			return (int) i;
	}
	return -1;
}

void findAllSubstrings(const char* str, const char* substr, size_t*& indexes, int& total)
{
	size_t len = strlen(str);
	size_t substrLen = strlen(substr);
	total = 0;
	indexes = (size_t*)malloc(len * sizeof(size_t));
	if (indexes == nullptr)
		throw "findAllSubstrings: Allocation error";
	size_t current = 0;
	while ((current = find(str, substr, current)) != -1)
	{
		indexes[total++] = current;
		current += substrLen;
	}
}

char* replaceAllSubstrings(const char* str, const char* before, const char* after, const size_t* indexes, int total)
{
	const size_t len = strlen(str);
	const size_t beforeLen = strlen(before);
	const size_t afterLen = strlen(after);
	const int diff = afterLen - beforeLen;
	const size_t newLen = len + diff * total;
 	char* newStr = (char*) malloc((newLen + 1) * sizeof(char));
	if (newStr == nullptr)
		throw "replaceAllSubstrings: Allocation error";
	newStr[newLen] = '\0';
	int current = 0;
	for (size_t i = 0, j = 0; i < newLen;)
	{
		if (indexes[current] != j)
		{
			newStr[i++] = str[j++];
		}
		else
		{
			for (int k = 0; k < afterLen;)
			{
				newStr[i++] = after[k++];
			}
			j += beforeLen;
			current++;
		}
	}
	return newStr;
}

char* replace(const char* string, const char* before, const char* after)
{
	size_t* indexes = nullptr;
	int total = 0;
	findAllSubstrings(string, before, indexes, total);
	char* res = replaceAllSubstrings(string, before, after, indexes, total);
	free(indexes);
	return res;
}
