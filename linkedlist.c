#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LINKED_LIST(type, name) \
typedef struct name##_node { \
    type value; \
    struct name##_node* next; \
} node_ ## name ## _t; \
\
typedef struct name##_linkedlist { \
    size_t size; \
    node_ ## name ##_t* head; \
    node_ ## name ##_t* tail; \
} name##_linkedlist_t; \
\
node_ ## name ##_t* create_ ## name ## _node(type value) \
{ \
    node_ ## name ##_t* node = malloc(sizeof(node_ ## name ## _t)); \
    node->value = value; \
    node->next = NULL; \
    return node; \
} \
\
name##_linkedlist_t* ll_ ## name ## _create() \
{ \
    name##_linkedlist_t* list = malloc(sizeof(name##_linkedlist_t)); \
    list->size = 0; \
    list->head = NULL; \
    list->tail = NULL; \
    return list; \
} \
\
size_t ll_## name ##_size(name##_linkedlist_t* list) \
{ \
    return list->size; \
} \
\
void ll_ ## name ## _add(name##_linkedlist_t* list, type value) \
{ \
    node_ ## name ## _t* newnode = create_ ## name ## _node(value); \
\
    if (list->size == 0) { \
        list->head = newnode; \
        list->tail = newnode; \
    } else { \
        list->tail->next = newnode; \
        list->tail = newnode; \
    } \
\
    ++list->size; \
} \
\
void ll_ ## name ##_insert(name##_linkedlist_t* list, size_t index, type value) \
{\
    node_ ## name ## _t* newnode = create_ ## name ## _node(value); \
\
    if (index == 0) { \
        newnode->next = list->head; \
        list->head = newnode; \
    } else { \
        node_ ## name ## _t* previous = list->head; \
        node_ ## name ## _t* current = list->head; \
\
        for (int i = 0; i < index; ++i) { \
            if (current->next == NULL) \
                break; \
\
            previous = current; \
            current = current->next; \
        } \
\
        if (current == list->tail) { \
            current->next = newnode; \
            list->tail = newnode; \
        } else { \
            previous->next = newnode; \
            newnode->next = current; \
        } \
    } \
\
    ++list->size; \
} \
\
int ll_ ## name ## _index(name##_linkedlist_t* list, type value, bool (*comparator)(void*, void*)) \
{ \
    node_ ## name ## _t* current = list->head; \
\
    for (int i = 0; i < list->size; ++i) { \
        if (comparator(&current->value, &value)) \
            return i; \
\
        current = current->next; \
    } \
\
    return -1; \
} \
\
bool ll_ ## name ## _has(name##_linkedlist_t* list, type value, bool (*comparator)(void*, void*)) \
{ \
    node_ ## name ## _t* current = list->head; \
\
    while (current) { \
        if (comparator(&current->value, &value)) \
            return true; \
\
        current = current->next; \
    } \
\
    return false; \
} \
\
bool ll_ ## name ## _remove(name##_linkedlist_t* list, type value, bool (*comparator)(void*, void*)) \
{\
    if (list->size == 0) \
        return false; \
\
    node_ ## name ## _t* current = list->head; \
    node_ ## name ## _t* previous = list->head; \
\
    while (current) { \
        if (comparator(&current->value, &value)) { \
            if (current == list->head) \
                list->head = current->next; \
            else \
                previous->next = current->next; \
\
            free(current); \
            --list->size; \
            return true; \
        } \
\
        previous = current; \
        current = current->next; \
    } \
\
    return false; \
} \
\
bool ll_ ## name ## _removeat(name##_linkedlist_t* list, size_t index) \
{ \
    if (index >= list->size) \
        return false; \
\
    bool removed = false; \
\
    if (index == 0) { \
        node_ ## name ## _t* tofree = list->head; \
        list->head = tofree->next; \
        free(tofree); \
        removed = true; \
    } else { \
        node_ ## name ## _t* previous = list->head; \
        node_ ## name ## _t* current = list->head; \
\
        for (int i = 0; i < index; ++i) { \
            previous = current; \
            current = current->next; \
        } \
\
        if (current == list->tail) { \
            previous->next = NULL; \
            list->tail = previous; \
        } else { \
            previous->next = current->next; \
        } \
\
        free(current); \
        removed = true; \
    } \
\
    --list->size; \
    return removed; \
} \
\
void ll_ ## name ## _print(name##_linkedlist_t* list, void (*printer)(void*)) \
{ \
    node_ ## name ## _t* current = list->head; \
\
    while (current) { \
        printer(&current->value); \
        current = current->next; \
    } \
\
    printf("\n"); \
} \
\
void ll_ ## name ## _traverse(name##_linkedlist_t* list, bool (*action)(void*)) \
{\
    node_ ## name ## _t* current = list->head; \
\
    while (current) { \
        if (!action(&current->value)) \
            return; \
\
        current = current->next; \
    } \
}\
\
void ll_ ## name ## _free(name##_linkedlist_t* list) \
{ \
    node_ ## name ## _t* current = list->head; \
\
    while (current) { \
        node_ ## name ## _t* next = current->next; \
        free(current); \
        current = next; \
    } \
\
    free(list); \
} \

