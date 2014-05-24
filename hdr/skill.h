/*=============================================================================
   file: skill.h
   date: 5/10/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: skill database management
   note: very simple code
=============================================================================*/
#ifndef SKILL_H
#define SKILL_H
	#include "util.h"
   #include "load.h"

	#define SKILL_COLUMN 18

	/* skill entry */
	typedef struct {
		int32_t id;
		array_w range;			/* array of int32_t delimit by : */
		int32_t hit;
		int32_t inf;
		array_w element;		/* array of int32_t delimit by : */
		uint32_t nk;
		array_w splash;		/* array of int32_t delimit by : */
		int32_t max;
		array_w hit_amount;	/* array of int32_t delimit by : */
		char * cast_cancel;	/* 'yes' or 'no' string */
		int32_t cast_def_reduce_rate;
		uint32_t inf2;
		array_w maxcount;		/* array of int32_t delimit by : */
		char * type;			/* 'none', 'weapon', 'magic', 'misc' */
		array_w blow_count;	/* array of int32_t delimit by : */
		uint32_t inf3;
		char * name;
		char * desc;
	} skill_t;
	
	/* skill database */
	typedef struct {
		skill_t * db;
		int32_t size;
	} skill_w;
	
	/* initialize and deinitialize the database */
	skill_w * skilldb_init(const char *);
	void skilldb_deinit(skill_w *);
	
	/* reading and writing the database */
	void skilldb_io(skill_t, FILE *);
	void skilldb_read(skill_w *);
	void skilldb_write(skill_w *, const char *);
	
	/* generic functions for getting and setting */
	int32_t * skilldb_id(void *);
	char * skilldb_name(void *);
	int32_t * skilldb_getint(void *, int32_t, DBFIELD);
	char * skilldb_getstr(void *, int32_t, DBFIELD_STR);
	void skilldb_swap(void *, int32_t, int32_t);
#endif