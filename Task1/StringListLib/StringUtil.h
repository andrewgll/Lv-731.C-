// by Oleh Klepatskyi
#ifndef _KLEPATSKYI_STRING_UTIL_
#define _KLEPATSKYI_STRING_UTIL_

// Finds a index of first occurrence of substr in str.
// start param (the starting index of search) is optional and is 0 by default
// (thus, the whole string is checked for substring).
// If such substr was not found in str in [start, strlen(str)], -1 returned.
int find(const char* str, const char* substr, size_t start = 0);

// Replaces all occurrences of string 'before' in 'dst' to 'after'.
// Memory for new string is allocated and the address of that memory is returned
char* replace(const char* string, const char* before, const char* after);

#endif // _KLEPATSKYI_STRING_LIST_UTIL_
