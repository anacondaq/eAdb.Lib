/*=============================================================================
   file: mob.h
   date: 5/10/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: mob database management
   note: very simple code
=============================================================================*/
#ifndef MOB_H
#define MOB_H
	#include "util.h"
	#include "load.h"
	
	#define MOB_COLUMNS 58

	/* mob entry */
	typedef struct {
		int32_t id;
		char * sprite;
		char * kro;
		char * iro;
		int32_t lv;
		int32_t hp;
		int32_t sp;
		int32_t exp;
		int32_t jexp;
		int32_t range;
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
		uint32_t mode;
		int32_t speed;
		int32_t adelay;
		int32_t amotion;
		int32_t dmotion;
		int32_t mexp;
		/*int32_t expper;*/
		int32_t mvp1id;
		int32_t mvp1per;
		int32_t mvp2id;
		int32_t mvp2per;
		int32_t mvp3id;
		int32_t mvp3per;
		int32_t drop1id;
		int32_t drop1per;
		int32_t drop2id;
		int32_t drop2per;
		int32_t drop3id;
		int32_t drop3per;
		int32_t drop4id;
		int32_t drop4per;
		int32_t drop5id;
		int32_t drop5per;
		int32_t drop6id;
		int32_t drop6per;
		int32_t drop7id;
		int32_t drop7per;
		int32_t drop8id;
		int32_t drop8per;
		int32_t drop9id;
		int32_t drop9per;
		int32_t dropcardid;
		int32_t dropcardper;
	} mob_t;
	
	/* mob database */
	typedef struct {
		mob_t * db;
		int32_t size;
	} mob_w;
	
	/* initialize and deinitialize the database */
	mob_w * mobdb_init(const char *);
	void mobdb_deinit(mob_w *);
	
	/* reading and writing the database */
	void mobdb_io(mob_t, FILE *);
	void mobdb_read(mob_w *);
	void mobdb_write(mob_w *, const char *);

	/* generic functions for getting and setting */
	int32_t * mobdb_id(void *);
	int32_t * mobdb_lv(void *);
	int32_t * mobdb_hp(void *);
	int32_t * mobdb_sp(void *);
	int32_t * mobdb_exp(void *);
	int32_t * mobdb_jexp(void *);
	int32_t * mobdb_range(void *);
	int32_t * mobdb_atk1(void *);
	int32_t * mobdb_atk2(void *);
	int32_t * mobdb_def(void *);
	int32_t * mobdb_mdef(void *);
	int32_t * mobdb_str(void *);
	int32_t * mobdb_agi(void *);
	int32_t * mobdb_vit(void *);
	int32_t * mobdb_intr(void *);
	int32_t * mobdb_dex(void *);
	int32_t * mobdb_luk(void *);
	int32_t * mobdb_range2(void *);
	int32_t * mobdb_range3(void *);
	int32_t * mobdb_scale(void *);
	int32_t * mobdb_race(void *);
	int32_t * mobdb_element(void *);
	int32_t * mobdb_speed(void *);
	int32_t * mobdb_adelay(void *);
	int32_t * mobdb_amotion(void *);
	int32_t * mobdb_dmotion(void *);
	int32_t * mobdb_mexp(void *);
	char * mobdb_sprite(void *);
	char * mobdb_kro(void *);
	char * mobdb_iro(void *);
	uint32_t * mobdb_mode(void *);
	int32_t * mobdb_dropcardid(void *);
	int32_t * mobdb_getint(void *, int32_t, DBFIELD);
	char * mobdb_getstr(void *, int32_t, DBFIELD_STR);
	void mobdb_swap(void *, int32_t, int32_t);
#endif