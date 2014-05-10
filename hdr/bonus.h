// file: bonus.h
// date: 5/9/2014
// auth: trickyloki3
// desc: item bonus database management
#ifndef BONUS_H
#define BONUS_H
   #include "util.h"
   
   // item database configuration
   #define BONUS_FIELD_HEADER   5    // subtract from the below macro for number of arguments
   #define BONUS1_FIELD_COUNT   6
   #define BONUS2_FIELD_COUNT   7
   #define BONUS3_FIELD_COUNT   8
   #define BONUS4_FIELD_COUNT   9
   #define BONUS5_FIELD_COUNT   10
   #define BONUS_VERBOSE        1

   // item bonus attributes
   #define STAT_ATTR 1 
   #define DAMG_ATTR 2
   #define HPSP_ATTR 4
   #define CAST_ATTR 8
   #define ELEM_ATTR 16
   #define AUTO_ATTR 32
   #define EFFT_ATTR 64
   #define MISC_ATTR 128
   #define ITEM_ATTR 256
   #define CHAR_ATTR 512
   #define EQUP_ATTR 1024
   #define UNSE_ATTR 2048

   // item bonus entry
   typedef struct {
      char * pref;         // bonus prefix, i.e. bonus, bonus2, ..
      char * name;         // bonus identifier
      int32_t attr;        // categorize bonus by type
      int32_t spec;        // special argument handling by compiler
      char * desc;         // base string for translation by compile
      int32_t argc;        // number of argument specifiers
      char * argv;         // argument specifiers
   } bonus_t;
   
   // item bonus database
   typedef struct {
      bonus_t * db;
      char * file;
      int32_t size;
   } bonus_w;

   // bonusdb primary functions
   bonus_w * bonusdb_load(const char *, const char *, int);
   bonus_w * bonusdb_unload(bonus_w *);
   void bonusdb_read(bonus_t item);
   void bonusdb_readall(bonus_w * db);
   void bonusdb_write(bonus_t, FILE *);
   void bonusdb_writeall(bonus_w *, char *);

   // bonusdb generic functions for interface
   char * bonusdb_pref(void * field);
   char * bonusdb_name(void *);
   int * bonusdb_attr(void * field);
   int * bonusdb_spec(void * field);
   int * bonusdb_getint(void * db, int index, DBFIELD field);
   char * bonusdb_getstr(void * db, int index, DBFIELD_STR field);
   int bonusdb_getsizeof(void);
   void bonusdb_swap(void * db, int a, int b);
#endif