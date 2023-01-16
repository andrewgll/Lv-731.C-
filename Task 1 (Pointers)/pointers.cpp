#include <stdlib.h>
#include <string.h>

extern "C"
{
  int printf(const char *__format, ...);
  int scanf(const char *__format, ...);
}

#define STR_MAX_SIZE 255

enum Menu
{
  DESTROY_LIST_AND_QUIT,
  ADD_NEW_ELEMENT,
  DELETE_ELEMENT,
  // REMOVE_SIMILAR_ELEMENTS_WITH,
  CALCULATE_AMOUNT_OF_ELEMENTS,
  FIND_FIRST_EXACT_OCCURRENCE_WITH,
  MAKE_UNIQUE_ELEMENTS,
  // REWRITE_SPECIFIC_ELEMENT,
  // SORT_ELEMENTS,
  PRINT_ENTIRE_LIST,
};

/* Prints menu for navigation over program. */
void ShowMenu();

/* Destroy list and set pointer to NULL. */
void StringListDestroy(char **list);

/* Initializes list */
char **StringListInit(const char *first);

/* Inserts value at the end of the list. */
void StringListAdd(char **head, char *data);

/* Removes all occurrences of str in the list. */
void StringListRemove(char **list, char *str, int &list_element_counter);

/* Returns the number of items in the list. */
void StringListSize(int &list_element_counter);

/* Returns the index position of the first occurrence of str in the list. */
void StringListIndexOf(char **list, char *str);

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char **list, int &list_element_counter);

// /* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
// void StringListReplaceInStrings(char **list, char *before, char *after);

// /* Sorts the list of strings in ascending order */
// void StringListSort(char** list);

void PrintEntireList(char **head);

int main()
{

  int list_element_counter = 1;
  printf("First of all, initialize first element of the List: ");
  char str[STR_MAX_SIZE];
  scanf(" %[^\n]с", &str);
  char **head = StringListInit(str);

  while (true)
  {
    ShowMenu();
    printf("Choose your option: ");
    short option;
    scanf("%i", &option);
    switch (option)
    {
    case DESTROY_LIST_AND_QUIT:
      StringListDestroy(head);
      printf("List was successfully deleted!");
      return 0;
      break;
    
    case ADD_NEW_ELEMENT:
      scanf(" %[^\n]с", &str);
      StringListAdd(head, str);
      list_element_counter += 1;
      break;

    case DELETE_ELEMENT:
      scanf(" %[^\n]с", &str);
      StringListRemove(head, str, list_element_counter);
      break;

    case CALCULATE_AMOUNT_OF_ELEMENTS:
      StringListSize(list_element_counter);
      break;

    case FIND_FIRST_EXACT_OCCURRENCE_WITH:
      scanf(" %[^\n]с", &str);
      StringListIndexOf(head, str);
      break;

    case MAKE_UNIQUE_ELEMENTS:
      StringListRemoveDuplicates(head, list_element_counter);
      break;

    // case REWRITE_SPECIFIC_ELEMENT:
    // {
    //   char before[STR_MAX_SIZE];
    //   char after[STR_MAX_SIZE];
    //   scanf(" %[^\n]с", &before);
    //   scanf(" %[^\n]с", &after);
    //   StringListReplaceInStrings(head, before, after);
    //   break;
    // }

    // case SORT_ELEMENTS:
    //   break;

    case PRINT_ENTIRE_LIST:
      PrintEntireList(head);
      break;

    
    default:
      printf("Impossible input!");
      break;
    }
  }
}

/* Prints menu for navigation over program. */
void ShowMenu()
{
  printf("\nPossible options: \n");
  printf("1)Add new element to the list. \n");
  printf("2)Delete specific element. \n");
  printf("3)Calculate amount of elements in the list. \n");
  printf("4)Find first exact occurrence with ... \n");
  printf("5)Make Unique list elements. \n");
  printf("6)Rewrite specific element. \n");
  //printf("7)Sort list elements. \n");
  printf("7)Print entire list. \n");
  printf("0)Destroy list and exit. \n");
}

/* Destroy list and set pointer to NULL. */
void StringListDestroy(char **list)
{
  char **temp = (char **)malloc(sizeof(char **));
  while (list != nullptr)
  {
    temp = (char **)list[0];
    free(list[1]);
    free(list);
    list = (char **)temp;
  }
  free(temp);
}

/* Initializes list */
char **StringListInit(const char *first)
{
  char **head = (char **)malloc(2 * sizeof(char *));
  head[0] = nullptr;
  head[1] = (char *)(malloc(strlen(first) + 1));
  memcpy(head[1], first, (strlen(first) + 1));
  return head;
}

