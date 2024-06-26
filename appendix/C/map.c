#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#define INITIAL_CAPACITY 2

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

void increaseCapacity(HashTable* table) {
    uint16_t newCapacity = table->capacity * 2;
    Entry* newEntries = calloc(newCapacity, sizeof(Entry));

    for (int i=0; i < table->capacity; i++) {
        if (table->entries[i].key) {
            uint64_t newKey = hash_key(table->entries[i].key) % newCapacity;
            newEntries[newKey] = table->entries[i];
        }
    }

    free(table->entries);
    table->entries = newEntries;
    table->capacity = newCapacity;
}

void destroyTable(HashTable *table) {
    for (size_t i = 0; i < table->capacity; i++) {
        free((void*)table->entries[i].key);
    }

    free(table->entries);
    free(table);
}


int main() {
    return 0;
}

// Inserty a K,V pair into the map. If Key exists, previous value is overwritten
const char* insert(HashTable* table, char* key, void* value) {
    if (!table || !key || !value) return NULL;

    if (table->length >= (table->capacity / 2)) {
        increaseCapacity(table);
    }

    uint64_t index = hash_key(key) % table->capacity;

    Entry entry = table->entries[index];

    if (table->entries[index].key) {
        table->entries[index].value = value;
        return table->entries[index].key;
    }

    table->entries[index].key = key;
    table->entries[index].value = value;

    table->entries[index] = table->entries[index];
    table->length++;

    return table->entries[index].key;
}

// find value to key
void* lookup(HashTable* table, char* key) {
    if (!table || !key) return NULL;

    uint64_t hash = hash_key(key) % table->capacity;

    if (table->entries[hash].key) {
        return table->entries[hash].value;
    }
    else return NULL;
}

// remove key from HashTable, if exists
void remove(HashTable* table, char* key) {
    if (!table || !key) return;

    uint64_t hash = hash_key(key) % table->capacity;

    if (table->entries[hash].key) {
        table->entries[hash].key = NULL;
        table->entries[hash].value = 0;
    }
}