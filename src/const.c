// file: const.c
// date: 5/10/2014
// auth: trickyloki3
// desc: const database management
#include "const.h"

// database loading functions
int constdb_load(FILE * file_stm, void * db_mem, int32_t db_size) {
   const_t * db = (const_t *) db_mem;
   int32_t cnt = DB_BEGIN;
   char buf[BUF_SIZE];
   char fld[BUF_SIZE];
   int32_t read_buf = 0;
   int32_t read_fld = 0;
   int32_t data_fld = 0;

   while(fgets(buf, BUF_SIZE, file_stm) != NULL) {
      // reset reading paramaters
      read_buf = 0;
      read_fld = 0;
      data_fld = 0;

      // initialize the database
      db[cnt].name = NULL;
      db[cnt].value = 0;
      db[cnt].type = 0;

      // read the entry
      while(1) {
         // check if delimiter for field
         if(isspace(buf[read_buf]) || buf[read_buf] == ',' || buf[read_buf] == '\0') {
            fld[read_fld] = '\0';
            switch(data_fld) {
               case 0: db[cnt].name = convert_string(fld); break;
               case 1:  
                  // Constant can be represented as hexadecimal or decimal
                  if(strlen(fld) > 2 && fld[0] == '0' && fld[1] == 'x')
                     db[cnt].value = convert_integer(fld, 16);
                  else
                     db[cnt].value = convert_integer(fld, 10);
                  break;
               case 2: db[cnt].type = convert_integer(fld, 10); break;
               default: fprintf(stdout,"warn: constdb_load; invalid field column %s in %s", fld, buf); break;
            }
            read_fld = 0;
            data_fld++;

            // skip all other whitespace
            while(isspace(buf[read_buf+1]) && buf[read_buf+1] != '\0') read_buf++;
         // copy from entry from buffer to field buffer
         } else {
            fld[read_fld] = buf[read_buf];
            read_fld++;
         }

         // finish reading the item
         if(buf[read_buf] == '\0' || buf[read_buf] == '\n') break;
         read_buf++;
      }

      // check for missing fields
      if(data_fld < CONST_COLUMNS_MIN || data_fld > CONST_COLUMNS_MAX) 
         fprintf(stdout,"warn: constdb_load; missing field expected %d < %d < %d %s", 
            CONST_COLUMNS_MIN, data_fld, CONST_COLUMNS_MAX, buf);
      cnt++;
   }
   return cnt;
}

void constdb_unload(const_w * const_db) {
   int32_t i = 0;
   const_t constant;
   if(const_db != NULL) {
      if(const_db->db != NULL) {
         for(i = DB_BEGIN; i < const_db->size; i++) {
            constant = const_db->db[i];
            if(constant.name != NULL) free(constant.name);
         }
         free(const_db->db);
      }
      free(const_db);
   }
}

int constdb_trim(FILE * file_stm, FILE * trim_stm) {
   int line_count = 0;
   char buf[BUF_SIZE];
   while(fgets(buf, sizeof(buf), file_stm) != NULL)
      if(strlen(buf) > 0)          // check if empty
         if(!isspace(buf[0]))      // check if whitespace
            if(buf[0] != '/') {    // check if comment
               fprintf(trim_stm, "%s", buf);
               line_count++;
            }
   return line_count;
}

// database io functions
void constdb_io(const_t constant, FILE * file_stm) {
   fprintf(file_stm,"%s\t%d\t%d\n", constant.name, constant.value, constant.type);
}

void constdb_read(const_w * const_db) {
   int32_t i;
   for(i = DB_BEGIN; i < const_db->size; i++)
      constdb_io(const_db->db[i], stdout);
}
void constdb_write(const_w * const_db, const char * file_name) {
   int32_t i;
   FILE * file_stm = fopen(file_name,"w");
   if(file_stm == NULL) return;
   for(i = DB_BEGIN; i < const_db->size; i++)
      constdb_io(const_db->db[i], file_stm);
   fclose(file_stm);
}

// generic functions for getting and setting
char * constdb_name(void * field) { return ((const_t *)field)->name; }
int32_t * constdb_value(void * field) { return &((const_t *)field)->value; }
int32_t * constdb_type (void * field) { return &((const_t *)field)->type; }
int * constdb_getint(void * db, int index, DBFIELD field) { return field(&(((const_t *) db)[index])); }
char * constdb_getstr(void * db, int index, DBFIELD_STR field) { return field(&(((const_t *) db)[index])); }
void constdb_swap(void * db, int a, int b) {
   const_t * const_db = db;
   const_t temp = const_db[a];
   const_db[a] = const_db[b];
   const_db[b] = temp;
}