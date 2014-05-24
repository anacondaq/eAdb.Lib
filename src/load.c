/*=============================================================================
  file: load.c
  date: 5/10/2014
update: 5/23/2014
  auth: trickyloki3
  desc: generalize database loading procedures
  note: very simple code
===============================================================================
char * trim(const char * file_name, int32_t * file_line, DB_TRIM file_trim)   
 * Refactor all the condition checking and generalize trimming functions.
 * Returns the trim filename and requires freeing from heap memory.
===============================================================================
void * load(const char * file_name, DB_TRIM file_trim, DB_LOAD file_load, size_t type_size)
 * Refactor all the condition checking and generalize loading functions.
 * Returns generic database structure that must be deinit.
===============================================================================
int trim_numeric(FILE * file_stm, FILE * trim_stm)
int trim_alpha(FILE * file_stm, FILE * trim_stm)
 * DB_TRIM function that expects numeric or alpha ID per row in the table.
=============================================================================*/
#include "load.h"

char * trim(const char * file_name, int32_t * file_line, DB_TRIM file_trim) {
   char * trim_name = NULL;
   FILE * file_stm = NULL;
   FILE * trim_stm = NULL;

   /* check if paramaters are valid */
   if(file_name == NULL || file_line == NULL || file_trim == NULL) {
      fprintf(stdout,"warn: trim; detected NULL paramaters for file %s.\n", file_name);
      return NULL;
   }

   /* failed to allocate temporary filename */
   trim_name = random_string(16);
   if(trim_name == NULL) {
      fprintf(stdout,"warn: trim; temporary filename failed to allocate memory for %s.\n", file_name);
      return NULL;
   }

   /* failed to open original or temporary file */
   file_stm = fopen(file_name,"r");
   trim_stm = fopen(trim_name,"w");
   if(file_stm == NULL || trim_stm == NULL) {
      fprintf(stdout,"warn: trim; failed to open %s or %s.\n", trim_name, file_name);
      if(trim_name != NULL) free(trim_name);
      fclose(file_stm);
      fclose(trim_stm);
      return NULL;
   }

   /* check if the file have at least one valid entry */
   *file_line = file_trim(file_stm, trim_stm);
   if(*file_line <= 0) {
      fprintf(stdout,"warn: trim; detected error or zero entries in file %s.\n", file_name);
      if(trim_name != NULL) free(trim_name);
      fclose(file_stm);
      fclose(trim_stm);
      return NULL;
   }

   /* clean up resources */
   fclose(file_stm);
   fclose(trim_stm);
   return trim_name;
}

void * load(const char * file_name, DB_TRIM file_trim, DB_LOAD file_load, size_t type_size) {
   generic_w * wrapper = NULL;
   void * db = NULL;
   int32_t size = 0;
   int32_t cnt = 0;

   char * trim_name = NULL;
   FILE * trim_stm = NULL;

   /* filter the database for valid entries per line */
   trim_name = trim(file_name, &size, file_trim);
   if(trim_name == NULL) {
      fprintf(stdout,"warn: load; failed to filter or trim the database file %s\n", file_name);
      return NULL;
   }

   /* allocate memory for the database */
   db = malloc(type_size * (size + DB_BEGIN));
   if(db == NULL) {
      fprintf(stdout,"warn: load; failed to allocate memory for database file %s.\n",file_name);
      if(trim_name != NULL) free(trim_name);
      return NULL;
   }

   /* open filtered database for reading */
   trim_stm = fopen(trim_name, "r");
   if(trim_stm == NULL) {
      fprintf(stdout,"warn: load; failed to open filtered database for database file %s.\n", file_name);
      if(trim_name != NULL) free(trim_name);
      if(db != NULL) free(db);
      return NULL;
   }

   /* load the datbase */
   cnt = file_load(trim_stm, db, size + DB_BEGIN);
   if(cnt <= 0) {
      fprintf(stdout,"warn: load; failed to load entries into database for database file %s.\n", file_name);
      if(trim_name != NULL) free(trim_name);
      if(db != NULL) free(db);
      fclose(trim_stm);
      return NULL;
   }

   /* return the wrapper */
   fclose(trim_stm);
   remove(trim_name);
   free(trim_name);
   wrapper = malloc(sizeof(generic_w));
   wrapper->db = db;
   wrapper->size = size + DB_BEGIN;
   return wrapper;
}

int32_t trim_general(FILE * file_stm, FILE * trim_stm) {
   int32_t line_count = 0;
   char buf[BUF_SIZE];
   while(fgets(buf, sizeof(buf), file_stm) != NULL)
      if(strlen(buf) > 0)          /* check if empty */
         if(!isspace(buf[0]))      /* check if whitespace */
            if(buf[0] != '/') {    /* check if comment */
               fprintf(trim_stm, "%s", buf);
               line_count++;
            }
   return line_count;
}

int32_t trim_numeric(FILE * file_stm, FILE * trim_stm) {
   int32_t line_count = 0;
   char buf[BUF_SIZE];
   while(fgets(buf, sizeof(buf), file_stm) != NULL)
      if(strlen(buf) > 0)            /* check if empty */
         if(!isspace(buf[0]))        /* check if whitespace */
            if(buf[0] != '/')        /* check if comment */
               if(isdigit(buf[0])) { /* check if digit */
                  fprintf(trim_stm, "%s", buf);
                  line_count++;
               }
   return line_count;
}

int32_t trim_alpha(FILE * file_stm, FILE * trim_stm) {
   int32_t line_count = 0;
   char buf[BUF_SIZE];
   while(fgets(buf, sizeof(buf), file_stm) != NULL)
      if(strlen(buf) > 0)            /* check if empty */
         if(!isspace(buf[0]))        /* check if whitespace */
            if(buf[0] != '/')        /* check if comment */
               if(isalpha(buf[0])) { /* check if digit */
                  fprintf(trim_stm, "%s", buf);
                  line_count++;
               }
   return line_count;
}