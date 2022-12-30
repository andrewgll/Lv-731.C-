#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int items = 0;

#define BUFFER_SIZE 4096

void StringListInit(char*** strings)
{   
    *strings = (char**)malloc(sizeof(char*));   
}

char** StringListAdd(char** strings, char* str)
{
    if (items == 0) StringListInit(&strings);   
    else strings = (char**)realloc(strings, (items + 1) * sizeof(char*));
    
    items++;
 
    strings[items - 1] = (char*)malloc(strlen(str) * sizeof(char));
    strcpy(strings[items - 1], str);
    
    printf("string[%d] = %s\n\n", items, strings[items - 1]);
    
    return strings;
}

char** StringListRemove(char** strings, int num)
{
    for (int i = num; i < (items - 1); i++)
        strings[i] = strings[i + 1];
    
    strings[items - 1] = nullptr;
    items--;
    
    return strings;
}

char** StringListRemove(char** strings, char *str)
{
    for (int i = 0; i < items; i++)
        if (strcmp(strings[i], str) == 0)
        {
            for (int j = i; j < (items - 1); j++)
                strings[j] = strings[j + 1];
    
            strings[items - 1] = nullptr;
            items--;
            i--;
        }
    
    return strings;
}

int StringListSize(char** strings)
{
    int size = 0;
    
    for (int i = 0; i < items; i++) size++;
    
    return size;
}

int StringListIndexOf(char** strings, char* str)
{
    for (int i = 0; i < items; i++)
        if (strstr(strings[i], str) != NULL)
            return i + 1;
    
    return 0;
}

char** StringListRemoveDuplicates(char** strings)
{
    for (int i = 0; i < items; i++)
        for (int j = 0; j < (items - 1); j++)
            if ((strcmp(strings[i], strings[j]) == 0) && (i != j))
            {
                for (int k = j; k < (items - 1); k++)
                    strings[k] = strings[k + 1];
        
                strings[items - 1] = nullptr;
                items--; i--; j--;
            }
        
    return strings;
}

char** StringListReplaceInStrings(char** strings, char* before, char* after)
{
    for (int i = 0; i < items; i++)
        if (strstr(strings[i], before) != NULL)
        {
            if (strlen(before) == strlen(after))
                memcpy(strstr(strings[i], before), after, strlen(before));
            else 
            {
                char temp[BUFFER_SIZE], end[100], head[100]; int k = 0;
                memset(end, 0, strlen(end));
                memset(head, 0, strlen(head));
                
                strcpy(temp, strings[i]);
                
                for (int j = 0; j < strstr(strings[i], before) - strings[i]; j++)
                    head[j] = temp[j];
                
                for (int j = strstr(strings[i], before) - strings[i] + strlen(before); j < strlen(temp); j++)
                {
                    end[k] = temp[j];
                    k++;
                }

                memset(temp, 0, strlen(temp));
                
                int size = 0;
                
                for (int j = 0; j < strlen(head); j++)
                {
                    temp[size] = head[j];
                    size++;
                }
                    
                for (int j = 0; j < strlen(after); j++)
                {
                    temp[size] = after[j];
                    size++;
                } 
                
                for (int j = 0; j < strlen(end); j++)
                {
                    temp[size] = end[j];
                    size++;
                } 
                    
                strings[i] = nullptr;
                strings[i] = (char*)realloc(strings[i], (strlen(temp) * sizeof(char)));
                strings[i] = temp;
            }
        }
    
    return strings;
}

void StringListSort(char** strings)
{
    for(int i = 0; i < items - 1; i++)
        for(int j = i + 1; j < items; j++)
            if(strings[j] < strings[i])
            {
                char *tmp = strings[i];
                strings[i] = strings[j];
                strings[j] = tmp;
            }
}

void StringListDestroy(char*** strings)
{
    items = 0;
    
    for (int i = 0; i < items; i++)
        free(strings[i]);
    free(*strings);
}

void Output(char** strings)
{
    for (int i = 0; i < items; i++)
        printf("string[%d] = %s\n", i + 1, strings[i]);
        
    printf("\n");
}

int main()
{
	char** strings = nullptr;
	char buffer[BUFFER_SIZE];
	int ch = 0; 
	
	printf("1. Add the string;\n");
	printf("2. Delete the string by id;\n");
	printf("3. Delete the string by str;\n");
	printf("4. The number of items in the list;\n");
	printf("5. The index position of the first occurrence of str in the list;\n");
	printf("6. Removes duplicate entries from the list;\n");
	printf("7. Replaces every occurrence of the before, in each of the string lists's strings, with after;\n");
	printf("8. Sorts the list of strings in ascending order;\n");
	printf("9. Output strings;\n");
	printf("10. Exit.\n");
	
	while (ch < 10)
	{
	    printf("Enter the number -> ");
	    scanf("%d", &ch);
	    
	    if (ch == 1)
	    {
	        printf("\nEnter the string:\n");
	        while(getchar() != '\n');
            fgets(buffer, BUFFER_SIZE, stdin);
	        buffer[strlen(buffer) - 1] = '\0';
	        strings = StringListAdd(strings, buffer);
	    }
	    if (ch == 2) 
	    {
	        int num;
	        printf("\nEnter the id in order to delete: ");
	        scanf("%d", &num);
	        strings = StringListRemove(strings, num);
	    }
	    if (ch == 3)
	    {
	        printf("\nEnter the string in order to delete:\n");
	        while(getchar() != '\n');
	        fgets(buffer, BUFFER_SIZE, stdin);
	        buffer[strlen(buffer) - 1] = '\0';
	        strings = StringListRemove(strings, buffer);
	    }
	    if (ch == 4) printf("\nSize of the list: %d\n\n", StringListSize(strings));
	    if (ch == 5)
	    {
	        printf("\nEnter the string in order to find:\n");
	        while(getchar() != '\n');
	        fgets(buffer, BUFFER_SIZE, stdin);
	        buffer[strlen(buffer) - 1] = '\0';
	        
	        int result = StringListIndexOf(strings, buffer);
	        
	        if (result == 0)
	            printf ("\nStrings is not founded!\n\n");
	        else
	            printf ("\nStrings is find: %d\n\n", result);
	    }
	    if (ch == 6) strings = StringListRemoveDuplicates(strings);
	    if (ch == 7)
	    {
	        char after[BUFFER_SIZE];
	        
	        printf("\nEnter the string before:\n");
	        while(getchar() != '\n');
	        fgets(buffer, BUFFER_SIZE, stdin);
	        buffer[strlen(buffer) - 1] = '\0';
	        
	        printf("Enter the string after:\n");
	        fgets(after, BUFFER_SIZE, stdin);
	        after[strlen(after) - 1] = '\0';
	        
	        strings = StringListReplaceInStrings(strings, buffer, after);
	    }
	    if (ch == 8) StringListSort(strings);
	    if (ch == 9) Output(strings);
	}
	
	StringListDestroy(&strings);
	return 0;
}
