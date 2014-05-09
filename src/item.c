// file: item.c
// date: 5/7/2014
// auth: trickyloki3
// desc: item database management
#include "item.h"
static char * itemdb_trim(const char *, int32_t *);

// Load a eAthena / rAthena item database file
// into main memory for processing.
// char * filename - Path directory to the item database 
// file, i.e. item_db.txt; both relative and absolute
// directory paths.
item_w * itemdb_load(const char * filename) {
   // item wrapper data
   item_w * item_wrapper = NULL;
   item_t * item_database = NULL;
   char * item_filename = NULL;
   int32_t item_size = 0;
   int32_t item_count = DB_BEGIN;

   // item load data
   FILE * item_file = NULL;
   char item_buf[BUF_SIZE];                  // item buffer
   char item_fld[BUF_SIZE];                  // field buffer
   int32_t read_buf = 0;                     // current item buffer index
   int32_t read_fld = 0;                     // current item field index
   int32_t script_level = 0;                 // script nesting using brackets
   int32_t field_level = 0;                  // current item field, i.e. id, aegis, eathena, ..

   // filter the database for valid entries per line
   item_filename = itemdb_trim(filename, &item_size);
   if(item_filename == NULL) {
      fprintf(stdout,"warn: itemdb_load failed to filter original database file %s.\n", filename);
      return NULL;
   }

   // check if the file have at least one valid entry
   if(item_size <= 0) {
      fprintf(stdout,"warn: itemdb_load failed to detect valid entries in the original database file %s\n", filename);
      if(item_filename != NULL) free(item_filename);
      return NULL;
   }

   // allocate memory for the database
   item_database = malloc(sizeof(item_t) * (item_size + DB_BEGIN));
   if(item_database == NULL) {
      fprintf(stdout,"warn: itemdb_load failed to allocate memory for database.\n");
      if(item_filename != NULL) free(item_filename);
      return NULL;
   }

   // open filtered database for reading
   item_file = fopen(item_filename, "r");
   if(item_file == NULL) {
      fprintf(stdout,"warn: itemdb_load failed to open filtered database file %s.\n", item_filename);
      if(item_database != NULL) free(item_database);
      if(item_filename != NULL) free(item_filename);
      return NULL;
   }

   // load the database into memory
   while(fgets(item_buf, BUF_SIZE, item_file) != NULL) {
      // reset reading paramaters
      read_buf = 0;
      read_fld = 0;
      script_level = 0;
      field_level = 0;

      // initialize item database
      item_database[item_count].id = FIELD_INT_EMPTY;
      item_database[item_count].aegis = NULL;
      item_database[item_count].eathena = NULL;
      item_database[item_count].type = FIELD_INT_EMPTY;
      item_database[item_count].buy = FIELD_INT_EMPTY;
      item_database[item_count].sell = FIELD_INT_EMPTY;
      item_database[item_count].weight = FIELD_INT_EMPTY;
      item_database[item_count].atk = FIELD_INT_EMPTY;
      item_database[item_count].matk = FIELD_INT_EMPTY;
      item_database[item_count].def = FIELD_INT_EMPTY;
      item_database[item_count].range = FIELD_INT_EMPTY;
      item_database[item_count].slots = FIELD_INT_EMPTY;
      item_database[item_count].job = FIELD_INT_EMPTY;
      item_database[item_count].upper = FIELD_INT_EMPTY;
      item_database[item_count].gender = FIELD_INT_EMPTY;
      item_database[item_count].loc = FIELD_INT_EMPTY;
      item_database[item_count].wlv = FIELD_INT_EMPTY;
      item_database[item_count].elv = FIELD_INT_EMPTY;
      item_database[item_count].refineable = FIELD_INT_EMPTY;
      item_database[item_count].view = FIELD_INT_EMPTY;
      item_database[item_count].script = NULL;
      item_database[item_count].onequip = NULL;
      item_database[item_count].onunequip = NULL;

      // read the item entry
      while(1) {
         // check if entering script
         if(item_buf[read_buf] == '{')
            script_level++;
         // check if leaving script
         else if(item_buf[read_buf] == '}')
            script_level--;

         // check if delimiter for field
         if(!script_level && (item_buf[read_buf] == ',' || item_buf[read_buf] == '\n' || item_buf[read_buf] == '\0')) {
            item_fld[read_fld] = '\0';
            switch(field_level) {
               case 0:   item_database[item_count].id = convert_integer(item_fld, 10); break;
               case 1:   item_database[item_count].aegis = convert_string(item_fld); break;
               case 2:   item_database[item_count].eathena = convert_string(item_fld); break;
               case 3:   item_database[item_count].type = convert_integer(item_fld, 10); break;
               case 4:   item_database[item_count].buy = convert_integer(item_fld, 10); break;
               case 5:   item_database[item_count].sell = convert_integer(item_fld, 10); break;
               case 6:   item_database[item_count].weight = convert_integer(item_fld, 10); break;
               case 7:   convert_delimit_integer(item_fld, ':', 2, 
                         &item_database[item_count].atk, &item_database[item_count].matk); break;
               case 8:   item_database[item_count].def = convert_integer(item_fld, 10); break;
               case 9:   item_database[item_count].range = convert_integer(item_fld, 10); break;
               case 10:  item_database[item_count].slots = convert_integer(item_fld, 10); break;
               case 11:  item_database[item_count].job = convert_uinteger(item_fld, 16); break;
               case 12:  item_database[item_count].upper = convert_integer(item_fld, 10); break;
               case 13:  item_database[item_count].gender = convert_integer(item_fld, 10); break;
               case 14:  item_database[item_count].loc = convert_integer(item_fld, 10); break;
               case 15:  item_database[item_count].wlv = convert_integer(item_fld, 10); break;
               case 16:  item_database[item_count].elv = convert_integer(item_fld, 10); break;
               case 17:  item_database[item_count].refineable = convert_integer(item_fld, 10); break;
               case 18:  item_database[item_count].view = convert_integer(item_fld, 10); break;
               case 19:  item_database[item_count].script = convert_string(item_fld); break;
               case 20:  item_database[item_count].onequip = convert_string(item_fld); break;
               case 21:  item_database[item_count].onunequip = convert_string(item_fld); break;
               default:  fprintf(stdout,"warn: invalid field column %s\n", item_fld); break;
            }
            read_fld = 0;
            field_level++;
         // copy from item buffer to field buffer
         } else {
            item_fld[read_fld] = item_buf[read_buf];
            read_fld++;
         }

         // finish reading the item
         if(item_buf[read_buf] == '\0' || item_buf[read_buf] == '\n') break;
         read_buf++;
      }

      // check for missing fields
      if(field_level == ITEM_COLUMNS) 
         fprintf(stdout,"warn: missing field %s: %s", filename, item_buf);

      // check for missing brackets
      if(script_level)
         fprintf(stdout,"warn: missing bracket %s: %s", filename, item_buf);

      item_count++;
   }
   
   // clean up loading resources
   if(ITEM_VERBOSE) fprintf(stdout, "info: %s item database loaded successfully.\n", filename);
   fclose(item_file);

   // return the item wrapper
   item_wrapper = malloc(sizeof(item_w));
   item_wrapper->db = item_database;
   item_wrapper->size = item_size + DB_BEGIN;
   item_wrapper->file = item_filename;
   return item_wrapper;
}

