#ifndef hash_table

#include <stdlib.h>
#include <string.h>
#include <math.h>
#define HT_PRIME_1 151
#define HT_PRIME_2 163
#define DEL_SUCESS 1
#define DEL_ERR -1
static ht_item HT_DELETED_ITEM = {NULL, NULL};

typedef struct {
    char* key;
    char* value;
} ht_item;

typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;

//Hash functions
ht_hash_table* ht_new(int size);
void ht_delete_hash_table(ht_hash_table* ht);
static int ht_hash(const char* string, const int prime, const int number_of_buckets);
static int ht_get_hash(const char* string, const int number_of_buckets, const int attempt);

//Item functions
static ht_item* ht_new_item(const char* key, const char* value);
void ht_delete_item(ht_item* item);

//API
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);

#endif