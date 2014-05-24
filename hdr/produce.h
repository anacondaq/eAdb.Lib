/*=============================================================================
   file: produce.h
   date: 5/11/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: produce database management
   note: very simple code
=============================================================================*/
#ifndef PRODUCE_H
#define PRODUCE_H
	#include "util.h"
   #include "load.h"
	
	#define PRODUCE_HEADER 3
	
	/* produce entry */
	typedef struct {
		int32_t item_id;
		int32_t item_lv;
		int32_t req_skill;
		int32_t req_skill_lv;
		int32_t * material;
		int32_t * amount;
		int32_t count;
	} produce_t;
	
	/* produce database */
	typedef struct {
		produce_t * db;
		int32_t size;
	} produce_w;
	
	/* initialize and deinitialize the database */
	produce_w * producedb_init(const char *);
	void producedb_deinit(produce_w *);

	/* reading and writing the database */
	void producedb_io(produce_t, FILE *);
	void producedb_read(produce_w *);
	void producedb_write(produce_w *, const char *);

	/* generic functions for getting and setting */
	int32_t * producedb_item_id(void *);
	int32_t * producedb_item_lv(void *);
	int32_t * producedb_req_skill(void *);
	int32_t * producedb_req_skill_lv(void *);
	int32_t * producedb_getint(void *, int32_t, DBFIELD);
	void producedb_swap(void *, int32_t, int32_t);	
#endif