
#include "stringList.h"
// Utils
char** MergeSort(char ***head){
    if((*head)[1] == NULL){
        return *head;
    }

    char **mid;
    char **mid_head;

    mid = MergeSortMiddle(head);
    mid_head = (char**)mid[1];
    mid[1] = NULL;

    char **a = MergeSort(&mid_head);
    char **b = MergeSort(head);
    char **final_head = Merge(&a, &b);

    return final_head;
}
char** Merge(char ***firstNode, char ***secondNode){
    char **result = NULL;
    if(*firstNode == NULL){
        return *secondNode;
    }
    else if(*secondNode == NULL){
        return *firstNode;
    }
    size_t len1 = strlen((*firstNode)[0]);
    size_t len2 = strlen((*secondNode)[0]);
    if(len1 <= len2){
        result = *firstNode;
        result[1] = Merge(&((*firstNode)[1]), secondNode);
    }
    else{
        result = *secondNode;
        result[1] = Merge(firstNode, &((*secondNode)[1]));
    }
    return result;
}
char** MergeSortMiddle(char ***head){
    char **slow = *head;
    char **fast = (char**)((*head)[1]);
    while(slow[1] && (fast && fast[1])){
        slow = (char**)slow[1];
        fast = (char**)fast[1];
        fast = (char**)fast[1];
    }
    return slow;
}

void StringListNullCheck(char ***list){
    if(list == NULL || *list == NULL ){
        printf("ERROR: NULL pointer exception;\n");
        exit(1);
    }
}
void StringListCheckInegrity(char ***list){
    StringListNullCheck(list);
    if(**list == NULL){
        printf("ERROR: Integrity check failed;\n");
        exit(1);
    }
}
void StringListCheck(char ***list, const char *param){
    StringListCheckInegrity(list);
    if(param == NULL){
        printf("ERROR: Parameter cannot be empty;\n");
        exit(1);
    }
}
void StringListFreeNode(char ***node){
    StringListNullCheck(node);
    free(**node);
    **node = NULL;
    free(*node);
    *node = NULL;
}
void StringListPrint(char ***list)
{   
    StringListCheckInegrity(list);
    char **temp = *list;
    while (temp)
    {
        printf("%s\n", temp[0]);
        temp = (char**)temp[1];
    }
}
// Actual functionality
void StringListInit(char ***list)
{
    *list = malloc(sizeof(char*)*2);
    StringListNullCheck(list);
    (*list)[0] = NULL;
    (*list)[1] = NULL;
}
void StringListDestroy(char ***list)
{
    StringListNullCheck(list);
    char **temp = *list;
    while(temp){
        char **node = temp;
        temp = (char**)temp[1];
        StringListFreeNode(&node);
    }
    *list = NULL;
}
void StringListAdd(char ***list, const char *str)
{
    StringListNullCheck(list);
    if(str == NULL){
        printf("ERROR: Parameter cannot be empty;\n");
        exit(1);
    }
    if((*list)[0] == NULL){
        (*list)[0] = malloc(sizeof(char) * strlen(str));
        strcpy((*list)[0], str);
    }
    else{
        char **temp = *list;
        while(temp[1]){
            temp = (char**)temp[1];
        }
        temp[1] = malloc(sizeof(char*)*2);
        char **node = (char**)temp[1];
        node[0] = malloc(sizeof(char) * strlen(str));
        strcpy(node[0], str);
        node[1] = NULL;
    }
}
void StringListRemove(char ***list, const char *str){
    StringListCheck(list, str);
    char **temp = *list;
    if(strcmp(temp[0], str) != 0 && temp[1] != NULL){
        char **next = temp[1];
        do {
            // strcmp returns 0 if they are equal
            if(strcmp(next[0], str) == 0){
                
                temp[1] = next[1];
                StringListFreeNode(&next);
                return;
            }
            next = (char**)next[1];
            temp = (char**)temp[1];
        }
        while(next);
    }
    else if(strcmp(temp[0], str) == 0){
        if(temp[1] == NULL){
            
            free(temp[0]);
            temp[0] = NULL;
            return;
        } 
        *list = (char**)((*list)[1]);
        StringListFreeNode(&temp);
    }
}
size_t StringListSize(char ***list) {
    StringListCheckInegrity(list);
    char **temp = *list;
    size_t index = 0;

    while(temp){
        temp = (char**)temp[1];
        index++;
    }
    return index;
}
size_t StringListIndexOf(char ***list, const char *str){
    StringListCheck(list, str);
    char **temp = *list;
    size_t index = 0;

    while(temp){
        // strcmp returns 0 if they are equal
        if(strcmp((temp[0]),str) == 0) {
            return index;
        }
        index++;
        temp = (char**)temp[1];
    }
    return -1;
}
void StringListRemoveDuplicates(char ***list){
    StringListCheckInegrity(list);
    char **str_to_compare = *list;
    char **str_to_compare_second;
    char **prev_node;
    
    // Compare first node with second, than with third, etc.
    while(str_to_compare){
        str_to_compare_second = (char**)str_to_compare[1];
        prev_node = str_to_compare;
        while (str_to_compare_second)
        {
            if(strcmp(*str_to_compare, *str_to_compare_second) == 0){
                prev_node[1] = str_to_compare_second[1];
                StringListFreeNode(&str_to_compare_second);
                str_to_compare_second = (char**)prev_node[1];
            }
            else{
                str_to_compare_second = (char**)str_to_compare_second[1];
                prev_node = (char**)prev_node[1];
            }
        }
        str_to_compare = (char**)str_to_compare[1];
    }
}
void StringListReplaceInStrings(char ***list, const char *before, const char *after){
    StringListCheckInegrity(list);
    if(*before == NULL || *after == NULL){
        printf("ERROR: Cannot replace with NULL pointer;\n");
        exit(1);
    }
    char **temp = *list;
    
    while(temp){
        char *s = temp[0];
        char* result; 
        int i, cnt = 0; 
        int newWlen = strlen(after); 
        int oldWlen = strlen(before); 

        for (i = 0; s[i] != '\0'; i++) { 
            if (strstr(&s[i], before) == &s[i]) { 
                cnt++; 
                i += oldWlen - 1; 
            } 
        } 

        result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1); 

        i = 0; 
        while (*s) { 
            if (strstr(s, before) == s) { 
                strcpy(&result[i], after); 
                i += newWlen; 
                s += oldWlen; 
            } 
            else
                result[i++] = *s++; 
        } 

        result[i] = '\0';
        char *to_free = temp[0];
        temp[0] = result;
        free(to_free);
        to_free = NULL;
        temp = temp[1]; 
    }

}
void StringListSort(char ***list){
    StringListCheckInegrity(list); 
    *list = MergeSort(list);
}
