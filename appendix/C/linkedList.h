#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

//V1

// Basic Struct for LinkedList
// - Length of list
// - Pointer to head
typedef struct LinkedList LinkedList;

// Creates an empty List and returns Pointer
LinkedList* createLinkedList();
// Destroys the list
// BUT does not destroy the value pointers
void destroyList(LinkedList *list);
// Destroys List, and each Value
void destroyListAndValues(LinkedList *list);
// Append value to the end of the list
int listAppendValue(LinkedList *list, void* data);
// Insert Value to the position n
// IF n > list -> length, nothing happens
int listInsertValueAtN(LinkedList *list, void *data, size_t n);
// Removes first Occurence of Value from List
int listRemoveValue(LinkedList *list, void* data);

#endif