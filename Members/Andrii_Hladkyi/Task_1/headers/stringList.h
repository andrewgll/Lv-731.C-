#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#ifndef stringList
#define stringList

    /* Initializes list */
    void StringListInit(char*** list);
    /* Destroy list and set pointer to NULL. */
    void StringListDestroy(char*** list);

    /* Inserts value at the end of the list. */
    void StringListAdd(char*** list, const char* str);
    /* Removes all occurrences of str in the list. */
    void StringListRemove(char*** list, const char* str);

    /* Returns the number of items in the list. */
    size_t StringListSize(char*** list);
    /* Returns the index position of the first occurrence of str in the list. */
    size_t StringListIndexOf(char*** list, const char* str);

    /* Removes duplicate entries from the list. */
    void StringListRemoveDuplicates(char*** list);
    /* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
    void StringListReplaceInStrings(char*** list, const char* before, const char* after);
    /* Sorts the list of strings in ascending order */
    void StringListSort(char*** list);
    // Prints all Nodes by iterating over it.
    void StringListPrint(char*** list);
    // Checks if List is NULL.
    void StringListNullCheck(char*** list);
    
    void StringListFreeNode(char*** list);
    // Checks if list is usable for operations. Checks if node value is not NULL.
    void StringListCheckInegrity(char*** list);
    // Checks if parameter not null. 
    // Checks if list is usabe for operations. 
    // Checks if node value is not NULL.
    void StringListCheck(char ***list, const char *str);
    // Linked list version of Merge Sort.
    char** MergeSort(char ***head);
    // Find middle by advancing fast for 2 pointers and slow for 1.
    char** MergeSortMiddle(char ***head);
    // Merge sorted lists.
    char** Merge(char ***firstNode, char ***secondNode);

#endif