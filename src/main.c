#include "../include/hash_table.h"
#include <stdio.h>

int main(){
  
  ht_hash_table* ht = ht_new(53);
  
  ht_insert(ht, "cat", "bob");
  ht_insert(ht, "dog", "dogo");
  ht_insert(ht, "bird", "jef");
  ht_insert(ht, "alien", "paul");
  ht_insert(ht, "demon", "behemot");
  ht_insert(ht, "angel", "sasa");
  
  printf("--------------------------------\n");
  printf("Hash contains %d itens\n", ht->count);
  printf("Printing all itens\n");
  ht_item *item = NULL;
  for(int i = 0; i < ht->size; i++){ 
    item = ht->items[i];
    if(item != NULL)
      printf("%d: %s - %s\n", i, ht->items[i]->key, ht->items[i]->value);
    else
      printf("%d: null\n", i);
  }
  printf("--------------------------------\n");

  printf("Removing bird\n");
  if(ht_delete(ht, "bird") == DEL_ERR)
    printf("Could not remove bird\n");
  else
    printf("Bird removed\n");

  printf("--------------------------------\n");
  printf("Is there a bird?\n");
  char* entry = ht_search(ht, "bird");
  if(entry != NULL)
    printf("There is a bird and its name is %s\n", entry);
  else
    printf("There is no bird here\n");
  printf("--------------------------------\n");

  printf("Is there a demon?\n");
  entry = ht_search(ht, "demon");
  if(entry != NULL)
    printf("There is a demon and its name is %s\n", entry);
  else
    printf("There is no demon here\n");
  printf("--------------------------------\n");

  printf("Updating demons name to jorge...\n");
  ht_insert(ht, "demon", "jorge");
  entry = ht_search(ht, "demon");
  printf("Demon name now is %s\n", entry);
  printf("--------------------------------\n");

  printf("Destroying hash\n");
  ht_delete_hash_table(ht); 
  printf("bye bye\n");
  return 0;
}