// Return the item database resources.
// item_w * wrapper - any valid item database that
// was loaded successfully.
item_w * itemdb_unload(item_w * wrapper) {
   int32_t i = 0;
   item_t item;
   if(wrapper != NULL) {
      if(wrapper->db != NULL) {
         // free all the strings for each item
         for(i = DB_BEGIN; i < wrapper->size; i++) {
            item = wrapper->db[i];
            if(item.aegis != NULL) free(item.aegis);
            if(item.eathena != NULL) free(item.eathena);
            if(item.script != NULL) free(item.script);
            if(item.onequip != NULL) free(item.onequip);
            if(item.onunequip != NULL) free(item.onunequip);
         }
      }

      // Clean the database resources
      remove(wrapper->file);
      if(wrapper->file != NULL) free(wrapper->file);
      if(wrapper->db != NULL) free(wrapper->db);
      free(wrapper);
   }
   return NULL;
}

// IO interface for item database
// item_w * wrapper - any valid item databse that was loaded successfully.
void itemdb_read(item_t item) {
   if(item.id >= 0) printf("%d,",item.id); else printf(",");   
   printf("%s,",item.aegis);
   printf("%s,",item.eathena);
   if(item.type >= 0) printf("%d,",item.type); else printf(",");
   if(item.buy >= 0) printf("%d,",item.buy); else printf(",");
   if(item.sell >= 0) printf("%d,",item.sell); else printf(",");
   if(item.weight >= 0) printf("%d,",item.weight); else printf(",");
   if(item.matk > 0 && item.atk > 0)
      printf("%d:%d,",item.atk,item.matk);
   else if(item.matk > 0 && item.atk <= 0)
      printf("%d:%d,",0,item.matk);
   else if(item.matk < 0 && item.atk > 0)
      printf("%d,",item.atk);
   else
      printf(",");
   if(item.matk >= 0) printf("%d,",item.matk); else printf(",");
   if(item.def >= 0) printf("%d,",item.def); else printf(",");   
   if(item.range >= 0) printf("%d,",item.range); else printf(",");   
   if(item.slots >= 0) printf("%d,",item.slots); else printf(",");
   if(item.job >= 0) printf("0x%x,", item.job);
   if(item.upper >= 0) printf("%d,",item.upper); else printf(",");
   if(item.gender >= 0) printf("%d,",item.gender); else printf(",");
   if(item.loc >= 0) printf("%d,",item.loc); else printf(",");   
   if(item.wlv >= 0) printf("%d,",item.wlv); else printf(",");
   if(item.elv >= 0) printf("%d,",item.elv); else printf(",");
   if(item.refineable >= 0) printf("%d,",item.refineable); else printf(",");
   if(item.view >= 0) printf("%d,",item.view); else printf(",");   
   printf("%s,",item.script);
   printf("%s,",item.onequip);
   printf("%s\n",item.onunequip);
}

