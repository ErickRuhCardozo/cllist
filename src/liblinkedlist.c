/*
 * Author: Erick Ruh Cardozo (W1SD00M) - <github.com/erickruhcardozo>
 * Date: November 23, 2023 - 11:20 AM
 */

#include "linkedlist.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

typedef struct linkedlist {
    size_t size;
    node_t* head;
    node_t* tail;
} linkedlist_t;

node_t* createnode(int value)
{
    node_t* node = malloc(sizeof(node_t));
    node->value = value;
    node->next = NULL;
    return node;
}

linkedlist_t* ll_create()
{
    linkedlist_t* list = malloc(sizeof(linkedlist_t));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

size_t ll_size(linkedlist_t* list)
{
    return list->size;
}

void ll_add(linkedlist_t* list, int value)
{
    node_t* newnode = createnode(value);

    if (list->size == 0) {
        list->head = newnode;
        list->tail = newnode;
    } else {
        list->tail->next = newnode;
        list->tail = newnode;
    }

    ++list->size;
}

void ll_insert(linkedlist_t* list, size_t index, int value)
{
    node_t* newnode = createnode(value);

    if (index == 0) {
        newnode->next = list->head;
        list->head = newnode;
    } else {
        node_t* previous = list->head;
        node_t* current = list->head;

        for (int i = 0; i < index; ++i) {
            if (current->next == NULL)
                break;

            previous = current;
            current = current->next;
        }

        if (current == list->tail) {
            current->next = newnode;
            list->tail = newnode;
        } else {
            previous->next = newnode;
            newnode->next = current;
        }
    }

    ++list->size;
}

int ll_index(linkedlist_t* list, int value)
{
    node_t* current = list->head;

    for (int i = 0; i < list->size; ++i) {
        if (current->value == value)
            return i;

        current = current->next;
    }

    return -1;
}

bool ll_has(linkedlist_t* list, int value)
{
    node_t* current = list->head;

    while (current) {
        if (current->value == value)
            return true;

        current = current->next;
    }

    return false;
}

bool ll_remove(linkedlist_t* list, int value)
{
    if (list->size == 0)
        return false;

    node_t* current = list->head;
    node_t* previous = list->head;

    while (current) {
        if (current->value == value) {
            if (current == list->head)
                list->head = current->next;
            else
                previous->next = current->next;

            free(current);
            --list->size;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

bool ll_removeat(linkedlist_t* list, size_t index)
{
    if (index >= list->size)
        return false;

    bool removed = false;

    if (index == 0) {
        node_t* tofree = list->head;
        list->head = tofree->next;
        free(tofree);
        removed = true;
    } else {
        node_t* previous = list->head;
        node_t* current = list->head;

        for (int i = 0; i < index; ++i) {
            previous = current;
            current = current->next;
        }

        if (current == list->tail) {
            previous->next = NULL;
            list->tail = previous;
        } else {
            previous->next = current->next;
        }

        free(current);
        removed = true;
    }

    --list->size;
    return removed;
}

void ll_print(linkedlist_t* list)
{
    node_t* current = list->head;

    while (current) {
        printf("[%d]->", current->value);
        current = current->next;
    }

    printf("\n");
}

void ll_traverse(linkedlist_t* list, bool (*action)(int*))
{
    node_t* current = list->head;

    while (current) {
        if (!action(&current->value))
            return;

        current = current->next;
    }
}

void ll_free(linkedlist_t* list)
{
    node_t* current = list->head;

    while (current) {
        node_t* next = current->next;
        free(current);
        current = next;
    }

    free(list);
}
