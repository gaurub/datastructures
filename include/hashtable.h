#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdbool.h>

typedef struct Hashtable_t {
	void **buckets;
	int count;
} Hashtable;

/* Implementation of the JCF Hashtable class.
Implements the Map and Dictionary classes */

Hashtable* hash_table_new();
void hash_table_clear(Hashtable *table); //optional, but doing all of it
bool hash_table_contains_key(Hashtable *table, const void *key);
bool hash_table_contains_value(Hashtable *table, const void *value);
bool hash_table_equals(Hashtable *table);
void* hash_table_get(Hashtable *table, const void *key);
int hash_code(Hashtable *table);
bool hash_table_is_empty(Hashtable *table);
void** hash_table_key_set(Hashtable *table);
void* hash_table_put(Hashtable *table, const void *key, const void *value);
void hash_table_put_all(Hashtable *table, Hashtable *source);
void* hash_table_remove(Hashtable *table, const void *key);
int hash_table_size(Hashtable *table);
void** hash_table_values(Hashtable *table);
void hash_table_free();

#endif /* __HASHTABLE_H__ */
