/*=============================================================================
   file: bonus.h
   date: 5/9/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: item bonus database management
   note: very simple code
=============================================================================*/
#ifndef BONUS_H
#define BONUS_H
   #include "util.h"

   /* item bonus attributes */
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

   /* bonus entry */
   typedef struct {
      char * pref;         /* bonus prefix, i.e. bonus, bonus2, etc. */
      char * buff;         /* bonus buff, i.e. bStr, bAgi, etc. */
      int32_t attr;        /* bonus category */
      char * desc;         /* bonus format string */
      int32_t * type;      /* bonus argument type */
      int32_t type_cnt;
      int32_t * order;     /* bonus order for each type */
      int32_t order_cnt;
   } bonus_t;
   
   /* bonus database */
   typedef struct {
      bonus_t * db;
      int32_t size;
   } bonus_w;

   /* initialize and deinitialize the database */
   bonus_w * bonusdb_init(const char *, const char *);
   bonus_w * bonusdb_deinit(bonus_w *);

   /* reading and writing the database */
   void bonusdb_io(bonus_t, FILE *);
   void bonusdb_read(bonus_w *);
   void bonusdb_write(bonus_w *, char *);

   /* generic functions for getting and setting */
   char * bonusdb_pref(void * field);
   char * bonusdb_name(void *);
   int * bonusdb_attr(void * field);
   int * bonusdb_spec(void * field);
   int * bonusdb_getint(void * db, int index, DBFIELD field);
   char * bonusdb_getstr(void * db, int index, DBFIELD_STR field);
   int bonusdb_getsizeof(void);
   void bonusdb_swap(void * db, int a, int b);
#endif