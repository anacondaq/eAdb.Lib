// Test item_bonus.c
#include "item.h"
#include "bonus.h"

int main(int argc, char * argv[]) {
   bonus_w * bonus_db = bonusdb_load("db/item_bonus.txt","bonus2",BONUS2_FIELD_COUNT);
   hpsort_str(bonus_db->db, bonus_db->size, bonusdb_name, bonusdb_getstr, bonusdb_swap);
   bonusdb_readall(bonus_db);
   bonusdb_writeall(bonus_db,"new_bonus.txt");
   bonusdb_unload(bonus_db);
   exit(EXIT_SUCCESS);
}