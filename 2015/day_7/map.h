#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct HashTable HashTable;

HashTable* createTable();
void destroyTable(HashTable* table);
const char* insert(HashTable* table, char* key, void* value);
void* lookup(HashTable* table, char* key);
void removeKey(HashTable* table, char* key);
int getLength(HashTable* table);

#endif