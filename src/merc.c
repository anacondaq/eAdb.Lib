/*=============================================================================
   file: merc.c
   date: 5/11/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: mercenary database management
   note: very simple code
=============================================================================*/
#include "merc.h"
static int32_t mercdb_load(FILE * file_stm, void * db_mem, int32_t db_size);

merc_w * mercdb_init(const char * filename) {
   return (merc_w *) load(filename, trim_numeric, mercdb_load, sizeof(merc_t));
}

void mercdb_deinit(merc_w * merc_db) {
   int32_t i = 0;
   merc_t merc;
   if(merc_db != NULL) {
      if(merc_db->db != NULL) {
         for(i = DB_BEGIN; i < merc_db->size; i++) {
            merc = merc_db->db[i];
            if(merc.sprite != NULL) free(merc.sprite);
            if(merc.name != NULL) free(merc.name);
         }
         free(merc_db->db);
      }
      free(merc_db);
   }
}

static int32_t mercdb_load(FILE * file_stm, void * db_mem, int32_t db_size) {
	merc_t * db = (merc_t *) db_mem;
   int32_t cnt = DB_BEGIN;
   char buf[BUF_SIZE];
   char fld[BUF_SIZE];
   int32_t read_buf = 0;
   int32_t read_fld = 0;
   int32_t data_fld = 0;

	while(fgets(buf, BUF_SIZE, file_stm) != NULL) {
      read_buf = 0;
      read_fld = 0;
      data_fld = 0;

      while(1) {
         /* check if delimiter for field */
         if(buf[read_buf] == ',' || buf[read_buf] == '\n' || buf[read_buf] == '\0') {
            fld[read_fld] = '\0';
            switch(data_fld) {
            	case 0: db[cnt].id = convert_integer(fld, 10); break;
            	case 1: db[cnt].sprite = convert_string(fld); break;
            	case 2: db[cnt].name = convert_string(fld); break;
            	case 3: db[cnt].lv = convert_integer(fld, 10); break;
            	case 4: db[cnt].hp = convert_integer(fld, 10); break;
            	case 5: db[cnt].sp = convert_integer(fld, 10); break;
            	case 6: db[cnt].range1 = convert_integer(fld, 10); break;
            	case 7: db[cnt].atk1 = convert_integer(fld, 10); break;
            	case 8: db[cnt].atk2 = convert_integer(fld, 10); break;
            	case 9: db[cnt].def = convert_integer(fld, 10); break;
            	case 10: db[cnt].mdef = convert_integer(fld, 10); break;
            	case 11: db[cnt].str = convert_integer(fld, 10); break;
            	case 12: db[cnt].agi = convert_integer(fld, 10); break;
            	case 13: db[cnt].vit = convert_integer(fld, 10); break;
            	case 14: db[cnt].intr = convert_integer(fld, 10); break;
            	case 15: db[cnt].dex = convert_integer(fld, 10); break;
            	case 16: db[cnt].luk = convert_integer(fld, 10); break;
            	case 17: db[cnt].range2 = convert_integer(fld, 10); break;
            	case 18: db[cnt].range3 = convert_integer(fld, 10); break;
            	case 19: db[cnt].scale = convert_integer(fld, 10); break;
            	case 20: db[cnt].race = convert_integer(fld, 10); break;
            	case 21: db[cnt].element = convert_integer(fld, 10); break;
            	case 22: db[cnt].speed = convert_integer(fld, 10); break;
            	case 23: db[cnt].adelay = convert_integer(fld, 10); break;
            	case 24: db[cnt].amotion = convert_integer(fld, 10); break;
            	case 25: db[cnt].dmotion = convert_integer(fld, 10); break;
               default: fprintf(stdout,"warn: mercdb_load; invalid field column %s in %s", fld, buf); break;
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

      /* check for missing fields */
      if(data_fld != MERCENARY_COLUMN) 
         fprintf(stdout,"warn: mercdb_load; missing field expected %d got %d; %s", MERCENARY_COLUMN, data_fld, buf);

      cnt++;

      /* check for exceed size of allocated memory */
      if(cnt > db_size) {
         fprintf(stdout,"warn: mercdb_load; exceeding the size of the database; %d < %d.\n%s\n", db_size, cnt, buf);
         exit(EXIT_FAILURE);
      }
   }
   return cnt;
}

void mercdb_io(merc_t merc, FILE * file_stm) {
	fprintf(file_stm, "%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
		merc.id, merc.sprite, merc.name, merc.lv, merc.hp, merc.sp, merc.range1, 
		merc.atk1, merc.atk2, merc.def, merc.mdef, merc.str, merc.agi, merc.vit, 
		merc.intr, merc.dex, merc.luk, merc.range2, merc.range3, merc.scale, merc.race, 
		merc.element, merc.speed, merc.adelay, merc.amotion, merc.dmotion);
}

void mercdb_read(merc_w * merc_db) {
	int32_t i;
	for(i = DB_BEGIN; i < merc_db->size; i++)
		mercdb_io(merc_db->db[i], stdout);
}

void mercdb_write(merc_w * merc_db, const char * file_name) {
   int32_t i;
   FILE * file_stm = fopen(file_name,"w");
   if(file_stm == NULL) return;
   for(i = DB_BEGIN; i < merc_db->size; i++)
      mercdb_io(merc_db->db[i], file_stm);
   fclose(file_stm);
}

int32_t * mercdb_id(void * field) { return &((merc_t *)field)->id; }
char * mercdb_sprite(void * field) { return ((merc_t *)field)->sprite; }
char * mercdb_name(void * field) { return ((merc_t *)field)->name; }
int32_t * mercdb_lv(void * field) { return &((merc_t *)field)->lv; }
int32_t * mercdb_hp(void * field) { return &((merc_t *)field)->hp; }
int32_t * mercdb_sp(void * field) { return &((merc_t *)field)->sp; }
int32_t * mercdb_range1(void * field) { return &((merc_t *)field)->range1; }
int32_t * mercdb_atk1(void * field) { return &((merc_t *)field)->atk1; }
int32_t * mercdb_atk2(void * field) { return &((merc_t *)field)->atk2; }
int32_t * mercdb_def(void * field) { return &((merc_t *)field)->def; }
int32_t * mercdb_mdef(void * field) { return &((merc_t *)field)->mdef; }
int32_t * mercdb_str(void * field) { return &((merc_t *)field)->str; }
int32_t * mercdb_agi(void * field) { return &((merc_t *)field)->agi; }
int32_t * mercdb_vit(void * field) { return &((merc_t *)field)->vit; }
int32_t * mercdb_intr(void * field) { return &((merc_t *)field)->intr; }
int32_t * mercdb_dex(void * field) { return &((merc_t *)field)->dex; }
int32_t * mercdb_luk(void * field) { return &((merc_t *)field)->luk; }
int32_t * mercdb_range2(void * field) { return &((merc_t *)field)->range2; }
int32_t * mercdb_range3(void * field) { return &((merc_t *)field)->range3; }
int32_t * mercdb_scale(void * field) { return &((merc_t *)field)->scale; }
int32_t * mercdb_race(void * field) { return &((merc_t *)field)->race; }
int32_t * mercdb_element(void * field) { return &((merc_t *)field)->element; }
int32_t * mercdb_speed(void * field) { return &((merc_t *)field)->speed; }
int32_t * mercdb_adelay(void * field) { return &((merc_t *)field)->adelay; }
int32_t * mercdb_amotion(void * field) { return &((merc_t *)field)->amotion; }
int32_t * mercdb_dmotion(void * field) { return &((merc_t *)field)->dmotion; }
int32_t * mercdb_getint(void * db, int32_t index, DBFIELD field) { return field(&(((merc_t *) db)[index])); }
char * mercdb_getstr(void * db, int32_t index, DBFIELD_STR field) { return field(&(((merc_t *) db)[index])); }
void mercdb_swap(void * db, int32_t a, int32_t b) {
	merc_t * merc_db = db;
	merc_t temp = merc_db[a];
	merc_db[a] = merc_db[b];
	merc_db[b] = temp;
}