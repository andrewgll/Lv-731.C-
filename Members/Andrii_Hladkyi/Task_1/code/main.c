#include "../headers/stringList.h"

int TestFunc(char ***list){
    StringListAdd(list, "Hi");
}
int main(){
    size_t test_n = 0;
    char **list;
    StringListInit(&list);
    StringListAdd(&list, "Hello");
    StringListRemove(&list, "Hell");
    StringListRemove(&list, "He");
    StringListRemove(&list, "Helo");
    StringListRemove(&list, "Hel");
    StringListAdd(&list, "Hi");
    StringListRemove(&list, "Hi"); 
    StringListAdd(&list, "Hi");
    StringListAdd(&list, "Hi");
    StringListAdd(&list, "Hi");
    StringListAdd(&list, "Hi");
    StringListAdd(&list, "HjiIh");

    StringListPrint(&list);
    StringListSort(&list);

    printf("***\n");
    StringListPrint(&list);

    printf("***\n");
    StringListReplaceInStrings(&list, "H", "X");
    StringListPrint(&list);

    StringListAdd(&list, "Hi World Hi");
    StringListAdd(&list, "Hi World Hi");
    StringListReplaceInStrings(&list, "Hi", "Hello");

    printf("***\n");
    StringListPrint(&list);

    StringListRemoveDuplicates(&list);
    printf("***\n");
    StringListPrint(&list);

    StringListSort(&list);
    printf("***\n");
    StringListPrint(&list);


    printf("***\n");
    printf("%i\n", StringListIndexOf(&list, "Xello"));

    printf("***\n");
    StringListPrint(&list);

    printf("***\n");
    printf("%i\n", StringListSize(&list));


    StringListAdd(&list, "Test test");
    printf("***\n");
    StringListPrint(&list);
    
    StringListDestroy(&list);
   return 0; 
}