/*=============================================================================
   file: skill.c
   date: 5/10/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: skill database management
   note: very simple code
=============================================================================*/
#include "skill.h"
static int32_t skilldb_load(FILE *, void *, int32_t);

skill_w * skilldb_init(const char * filename) {
   return (skill_w *) load(filename, trim_numeric, skilldb_load, sizeof(skill_t));
}

void skilldb_deinit(skill_w * skill_db) {
   int32_t i = 0;
   skill_t skill;
   if(skill_db != NULL) {
      if(skill_db->db != NULL) {
         for(i = DB_BEGIN; i < skill_db->size; i++) {
            skill = skill_db->db[i];
            array_unload(skill.range);
            array_unload(skill.element);
            array_unload(skill.splash);
            array_unload(skill.hit_amount);
            if(skill.cast_cancel != NULL) free(skill.cast_cancel);
            array_unload(skill.maxcount);
            if(skill.type != NULL) free(skill.type);
            array_unload(skill.blow_count);
            if(skill.name != NULL) free(skill.name);
            if(skill.desc != NULL) free(skill.desc);
         }
         free(skill_db->db);
      }
      free(skill_db);
   }
}

static int32_t skilldb_load(FILE * file_stm, void * db_mem, int32_t db_size) {
	skill_t * db = (skill_t *) db_mem;
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
            	case 0: db[cnt].id = convert_integer(fld,10); break;
            	case 1: convert_integer_list(fld, ":", &(db[cnt].range)); break;
            	case 2: db[cnt].hit = convert_integer(fld,10); break;
            	case 3: db[cnt].inf = convert_integer(fld,10); break;
            	case 4: convert_integer_list(fld, ":", &(db[cnt].element)); break;
            	case 5: db[cnt].nk = convert_uinteger(fld,16); break;
            	case 6: convert_integer_list(fld, ":", &(db[cnt].splash)); break;
            	case 7: db[cnt].max = convert_integer(fld,10); break;
            	case 8: convert_integer_list(fld, ":", &(db[cnt].hit_amount)); break;
            	case 9: db[cnt].cast_cancel = convert_string(fld); break;
            	case 10: db[cnt].cast_def_reduce_rate = convert_integer(fld,10); break;
            	case 11: db[cnt].inf2 = convert_uinteger(fld,16); break;
            	case 12: convert_integer_list(fld, ":", &(db[cnt].maxcount)); break;
            	case 13: db[cnt].type = convert_string(fld); break;
            	case 14: convert_integer_list(fld, ":", &(db[cnt].blow_count)); break;
            	case 15: db[cnt].inf3 = convert_uinteger(fld,16); break;
            	case 16: db[cnt].name = convert_string(fld); break;
            	case 17: db[cnt].desc = convert_string(fld); break;
               default: fprintf(stdout,"warn: skilldb_load; invalid field column %s in %s", fld, buf); break;
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
      if(data_fld != SKILL_COLUMN) 
         fprintf(stdout,"warn: skilldb_load; missing field expected %d got %d; %s", SKILL_COLUMN, data_fld, buf);

      cnt++;

      /* check for exceed size of allocated memory */
      if(cnt > db_size) {
         fprintf(stdout,"warn: skilldb_load; exceeding the size of the database; %d < %d.\n%s\n", db_size, cnt, buf);
         exit(EXIT_FAILURE);
      }
   }
   return cnt;
}

void skilldb_io(skill_t skill, FILE * file_stm) {
   fprintf(file_stm,"%d,",skill.id);
   array_io(skill.range, file_stm);
   fprintf(file_stm,"%d,%d,", skill.hit, skill.inf);
   array_io(skill.element, file_stm);
   fprintf(file_stm,"0x%x,", skill.nk);
   array_io(skill.splash, file_stm);
   fprintf(file_stm,"%d,", skill.max);
   array_io(skill.hit_amount, file_stm);
   fprintf(file_stm,"%s,%d,0x%x,", skill.cast_cancel, skill.cast_def_reduce_rate, skill.inf2);
   array_io(skill.maxcount, file_stm);
   fprintf(file_stm,"%s,", skill.type);
   array_io(skill.blow_count, file_stm);
   fprintf(file_stm,"0x%x,%s,%s\n", skill.inf3, skill.name, skill.desc);
}

void skilldb_read(skill_w * skill_db) {
   int32_t i;
   for(i = DB_BEGIN; i < skill_db->size; i++)
      skilldb_io(skill_db->db[i],stdout);
}

void skilldb_write(skill_w * skill_db, const char * file_name) {
   int32_t i;
   FILE * file_stm = fopen(file_name,"w");
   if(file_stm == NULL) return;
   for(i = DB_BEGIN; i < skill_db->size; i++)
      skilldb_io(skill_db->db[i], file_stm);
   fclose(file_stm);
}

int32_t * skilldb_id(void * field) { return &((skill_t *)field)->id; }
char * skilldb_name(void * field) { return ((skill_t *)field)->name; }
int32_t * skilldb_getint(void * db, int32_t index, DBFIELD field) { return field(&(((skill_t *) db)[index])); }
char * skilldb_getstr(void * db, int32_t index, DBFIELD_STR field) { return field(&(((skill_t *) db)[index])); }
void skilldb_swap(void * db, int32_t a, int32_t b) {
   skill_t * skill_db = db;
   skill_t temp = skill_db[a];
   skill_db[a] = skill_db[b];
   skill_db[b] = temp;
}