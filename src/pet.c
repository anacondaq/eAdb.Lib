// file: pet.c
// date: 5/11/2014
// auth: trickyloki3
// desc: pet database management
#include "pet.h"

// database loading functions
int32_t petdb_load(FILE * file_stm, void * db_mem, int32_t db_size) {
	pet_t * db = (pet_t *) db_mem;
   int32_t cnt = DB_BEGIN;
   char buf[BUF_SIZE];
   char fld[BUF_SIZE];
   int32_t read_buf = 0;
   int32_t read_fld = 0;
   int32_t data_fld = 0;
   int32_t script_level = 0;

	while(fgets(buf, BUF_SIZE, file_stm) != NULL) {
      // reset reading paramaters
      read_buf = 0;
      read_fld = 0;
      data_fld = 0;
      script_level = 0;

      // read the entry
      while(1) {
      	// check if entering script
         if(buf[read_buf] == '{')
            script_level++;
         // check if leaving script
         else if(buf[read_buf] == '}')
            script_level--;

         // check if delimiter for field
         if(!script_level && (buf[read_buf] == ',' || buf[read_buf] == '\n' || buf[read_buf] == '\0')) {
            fld[read_fld] = '\0';
            switch(data_fld) {
            	case 0: db[cnt].mob_id = convert_integer(fld,10); break;
            	case 1: db[cnt].pet_name = convert_string(fld); break;
            	case 2: db[cnt].pet_jname = convert_string(fld); break;
            	case 3: db[cnt].lure_id = convert_integer(fld,10); break;
            	case 4: db[cnt].egg_id = convert_integer(fld,10); break;
            	case 5: db[cnt].equip_id = convert_integer(fld,10); break;
            	case 6: db[cnt].food_id = convert_integer(fld,10); break;
            	case 7: db[cnt].fullness = convert_integer(fld,10); break;
            	case 8: db[cnt].hungry_delay = convert_integer(fld,10); break;
            	case 9: db[cnt].r_hungry = convert_integer(fld,10); break;
            	case 10: db[cnt].r_full = convert_integer(fld,10); break;
            	case 11: db[cnt].intimate = convert_integer(fld,10); break;
            	case 12: db[cnt].die = convert_integer(fld,10); break;
            	case 13: db[cnt].capture = convert_integer(fld,10); break;
            	case 14: db[cnt].speed = convert_integer(fld,10); break;
            	case 15: db[cnt].s_performance = convert_integer(fld,10); break;
            	case 16: db[cnt].talk_convert = convert_integer(fld,10); break;
            	case 17: db[cnt].attack_rate = convert_integer(fld,10); break;
            	case 18: db[cnt].defence_attack_rate = convert_integer(fld,10); break;
            	case 19: db[cnt].change_target_rate = convert_integer(fld,10); break;
            	case 20: db[cnt].pet_script = convert_string(fld); break;
            	case 21: db[cnt].loyal_script = convert_string(fld); break;
               default: fprintf(stdout,"warn: petdb_load; invalid field column %s in %s", fld, buf); break;
            }
            read_fld = 0;
            data_fld++;
         } else {
         	// skip initial whitespace
         	if(!(isspace(buf[read_buf]) && read_fld <= 0)) {
         		// copy from entry from buffer to field buffer
		         fld[read_fld] = buf[read_buf];
		         read_fld++;
		      }
         }

         // finish reading the item
         if(buf[read_buf] == '\0' || buf[read_buf] == '\n') break;
         read_buf++;
      }

      // check for missing fields
      if(data_fld != PET_COLUMN) 
         fprintf(stdout,"warn: petdb_load; missing field expected %d got %d; %s", PET_COLUMN, data_fld, buf);
      cnt++;
   }
   return cnt;
}

void petdb_unload(pet_w * pet_db) {
   int32_t i = 0;
   pet_t pet;
   if(pet_db != NULL) {
      if(pet_db->db != NULL) {
         for(i = DB_BEGIN; i < pet_db->size; i++) {
            pet = pet_db->db[i];
            if(pet.pet_name != NULL) free(pet.pet_name);
            if(pet.pet_jname != NULL) free(pet.pet_jname);
            if(pet.pet_script != NULL) free(pet.pet_script);
            if(pet.loyal_script != NULL) free(pet.loyal_script);
         }
         free(pet_db->db);
      }
      free(pet_db);
   }
}

// database io functions
void petdb_io(pet_t pet, FILE * file_stm) {
	fprintf(file_stm, "%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s\n",
				pet.mob_id, pet.pet_name, pet.pet_jname, pet.lure_id, pet.egg_id, pet.equip_id, pet.food_id, pet.fullness, pet.hungry_delay, 
				pet.r_hungry, pet.r_full, pet.intimate, pet.die, pet.capture, pet.speed, pet.s_performance, pet.talk_convert, pet.attack_rate,
				pet.defence_attack_rate, pet.change_target_rate, pet.pet_script, pet.loyal_script);
}

void petdb_read(pet_w * pet_db) {
	int32_t i;
	for(i = DB_BEGIN; i < pet_db->size; i++)
		petdb_io(pet_db->db[i],stdout);
}

void petdb_write(pet_w * pet_db, const char * file) {
	int32_t i;
	FILE * file_stm = fopen(file,"w");
	if(file_stm == NULL) return;
	for(i = DB_BEGIN; i < pet_db->size; i++)
		petdb_io(pet_db->db[i], file_stm);
	fclose(file_stm);
}

// generic functions for getting and setting
int32_t * petdb_mob_id(void * field) { return &((pet_t *)field)->mob_id; }
char * petdb_pet_name(void * field) { return ((pet_t *)field)->pet_name; }
int32_t * petdb_getint(void * db, int32_t index, DBFIELD field) { return field(&(((pet_t *) db)[index])); }
char * petdb_getstr(void * db, int32_t index, DBFIELD_STR field) { return field(&(((pet_t *) db)[index])); }
void petdb_swap(void * db, int32_t a, int32_t b) {
	pet_t * pet_db = db;
	pet_t temp = pet_db[a];
	pet_db[a] = pet_db[b];
	pet_db[b] = temp;
}