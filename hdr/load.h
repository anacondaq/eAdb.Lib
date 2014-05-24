/*=============================================================================
   file: load.h
   date: 5/10/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: generalize database loading procedures
   note: very simple code
===============================================================================
If the explanations of the code is not clear, then please email me @
tricky.loki3@gmail.com or contact me on GitHub.
===============================================================================
void * load(const char * file_name, DB_TRIM file_trim, DB_LOAD file_load, size_t type_size)
   * file_name - name of the database file, i.e. item_db.txt.
   * file_trim - function pointer to either trim_numeric or trim_alpha or custom.
   * file_load - function pointer to db_load functions, see other headers.
   * size_t - size of the database entry, i.e. sizeof(item_t)
===============================================================================
char * trim(const char * file_name, int32_t * file_line, DB_TRIM file_trim)
   * file_name - name of the databse file, i.e. item_db.txt.
   * file_line - store the total number of lines written to file_trim.
   * file_trim - file stream reading from file_name.
=============================================================================*/
#ifndef LOAD_H
#define LOAD_H
   #include "util.h"
   
   /* generic function pointer type */
   typedef int32_t (*DB_TRIM)(FILE *, FILE *);
   typedef int32_t (*DB_LOAD)(FILE *, void *, int32_t);

   /* generic database wrapper */
   typedef struct {
      void * db;
      int32_t size;
   } generic_w;

   /* generic functions */
   char * trim(const char *, int32_t *, DB_TRIM);
   void * load(const char *, DB_TRIM, DB_LOAD, size_t);

   /* DB_TRIM functions */
   int32_t trim_general(FILE *, FILE *);
   int32_t trim_numeric(FILE *, FILE *);
   int32_t trim_alpha(FILE *, FILE *);
#endif