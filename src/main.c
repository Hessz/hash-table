#include "../include/hash_table.h"

int main(){
  
  ht_hash_table* ht = ht_new(53);
  ht_delete_hash_table(ht);

  printf("%d", ht_hash("cat", 151, 53));
  
  return 0;
}