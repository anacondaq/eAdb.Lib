// file: pet.h
// date: 5/11/2014
// auth: trickyloki3
// desc: pet database management
#ifndef PET_H
#define PET_H
	#include "util.h"
   #include "load.h"

	#define PET_COLUMN 22

	// pet entry
	typedef struct {
		int32_t mob_id;
		char * pet_name;
		char * pet_jname;
		int32_t lure_id;
		int32_t egg_id;
		int32_t equip_id;
		int32_t food_id;
		int32_t fullness;
		int32_t hungry_delay;
		int32_t r_hungry;
		int32_t r_full;
		int32_t intimate;
		int32_t die;
		int32_t capture;
		int32_t speed;
		int32_t s_performance;
		int32_t talk_convert;
		int32_t attack_rate;
		int32_t defence_attack_rate;
		int32_t change_target_rate;
		char * pet_script;
		char * loyal_script;
	} pet_t;
	
	// pet database
	typedef struct {
		pet_t * db;
		int32_t size;
	} pet_w;
	
	// database loading functions
	int32_t petdb_load(FILE *, void *, int32_t);
	void petdb_unload(pet_w *);
	
	// database io functions
	void petdb_io(pet_t, FILE *);
	void petdb_read(pet_w *);
	void petdb_write(pet_w *, const char *);
	
	// generic functions for getting and setting
	int32_t * petdb_mob_id(void *);
	char * petdb_pet_name(void * field);
	int32_t * petdb_getint(void *, int32_t, DBFIELD);
	char * petdb_getstr(void *, int32_t, DBFIELD_STR);
	void petdb_swap(void *, int32_t, int32_t);
#endif