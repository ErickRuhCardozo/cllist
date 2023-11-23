#include "linkedlist.c"
#include <string.h>

LINKED_LIST(char*, str)

bool printname(void* name)
{
    if (strcmp(*(char**)name, "James Doe") == 0) {
        printf(" James is not allowed here.\n");
        return false;
    }

    printf("[%s]->", *(char**)name);
    return true;
}

int main(void)
{
    str_linkedlist_t* names = ll_str_create();
    ll_str_add(names, "John Doe");
    ll_str_add(names, "Jane Doe");
    ll_str_add(names, "Joseph Doe");
    ll_str_add(names, "Jennifer Doe");
    ll_str_add(names, "James Doe");
    ll_str_traverse(names, printname);
    ll_str_free(names);
    return 0;
}
