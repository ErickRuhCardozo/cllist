/*
 * Author: Erick Ruh Cardozo (W1SD00M) - <github.com/erickruhcardozo>
 * Date: November 23, 2023 - 11:18 AM
 */

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <stdbool.h>
#include <stddef.h>

typedef struct linkedlist linkedlist_t;

/** Creates a new LinkedList */
linkedlist_t* ll_create();

/** Retrieves the size of the list */
size_t ll_size(linkedlist_t*);

/** Add a new value at the end of the LinkedList */
void ll_add(linkedlist_t*, int);

/** Insert a new element at the specified index */
void ll_insert(linkedlist_t*, size_t, int);

/** Removes an element from the LinkedList. Returns true on success, false otherwise */
bool ll_remove(linkedlist_t*, int);

/** Removes the element at the specified index */
bool ll_removeat(linkedlist_t*, size_t);

/** Checks if the LinkedList contains some value */
bool ll_has(linkedlist_t*, int);

/** Retrieve the index of the specified value. Returns -1 if the element is not in the list */
int  ll_index(linkedlist_t*, int);

/** Print all elements in the LinkedList */
void ll_print(linkedlist_t*);

/** Traverses the LinkedList executing action for each element. Stops when action returns false. */
void ll_traverse(linkedlist_t*, bool (*)(int*));

/** Free all elements and the List itself */
void ll_free(linkedlist_t*);

#endif

