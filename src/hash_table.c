#include "../include/hash_table.h"
static ht_item HT_DELETED_ITEM = {NULL, NULL};

static ht_item* ht_new_item(const char* k, const char* v){
   
  ht_item* new_item = malloc(sizeof(ht_item));
  new_item->key = strdup(k);
  new_item->value = strdup(v);
  return new_item;
}

ht_hash_table* ht_new(int size){
    
  ht_hash_table* ht = malloc(sizeof(ht_hash_table));
  ht->count = 0;
  ht->size = size; 
  ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
  return ht;
}

static void ht_delete_item(ht_item* item){
  
  free(item->key);
  free(item->value);
  free(item);
}

void ht_delete_hash_table(ht_hash_table* ht){
    
  for(int i = 0; i < ht->size; i++){
    ht_item* item = ht->items[i];
    if(item != NULL && item != &HT_DELETED_ITEM){
      ht_delete_item(item);
    }
  }
  free(ht->items);
  free(ht);
}

static int ht_hash(const char* string, const int prime, const int number_of_buckets){

  long hash = 0;
  size_t len_string = strlen(string);
  for(int i = 0; i < len_string; i++){
    hash += pow(prime,len_string - (i+1)) * string[i];
  }
  hash = hash % number_of_buckets;
  return (int)hash;
}

static int ht_get_hash(const char* string, const int number_of_buckets, const int attempt){
  
  const int hash_a = ht_hash(string, HT_PRIME_1, number_of_buckets);
  const int hash_b = ht_hash(string, HT_PRIME_2, number_of_buckets);
  return (hash_a + attempt * (hash_b + 1)) % number_of_buckets;
}

//API
void ht_insert(ht_hash_table* ht, const char* key, const char* value){
 
  ht_item* new_item = ht_new_item(key, value);
  
  int attempt = 0;
  int index = ht_get_hash(key, ht->size, attempt);
  ht_item* item = ht->items[index];
  
  while(item != NULL){

    if(item != &HT_DELETED_ITEM)
      if(strcmp(key, item->key) == 0){ //Update the entry if it already exists
        ht_delete_item(item);
        ht->items[index] = new_item;
        return;
      }

    index = ht_get_hash(item->key, ht->size, attempt);
    item = ht->items[index];
    attempt++;
  } 
  
  ht->items[index] = new_item;
  ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* key){

  int attempt = 0;
  int index = ht_get_hash(key, ht->size, attempt);
  ht_item* item = ht->items[index];

  while(item != NULL){
    
    if(item != &HT_DELETED_ITEM)
      if(strcmp(key,item->key) == 0)
        return item->value;
    
    index = ht_get_hash(key, ht->size, attempt);
    item = ht->items[index];   
    attempt++;  
  }
  return NULL;
}

int ht_delete(ht_hash_table* ht, const char* key) {

  int attempt = 0;
  int index = ht_get_hash(key, ht->size, attempt);
  ht_item* item = ht->items[index];
  
  while(item != NULL) {
    
    if(item != &HT_DELETED_ITEM){
      if(strcmp(key,item->key) == 0){
        ht_delete_item(item);
        ht->items[index] = &HT_DELETED_ITEM;
        ht->count--;
        return DEL_SUCESS;
      }
    } 
    index = ht_get_hash(key, ht->size, attempt);
    item = ht->items[index];
    attempt++;  
  }
  return DEL_ERR;
}