/* Inserts value at the end of the list. */
void StringListAdd(char **head, char *data)
{
  char **tmp = head;
  while (tmp[0] != nullptr)
  {
    tmp = (char **)tmp[0];
  }
  tmp[0] = (char *)StringListInit(data);
}

/* Removes all occurrences of str in the list. */
void StringListRemove(char **list, char *str, int &list_element_counter)
{
  char **str_to_compare = list;
  char **str_to_compare_second;
  char **prev_node;

  // Compare first node with second, than with third, etc.
  while (str_to_compare)
  {
    str_to_compare_second = (char **)str_to_compare[0];
    prev_node = str_to_compare;
    while (str_to_compare_second)
    {
      if (strcmp(str, str_to_compare_second[1]) == 0)
      {
        prev_node[0] = str_to_compare_second[0];
        free(str_to_compare_second[1]);
        free(str_to_compare_second);
        list_element_counter--;
        str_to_compare_second = (char **)prev_node[0];
      }
      else
      {
        str_to_compare_second = (char **)str_to_compare_second[0];
        prev_node = (char **)prev_node[0];
      }
    }
    str_to_compare = (char **)str_to_compare[0];
  }
}

/* Returns the number of items in the list. */
void StringListSize(int &list_element_counter)
{
  printf("Your list contains: %i elements.", list_element_counter);
}

/* Returns the index position of the first occurrence of str in the list. */
void StringListIndexOf(char **list, char *str)
{
  char **str_to_compare = list;
  char **str_to_compare_second;
  char **prev_node;
  short index = 0;

  // Compare first node with second, than with third, etc.

  str_to_compare_second = (char **)str_to_compare[0];
  prev_node = str_to_compare;
  while (str_to_compare_second)
  {
    if (strstr(str_to_compare_second[1], str) == 0)
    {
      prev_node[0] = str_to_compare_second[0];
      str_to_compare_second = (char **)prev_node[0];
      index++;
    }
    else
    {
      index++;
      printf("\n%i\n", index);
      str_to_compare_second = (char **)str_to_compare_second[0];
      prev_node = (char **)prev_node[0];
    }
  }
  printf("\nThere were no occurrences found.\n");
}

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char **list, int &list_element_counter) 
{
  char **str_to_compare = list;
  char **str_to_compare_second;
  char **prev_node;

  // Compare first node with second, than with third, etc.
  while (str_to_compare)
  {
    str_to_compare_second = (char **)str_to_compare[0];
    prev_node = str_to_compare;
    while (str_to_compare_second)
    {
      if (strcmp(str_to_compare[1], str_to_compare_second[1]) == 0)
      {
        prev_node[0] = str_to_compare_second[0];
        free(str_to_compare_second[1]);
        free(str_to_compare_second);
        list_element_counter--;
        str_to_compare_second = (char **)prev_node[0];
      }
      else
      {
        str_to_compare_second = (char **)str_to_compare_second[0];
        prev_node = (char **)prev_node[0];
      }
    }
    str_to_compare = (char **)str_to_compare[0];
  }
}

// /* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
// void StringListReplaceInStrings(char **list, char *before, char *after)
// {
//   char **str_to_compare = list;
//   char *str;
//   char **prev_node;
//   short index;
//   while (str_to_compare)
//   {
//     str = (char *)str_to_compare[1];
//     prev_node = str_to_compare;
//     while (str)
//     {
//       if (strstr(str_to_compare[1], str) == 0)
//       {
//         str = (char *)prev_node[0];
//       }
//       else
//       {
//         str = (char *)str[0];
//         prev_node = (char **)prev_node[0];
//       }
//     }
//     str_to_compare = (char **)str_to_compare[0];
//   }
// }

/* Sorts the list of strings in ascending order */
void StringListSort(char **list)
{
  char **str_to_compare = list;
  char **str_to_compare_second;
  char *str;
  char **prev_node;

  // Compare first node with second, than with third, etc.
  while (str_to_compare)
  {
    str_to_compare_second = (char **)str_to_compare[0];
    prev_node = str_to_compare;
    while (str_to_compare_second)
    {
      if (strcmp(str, str_to_compare_second[1]) == 0)
      {
        prev_node[0] = str_to_compare_second[0];

        str_to_compare_second = (char **)prev_node[0];
      }
      else
      {
        str_to_compare_second = (char **)str_to_compare_second[0];
        prev_node = (char **)prev_node[0];
      }
    }
    str_to_compare = (char **)str_to_compare[0];
  }
}

void PrintEntireList(char **head)
{
  short index = 0;
  printf("Your list is: \n");
  while (head)
  {
    printf(":%i: %s\n", index, (char *)(head[1]));

    // printf("\n Address: %lli \n", &(head[1]));

    head = (char **)head[0];
    index++;
  }
  printf("\n");
}