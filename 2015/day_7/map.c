#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 16

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
} 


typedef struct{
    const char* key;
    void* value;
} Entry;

typedef struct{
    Entry* entries;
    size_t capacity;
    size_t length;
} HashTable;


HashTable* createTable() {
    HashTable* table = malloc(sizeof(HashTable));

    if (!table) {
        return NULL;
    }

    table->capacity = INITIAL_CAPACITY;
    table->length = 0;

    // zero'd space for entry buckets
    table->entries = calloc(table->capacity, sizeof(Entry));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }
    return table;
}


void destroyTable(HashTable *table) {
    for (size_t i = 0; i < table->capacity; i++) {
        free((void*)table->entries[i].key);
        free(table->entries->value);
    }

    free(table->entries);
    free(table);
}

// Fucking ahte collisions
static const char* _insert(Entry* entries, size_t capacity,
    const char* key, void* value, size_t* plength) {

    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

    
    while (entries[index].key) {
        if (strcmp(key, entries[index].key) == 0) {
            entries[index].value = value;
            return entries[index].key;
        }

        index++;
        if (index >= capacity) {
            index = 0; // wraparound
        }
    }

    if (plength) {
        key = strdup(key);
        if (!key) {
            return NULL;
        }
        (*plength)++;
    }
    
    entries[index].key = key;
    entries[index].value = value;
    
    return key;
}

void increaseCapacity(HashTable* table) {
    size_t newCapacity = table->capacity * 2;
    Entry* newEntries = calloc(newCapacity, sizeof(Entry));

    for (size_t i=0; i < table->capacity; i++) {
        Entry entry = table->entries[i];
        if (entry.key) {
            _insert(newEntries, newCapacity, entry.key, entry.value, NULL);
        }
    }

    free(table->entries);
    table->entries = newEntries;
    table->capacity = newCapacity;
}


// Inserty a K,V pair into the map. If Key exists, previous value is overwritten
const char* insert(HashTable* table, char* key, void* value) {
    if (!table || !key || !value) return NULL;

    if (table->length >= (table->capacity / 2)) {
        increaseCapacity(table);
    }

    return _insert(table->entries, table->capacity, key, value, 
            &table->length);

}

int getLength(HashTable* table) {
    return table->length;
}

// find value to key
void* lookup(HashTable* table, char* key) {
    if (!table || !key) return NULL;

    //printMap(table);

    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

    while (table->entries[index].key) {
        if (strcmp(key, table->entries[index].key) == 0) {
            return table->entries[index].value;
        }
        index ++;

        if (index >= table->capacity) {
            index = 0;
        }
    }

    return NULL;
}

// remove key from HashTable, if exists
void removeKey(HashTable* table, char* key) {
    if (!table || !key) return;

    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

    while (table->entries[index].key) {
        if (strcmp(key, table->entries[index].key) == 0) {
            table->entries[index].key = NULL;
            table->entries[index].value = 0;
        }

        index++;

        if (index >= table->capacity) {
            index = 0;
        }
    }
}