void itemdb_readall(item_w * item_db) {
   int32_t i = DB_BEGIN;
   for(; i < item_db->size; i++)
      itemdb_read(item_db->db[i]);
}

void itemdb_write(item_t item, FILE * item_db_new) {
   if(item.id >= 0) fprintf(item_db_new,"%d,",item.id); else fprintf(item_db_new,",");
   fprintf(item_db_new,"%s,",item.aegis);
   fprintf(item_db_new,"%s,",item.eathena);
   if(item.type >= 0) fprintf(item_db_new,"%d,",item.type); else fprintf(item_db_new,",");
   if(item.buy >= 0) fprintf(item_db_new,"%d,",item.buy); else fprintf(item_db_new,",");
   if(item.sell >= 0) fprintf(item_db_new,"%d,",item.sell); else fprintf(item_db_new,",");
   if(item.weight >= 0) fprintf(item_db_new,"%d,",item.weight); else fprintf(item_db_new,",");   
   if(item.matk > 0 && item.atk > 0)
      fprintf(item_db_new,"%d:%d,",item.atk,item.matk);
   else if(item.matk > 0 && item.atk <= 0)
      fprintf(item_db_new,"%d:%d,",0,item.matk);
   else if(item.matk <= 0 && item.atk > 0)
      fprintf(item_db_new,"%d,",item.atk);
   else
      fprintf(item_db_new,",");
   if(item.def >= 0) fprintf(item_db_new,"%d,",item.def); else fprintf(item_db_new,",");
   if(item.range >= 0) fprintf(item_db_new,"%d,",item.range); else fprintf(item_db_new,",");
   if(item.slots >= 0) fprintf(item_db_new,"%d,",item.slots); else fprintf(item_db_new,",");
   if(item.job >= 0) fprintf(item_db_new,"0x%x,",item.job);
   if(item.upper >= 0) fprintf(item_db_new,"%d,",item.upper); else fprintf(item_db_new,",");
   if(item.gender >= 0) fprintf(item_db_new,"%d,",item.gender); else fprintf(item_db_new,",");
   if(item.loc >= 0) fprintf(item_db_new,"%d,",item.loc); else fprintf(item_db_new,",");
   if(item.wlv >= 0) fprintf(item_db_new,"%d,",item.wlv); else fprintf(item_db_new,",");
   if(item.elv >= 0) fprintf(item_db_new,"%d,",item.elv); else fprintf(item_db_new,",");
   if(item.refineable >= 0) fprintf(item_db_new,"%d,",item.refineable); else fprintf(item_db_new,",");
   if(item.view >= 0) fprintf(item_db_new,"%d,",item.view); else fprintf(item_db_new,",");   
   fprintf(item_db_new,"%s,",item.script);
   fprintf(item_db_new,"%s,",item.onequip);
   fprintf(item_db_new,"%s\n",item.onunequip);
}

void itemdb_writeall(item_w * item_db, char * file) {
   int32_t i = DB_BEGIN;
   FILE * file_stm = fopen(file,"w");
   if(file_stm == NULL) return;
   for(; i < item_db->size; i++)
      itemdb_write(item_db->db[i], file_stm);
   fclose(file_stm);
}

