// Test item_bonus.c
#include "const.h"

int main(int argc, char * argv[]) {
   const_w * const_db = (const_w *) load("db/const.txt", constdb_trim, constdb_load, sizeof(const_t));
   hpsort_str(const_db->db, const_db->size, constdb_name, constdb_getstr, constdb_swap);
   constdb_read(const_db);
   constdb_unload(const_db);
   exit(EXIT_SUCCESS);
}