# Linked-List-Pointers-only-
This is a Linked List version based on pointers only; Still needs to be properly tested.

* So, this is implemented by double pointer sizeof(char*)*2, which contains array of two other pointers, ptr[0], which has actual string value and ptr[1] which points to another array of two pointers;


![picture](https://user-images.githubusercontent.com/58784803/209476002-54ed0072-64cf-404e-8432-023f055c57a1.png)

* So basicaly you can just write:
```
char **arr = malloc(sizeof(char*)*2);
```
and use it as:
```
arr[0] = "Hello";
arr[1] = malloc(sizeof(char*)*2);
```

* I used recursive merge sort and adapt it to work with Linked list because it gives the best performance in this situation, also no additional memory is allocated for this. 

* init.sh for max optimization and init_debug.sh for debuging

* valgrid.sh for memory leak testing