// Filter the item database for valid item entries only;
// the item entries are written to another file in the
// same directory as the program and will have the name
// (trim_filename) with the (size) pointer set to the 
// number of entries found.
// char * filename - Path directory to the item database 
// file, i.e. item_db.txt; both relative and absolute
// directory paths.
// int * size - The total number of valid item entries
// detected, which is used to allocate exact memory 
// storage.
static char * itemdb_trim(const char * filename, int32_t * size) {
   char * trim_filename = NULL;
   FILE * itemdb_file = NULL;
   FILE * itemdb_trim = NULL;
   int32_t itemdb_size = 0;

   char item_buf[BUF_SIZE];
   int32_t script_level = 0;
   int32_t field_level = 0;
   int32_t i = 0;

   // failed to allocate temporary filename
   trim_filename = random_string(16);
   if(trim_filename == NULL) {
      fprintf(stdout,"warn: itemdb_trim temporary filename failed to allocate memory.\n");
      return NULL;
   }

   // failed to open original and temporary files
   itemdb_file = fopen(filename,"r");
   itemdb_trim = fopen(trim_filename,"w");
   if(itemdb_file == NULL || itemdb_trim == NULL) {
      fprintf(stdout,"warn: itemdb_trim failed to open %s or %s.\n", trim_filename, filename);
      fclose(itemdb_file);
      fclose(itemdb_trim);
      return NULL;
   }

   // filter item database for valid entries only
   while(fgets(item_buf, sizeof(item_buf), itemdb_file) != NULL)
      if(!isspace(item_buf[0]))         // check whitespace
         if(item_buf[0] != '/')         // check comment
            if(isdigit(item_buf[0])) {  // check item id
               // check missing fields and unmatch brackets
               script_level = 0;
               field_level = 0;

               for(i = 0; item_buf[i] != '\0'; i++)
                  if(item_buf[i] == '{')
                     script_level++;
                  else if(item_buf[i] == '}')
                     script_level--;
                  else if(item_buf[i] == ',' && !script_level)
                     field_level++;

               if(script_level)
                  fprintf(stdout,"warn: missing bracket %s: %s", filename, item_buf);
               else if(field_level != ITEM_COLUMNS)
                  fprintf(stdout,"warn: missing field %s: %s", filename, item_buf);
               else {
                  fprintf(itemdb_trim, item_buf);
                  itemdb_size++;
               }
            }

   *size = itemdb_size;
   fclose(itemdb_file);
   fclose(itemdb_trim);
   return trim_filename;
}

// Generic function pointers for searching, sorting, etc interfaces
// void * field - Retrieve from the item entry (item_t) field
int32_t * itemdb_id(void * field) { return &((item_t *)field)->id; return 0; }
int32_t * itemdb_type(void * field) { return &((item_t *)field)->type; return 0; }
int32_t * itemdb_buy(void * field) { return &((item_t *)field)->buy; return 0; }
int32_t * itemdb_sell(void * field) { return &((item_t *)field)->sell; return 0; }
int32_t * itemdb_weight(void * field) { return &((item_t *)field)->weight; return 0; }
int32_t * itemdb_atk(void * field) { return &((item_t *)field)->atk; return 0; }
int32_t * itemdb_matk(void * field) { return &((item_t *)field)->matk; return 0; }
int32_t * itemdb_def(void * field) { return &((item_t *)field)->def; return 0; }
int32_t * itemdb_range(void * field) { return &((item_t *)field)->range; return 0; }
int32_t * itemdb_slots(void * field) { return &((item_t *)field)->slots; return 0; }
uint32_t * itemdb_job(void * field) { return &((item_t *)field)->job; return 0; }
int32_t * itemdb_upper(void * field) { return &((item_t *)field)->upper; return 0; }
int32_t * itemdb_gender(void * field) { return &((item_t *)field)->gender; return 0; }
int32_t * itemdb_loc(void * field) { return &((item_t *)field)->loc; return 0; }
int32_t * itemdb_wlv(void * field) { return &((item_t *)field)->wlv; return 0; }
int32_t * itemdb_elv(void * field) { return &((item_t *)field)->elv; return 0; }
int32_t * itemdb_refineable(void * field) { return &((item_t *)field)->refineable; return 0; }
int32_t * itemdb_view(void * field) { return &((item_t *)field)->view; return 0; }
char *itemdb_aegis(void * field) { return ((item_t *)field)->aegis;  return NULL; }
char *itemdb_eathena(void * field) { return ((item_t *)field)->eathena;  return NULL; }
char *itemdb_script(void * field) { return ((item_t *)field)->script;  return NULL; }
char *itemdb_onequip(void * field) { return ((item_t *)field)->onequip;  return NULL; }
char *itemdb_onunequip(void * field) { return ((item_t *)field)->onunequip; return NULL; }
int32_t itemdb_getsizeof(void) { return sizeof(item_t); }
int32_t * itemdb_getint(void * db, int32_t index, DBFIELD field) { return field(&(((item_t *) db)[index])); }
char * itemdb_getstr(void * db, int32_t index, DBFIELD_STR field) { return field(&(((item_t *) db)[index])); }
void itemdb_swap(void * db, int32_t a, int32_t b) {
   item_t * item_db = db;
   item_t temp = item_db[a];
   item_db[a] = item_db[b];
   item_db[b] = temp;
}