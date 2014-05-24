/*=============================================================================
   file: produce.c
   date: 5/11/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: produce database management
   note: very simple code
=============================================================================*/
#include "produce.h"
static int32_t producedb_load(FILE * file_stm, void * db_mem, int32_t db_size);

produce_w * producedb_init(const char * filename) {
   return (produce_w *) load(filename, trim_numeric, producedb_load, sizeof(produce_t));
}

void producedb_deinit(produce_w * produce_db) {
   int32_t i = 0;
   produce_t produce;
   if(produce_db != NULL) {
      if(produce_db->db != NULL) {
         for(i = DB_BEGIN; i < produce_db->size; i++) {
            produce = produce_db->db[i];
            if(produce.material != NULL) free(produce.material);
            if(produce.amount != NULL) free(produce.amount);
         }
         free(produce_db->db);
      }
      free(produce_db);
   }
}

static int32_t producedb_load(FILE * file_stm, void * db_mem, int32_t db_size) {
	produce_t * db = (produce_t *) db_mem;
   int32_t cnt = DB_BEGIN;
   char buf[BUF_SIZE];
   char fld[BUF_SIZE];
   int32_t read_buf = 0;
   int32_t read_fld = 0;
   int32_t data_fld = 0;
   int32_t fld_cnt = 0;
   int32_t material_cnt = 0;
   int32_t alternate = 0;

	while(fgets(buf, BUF_SIZE, file_stm) != NULL) {
      read_buf = 0;
      read_fld = 0;
      data_fld = 0;
      fld_cnt = 0;
      material_cnt = 0;
      alternate = 0;

      /* retrieve the total number of materials */
      while(buf[read_buf] != '\0') {
      	if(buf[read_buf] == ',') fld_cnt++;
      	read_buf++;
      }
      read_buf = 0;
      fld_cnt -= PRODUCE_HEADER;
      fld_cnt /= 2;

      /* check if materials exist */
      if(fld_cnt <= 0) {
      	fprintf(stdout,"warn: producedb_load missing material or amount %s",buf);
      	continue;
      }

      /* allocate memory for material and amount */
      db[cnt].material = malloc(sizeof(int32_t) * fld_cnt);
      if(db[cnt].material == NULL) {
      	fprintf(stdout,"warn: producedb_load failed to allocate memory for material.");
      	continue;
      }
      db[cnt].amount = malloc(sizeof(int32_t) * fld_cnt);
      if(db[cnt].amount == NULL) {
      	fprintf(stdout,"warn: producedb_load failed to allocate memory for amount.");
      	continue;
      }
      db[cnt].count = fld_cnt;

      while(1) {
         /* check if delimiter for field */
         if(buf[read_buf] == ',' || buf[read_buf] == '\n' || buf[read_buf] == '\0') {
            fld[read_fld] = '\0';
            switch(data_fld) {
            	case 0: db[cnt].item_id = convert_integer(fld,10); break;
            	case 1: db[cnt].item_lv = convert_integer(fld,10); break;
            	case 2: db[cnt].req_skill = convert_integer(fld,10); break;
            	case 3: db[cnt].req_skill_lv = convert_integer(fld,10); break;
               default: 
               	if(!alternate) 
               		db[cnt].material[material_cnt] = convert_integer(fld,10);
               	else {
               		db[cnt].amount[material_cnt] = convert_integer(fld,10);
               		material_cnt++;
               	}
               	alternate = !alternate;
               	break;
            }
            read_fld = 0;
            data_fld++;
         } else {
         	/* skip initial whitespace */
         	if(!(isspace(buf[read_buf]) && read_fld <= 0)) {
		         fld[read_fld] = buf[read_buf];
		         read_fld++;
		      }
         }

         /* finish reading the item */
         if(buf[read_buf] == '\0' || buf[read_buf] == '\n') break;
         read_buf++;
      }

      cnt++;

      /* check for exceed size of allocated memory */
      if(cnt > db_size) {
         fprintf(stdout,"warn: producedb_load; exceeding the size of the database; %d < %d.\n%s\n", db_size, cnt, buf);
         exit(EXIT_FAILURE);
      }
   }
   return cnt;
}

void producedb_io(produce_t produce, FILE * file_stm) {
	int32_t i;
	fprintf(file_stm,"%d,%d,%d,%d,", produce.item_id, produce.item_lv, produce.req_skill, produce.req_skill_lv);
	for(i = 0; i < produce.count - 1; i++)
		fprintf(file_stm,"%d,%d,", produce.material[i], produce.amount[i]);
	fprintf(file_stm,"%d,%d\n", produce.material[i], produce.amount[i]);
}

void producedb_read(produce_w * produce_db) {
	int32_t i;
	for(i = DB_BEGIN; i < produce_db->size; i++)
		producedb_io(produce_db->db[i], stdout);
}

void producedb_write(produce_w * produce_db, const char * file_name) {
   int32_t i;
   FILE * file_stm = fopen(file_name,"w");
   if(file_stm == NULL) return;
   for(i = DB_BEGIN; i < produce_db->size; i++)
      producedb_io(produce_db->db[i], file_stm);
   fclose(file_stm);
}

int32_t * producedb_item_id(void * field) { return &((produce_t *)field)->item_id; }
int32_t * producedb_item_lv(void * field) { return &((produce_t *)field)->item_lv; }
int32_t * producedb_req_skill(void * field) { return &((produce_t *)field)->req_skill; }
int32_t * producedb_req_skill_lv(void * field) { return &((produce_t *)field)->req_skill_lv; }
int32_t * producedb_getint(void * db, int32_t index, DBFIELD field) { return field(&(((produce_t *) db)[index])); }
void producedb_swap(void * db, int32_t a, int32_t b) {
	produce_t * produce_db = db;
	produce_t temp = produce_db[a];
	produce_db[a] = produce_db[b];
	produce_db[b] = temp;
}