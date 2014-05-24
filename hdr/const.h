/*=============================================================================
   file: const.h
   date: 5/10/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: const database management
   note: very simple code
=============================================================================*/
#ifndef CONST_H
#define CONST_H
   #include "util.h"
   #include "load.h"

   #define CONST_COLUMNS_MIN        2
   #define CONST_COLUMNS_MAX        3
   
   /* const entry */
   typedef struct {
      char * name;
      int32_t value;
      int32_t type;
   } const_t;
   
   /* const database */
   typedef struct {
      const_t * db;
      int32_t size;
   } const_w;

   /* initialize and deinitialize the database */
   const_w * constdb_init(const char *);
   void constdb_deinit(const_w *);

   /* reading and writing the database */
   void constdb_io(const_t, FILE *);
   void constdb_read(const_w *);
   void constdb_write(const_w *, const char *);

   /* generic functions for getting and setting */
   char * constdb_name(void *);
   int32_t * constdb_value(void *);
   int32_t * constdb_type (void *);
   int * constdb_getint(void *, int, DBFIELD);
   char * constdb_getstr(void *, int, DBFIELD_STR);
   void constdb_swap(void *, int, int);
#endif