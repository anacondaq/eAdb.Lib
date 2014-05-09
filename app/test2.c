#include "item.h"

int main(int argc, char * argv[]) {
   item_w * item_db = itemdb_load("db/item_db.txt");
   itemdb_unload(item_db);
   exit(EXIT_SUCCESS);
}