// file: merc.h
// date: 5/11/2014
// auth: trickyloki3
// desc: mercenary database management
#ifndef MERCENARY_DB
#define MERCENARY_DB
	#include "util.h"
   #include "load.h"
	
	#define MERCENARY_COLUMN 26
	
	// mercenary entry
	typedef struct {
		int32_t id;
		char * sprite;
		char * name;
		int32_t lv;
		int32_t hp;
		int32_t sp;
		int32_t range1;
		int32_t atk1;
		int32_t atk2;
		int32_t def;
		int32_t mdef;
		int32_t str;
		int32_t agi;
		int32_t vit;
		int32_t intr;
		int32_t dex;
		int32_t luk;
		int32_t range2;
		int32_t range3;
		int32_t scale;
		int32_t race;
		int32_t element;
		int32_t speed;
		int32_t adelay;
		int32_t amotion;
		int32_t dmotion;
	} merc_t;

	// mercenary database
	typedef struct {
		merc_t * db;
		int32_t size;
	} merc_w;
	
	// database loading functions
	int32_t mercdb_load(FILE *, void *, int32_t);
	void mercdb_unload(merc_w *);

	// database io functions
	void mercdb_io(merc_t, FILE *);
	void mercdb_read(merc_w *);
	void mercdb_write(merc_w *, const char *);
	
	// generic functions for getting and setting
	int32_t * mercdb_id(void *);
	char * mercdb_sprite(void *);
	char * mercdb_name(void *);
	int32_t * mercdb_hp(void *);
	int32_t * mercdb_sp(void *);
	int32_t * mercdb_lv(void *);
	int32_t * mercdb_range1(void *);
	int32_t * mercdb_atk1(void *);
	int32_t * mercdb_atk2(void *);
	int32_t * mercdb_def(void *);
	int32_t * mercdb_mdef(void *);
	int32_t * mercdb_str(void *);
	int32_t * mercdb_agi(void *);
	int32_t * mercdb_vit(void *);
	int32_t * mercdb_intr(void *);
	int32_t * mercdb_dex(void *);
	int32_t * mercdb_luk(void *);
	int32_t * mercdb_range2(void *);
	int32_t * mercdb_range3(void *);
	int32_t * mercdb_scale(void *);
	int32_t * mercdb_race(void *);
	int32_t * mercdb_element(void *);
	int32_t * mercdb_speed(void *);
	int32_t * mercdb_adelay(void *);
	int32_t * mercdb_amotion(void *);
	int32_t * mercdb_dmotion(void *);
	int32_t * mercdb_getint(void *, int32_t, DBFIELD);
	char * mercdb_getstr(void *, int32_t, DBFIELD_STR);
	void mercdb_swap(void *, int32_t, int32_t);
#endif