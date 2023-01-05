// by Oleh Klepatskyi
#ifndef _KLEPATSKYI_STRING_LIST_
#define _KLEPATSKYI_STRING_LIST_

/*
Defines an interface for a dynamically sized list of c-strings.
Implementation is dynamic array, similar to std::vector.
Sort implementation is quick sort.
 
Implemented requirements:
+ 1) Only stdlib.h and string.h headers are used in file where the list is implemented.
+ 2) No new or delete operators. Only malloc, realloc and free functions.
+ 3) NO classes or structures. Only pointers are used.
+ 4) You can use ANY code convention you like
+ 5) User should be able to:
    + add/remove string
     + in addition: remove first/all identical strings
    + get the number of items in the list
    + get the index position of the first exact match of specified string
    + remove duplicates (identical items in list)
    + replace the text in items
    + sort list
*/

/* Initializes list */
void StringListInit(char**& list);

/* Destroy list and set pointer to NULL. */
void StringListDestroy(char**& list);

/* Inserts value at the end of the list. */
void StringListAdd(char**& list, const char* str);

/* Removes all occurrences of str in the list. */
void StringListRemoveAll(char** list, const char* str);

/* Removes firsrt occurrence of str in the list. */
void StringListRemove(char** list, const char* str);

/* Returns the number of items in the list. */
int StringListSize(char** list);

/* Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf(char** list, const char* str);

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char** list);

/* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
void StringListReplaceInStrings(char** list, const char* before, const char* after);

/* Sorts the list of strings in ascending order */
void StringListSort(char** list);

#endif