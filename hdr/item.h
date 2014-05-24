/*=============================================================================
   file: item.h
   date: 5/7/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: item database management
   note: very simple code
=============================================================================*/
#ifndef ITEM_H
#define ITEM_H
   #include "util.h"

   #define ITEM_COLUMNS        22

   /* item entry */
   typedef struct {
      int32_t id;
      char * aegis;
      char * eathena;
      int32_t type;
      int32_t buy;
      int32_t sell;
      int32_t weight;
      int32_t atk;
      int32_t matk;
      int32_t def;
      int32_t range;
      int32_t slots;
      uint32_t job;
      int32_t upper;
      int32_t gender;
      int32_t loc;
      int32_t wlv;
      int32_t elv;
      int32_t refineable;
      int32_t view;
      char * script;
      char * onequip;
      char * onunequip;
   } item_t;

   /* item database */
   typedef struct {
      item_t * db;
      int32_t size;
   } item_w;

   /* initialize and deinitialize the database */
   item_w * itemdb_init(const char *);
   item_w * itemdb_deinit(item_w *);

   /* reading and writing the database */
   void itemdb_read(item_t);
   void itemdb_readall(item_w *);
   void itemdb_write(item_t, FILE *);
   void itemdb_writeall(item_w *, char *);

   /* generic functions for getting and setting */
   int32_t * itemdb_id(void *);
   int32_t * itemdb_type(void *);
   int32_t * itemdb_buy(void *);
   int32_t * itemdb_sell(void *);
   int32_t * itemdb_weight(void *);
   int32_t * itemdb_atk(void *);
   int32_t * itemdb_matk(void *);
   int32_t * itemdb_def(void *);
   int32_t * itemdb_range(void *);
   int32_t * itemdb_slots(void *);
   uint32_t * itemdb_job(void *);
   int32_t * itemdb_upper(void *);
   int32_t * itemdb_gender(void *);
   int32_t * itemdb_loc(void *);
   int32_t * itemdb_wlv(void *);
   int32_t * itemdb_elv(void *);
   int32_t * itemdb_refineable(void *);
   int32_t * itemdb_view(void *);
   char * itemdb_aegis(void *);
   char * itemdb_eathena(void *);
   char * itemdb_script(void *);
   char * itemdb_onequip(void *);
   char * itemdb_onunequip(void *);
   int32_t itemdb_getsizeof(void);
   int32_t * itemdb_getint(void *, int32_t, DBFIELD);
   char * itemdb_getstr(void *, int32_t, DBFIELD_STR);
   void itemdb_swap(void *, int32_t, int32_t);
#endif