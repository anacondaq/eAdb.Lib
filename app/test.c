#include "item.h"

int main(int argc, char * argv[]) {
   int i;

   item_w * item_db = itemdb_load("db/item_db.txt");
   item_w * item_db2 = itemdb_load("db/item_db.txt");

   item_t * db = item_db2->db;
   int size = item_db2->size;

   
   hpsort_str(item_db->db, item_db->size, itemdb_eathena, itemdb_getstr, itemdb_swap);
   
   for(i = DB_BEGIN; i < size; i++)
      if(!bsearch_ncs_str(item_db->db, item_db->size, db[i].eathena, itemdb_eathena, itemdb_getstr))
         fprintf(stderr,"warn: unable to find %s[%d].\n", db[i].eathena, db[i].id);

   itemdb_unload(item_db);
   itemdb_unload(item_db2);
   exit(EXIT_SUCCESS);
}