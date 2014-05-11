#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mob.h"

// database loading functions
int32_t mobdb_load(FILE * file_stm, void * db_mem, int32_t db_size) {
	mob_t * db = (mob_t *) db_mem;
   int32_t cnt = DB_BEGIN;
   char buf[BUF_SIZE];
   char fld[BUF_SIZE];
   int32_t read_buf = 0;
   int32_t read_fld = 0;
   int32_t data_fld = 0;
	
	while(fgets(buf,sizeof(buf),file_stm) != NULL) {
		read_buf = 0;
	   read_fld = 0;
	   data_fld = 0;

		while(1) {
			if(buf[read_buf] == ',' || buf[read_buf] == '\0') {
				fld[read_fld] = '\0';
				switch(data_fld) {
					case 0: db[cnt].id = convert_integer(fld,10);				break;	// id
					case 1: db[cnt].sprite = convert_string(fld); 			break;	// sprite
					case 2: db[cnt].kro = convert_string(fld);				break;	// kRO
					case 3: db[cnt].iro = convert_string(fld); 				break;	// iRO
					case 4: db[cnt].lv = convert_integer(fld,10);				break;	// lv
					case 5: db[cnt].hp = convert_integer(fld,10);				break;	// hp
					case 6: db[cnt].sp = convert_integer(fld,10);				break;	// sp
					case 7: db[cnt].exp = convert_integer(fld,10);				break;	// exp
					case 8: db[cnt].jexp = convert_integer(fld,10);				break;	// jexp
					case 9: db[cnt].range = convert_integer(fld,10);			break;	// range
					case 10: db[cnt].atk1 = convert_integer(fld,10);			break;	// atk1
					case 11: db[cnt].atk2 = convert_integer(fld,10);			break;	// atk2
					case 12: db[cnt].def = convert_integer(fld,10);				break;	// def
					case 13: db[cnt].mdef = convert_integer(fld,10);			break;	// mdef
					case 14: db[cnt].str = convert_integer(fld,10);				break;	// str
					case 15: db[cnt].agi = convert_integer(fld,10);				break;	// agi
					case 16: db[cnt].vit = convert_integer(fld,10);				break;	// vit
					case 17: db[cnt].intr = convert_integer(fld,10);			break;	// intr
					case 18: db[cnt].dex = convert_integer(fld,10);				break;	// dex
					case 19: db[cnt].luk = convert_integer(fld,10);				break;	// luk
					case 20: db[cnt].range2 = convert_integer(fld,10);			break;	// range2
					case 21: db[cnt].range3 = convert_integer(fld,10);			break;	// range3
					case 22: db[cnt].scale = convert_integer(fld,10);			break;	// scale
					case 23: db[cnt].race = convert_integer(fld,10);			break;	// race
					case 24: db[cnt].element = convert_integer(fld,10);		break;	// element
					case 25: db[cnt].mode = convert_uinteger(fld,16); 			break;	// mode
					case 26: db[cnt].speed = convert_integer(fld,10);			break;	// speed
					case 27: db[cnt].adelay = convert_integer(fld,10);			break;	// adelay
					case 28: db[cnt].amotion = convert_integer(fld,10);		break;	// amotion
					case 29: db[cnt].dmotion = convert_integer(fld,10);		break;	// dmotion
					case 30: db[cnt].mexp = convert_integer(fld,10);			break;	// mexp
					case 31: data_fld++;
					//case 31: db[cnt].expper = convert_integer(fld,10);		break;	// expper
					case 32: db[cnt].mvp1id = convert_integer(fld,10);			break;	// mvp1id
					case 33: db[cnt].mvp1per = convert_integer(fld,10);		break;	// mvp1per
					case 34: db[cnt].mvp2id = convert_integer(fld,10);			break;	// mvp2id
					case 35: db[cnt].mvp2per = convert_integer(fld,10);		break;	// mvp2per
					case 36: db[cnt].mvp3id = convert_integer(fld,10);			break;	// mvp3id
					case 37: db[cnt].mvp3per = convert_integer(fld,10);		break;	// mvp3per
					case 38: db[cnt].drop1id = convert_integer(fld,10);		break;	// drop1id
					case 39: db[cnt].drop1per = convert_integer(fld,10);		break;	// drop1per
					case 40: db[cnt].drop2id = convert_integer(fld,10);		break;	// drop2id
					case 41: db[cnt].drop2per = convert_integer(fld,10);		break;	// drop2per
					case 42: db[cnt].drop3id = convert_integer(fld,10);		break;	// drop3id
					case 43: db[cnt].drop3per = convert_integer(fld,10);		break;	// drop3per
					case 44: db[cnt].drop4id = convert_integer(fld,10);		break;	// drop4id
					case 45: db[cnt].drop4per = convert_integer(fld,10);		break;	// drop4per
					case 46: db[cnt].drop5id = convert_integer(fld,10);		break;	// drop5id
					case 47: db[cnt].drop5per = convert_integer(fld,10);		break;	// drop5per
					case 48: db[cnt].drop6id = convert_integer(fld,10);		break;	// drop6id
					case 49: db[cnt].drop6per = convert_integer(fld,10);		break;	// drop6per
					case 50: db[cnt].drop7id = convert_integer(fld,10);		break;	// drop7id
					case 51: db[cnt].drop7per = convert_integer(fld,10);		break;	// drop7per
					case 52: db[cnt].drop8id = convert_integer(fld,10);		break;	// drop8id
					case 53: db[cnt].drop8per = convert_integer(fld,10);		break;	// drop8per
					case 54: db[cnt].drop9id = convert_integer(fld,10);		break;	// drop9id
					case 55: db[cnt].drop9per = convert_integer(fld,10);		break;	// drop9per
					case 56: db[cnt].dropcardid = convert_integer(fld,10);	break;	// dropcardid
					case 57: db[cnt].dropcardper = convert_integer(fld,10);	break;	// dropcardper
					default: fprintf(stdout,"warn: mobdb_load; invalid field column %s in %s", fld, buf); break;
				}
				read_fld = 0;
				data_fld++;
			} else {
				fld[read_fld] = buf[read_buf];
            read_fld++;
			}

			if(buf[read_buf] == '\0' || buf[read_buf] == '\n') break;
			read_buf++;
		}

		if(data_fld != MOB_COLUMNS) 
         fprintf(stdout,"warn: mobdb_load; missing field expected %d got %d; %s", MOB_COLUMNS, data_fld, buf);
		cnt++;
	}
	return cnt;
}

void mobdb_unload(mob_w * mob_db) {
	int32_t i = 0;
	mob_t mob;
	if(mob_db != NULL) {
      if(mob_db->db != NULL) {
         for(i = DB_BEGIN; i < mob_db->size; i++) {
            mob = mob_db->db[i];
            if(mob.sprite != NULL) free(mob.sprite);
            if(mob.kro != NULL) free(mob.kro);
            if(mob.iro != NULL) free(mob.iro);
         }
         free(mob_db->db);
      }
      free(mob_db);
   }
}

// database io functions
void mobdb_io(mob_t mob, FILE *mob_stm) {
	if(mob_stm == NULL) return;
	fprintf(mob_stm,"%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,0x%x,%d,%d,%d,%d,%d,"
										 , mob.id, mob.sprite, mob.kro, mob.iro 
										 , mob.lv, mob.hp, mob.sp, mob.exp 
										 , mob.jexp, mob.range, mob.atk1, mob.atk2 
										 , mob.def, mob.mdef, mob.str, mob.agi 
										 , mob.vit, mob.intr,mob.dex,mob.luk 
										 , mob.range2,mob.range2,mob.scale,mob.race 
										 , mob.element,mob.mode,mob.speed,mob.adelay 
										 , mob.amotion,mob.dmotion,mob.mexp);
	
	fprintf(mob_stm,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"
		, mob.mvp1id, mob.mvp1per, mob.mvp2id, mob.mvp2per, mob.mvp3id, mob.mvp3per
		, mob.drop1id, mob.drop1per, mob.drop2id, mob.drop2per, mob.drop3id, mob.drop3per
		, mob.drop4id, mob.drop4per, mob.drop5id, mob.drop5per, mob.drop6id, mob.drop6per
		, mob.drop7id, mob.drop7per, mob.drop8id, mob.drop8per, mob.drop9id, mob.drop9per
		, mob.dropcardid, mob.dropcardper);
}

void mobdb_read(mob_w * mob_db) {
	int32_t i;
	for(i = DB_BEGIN; i < mob_db->size; i++)
		mobdb_io(mob_db->db[i], stdout);
}

void mobdb_write(mob_w * mob_db, const char * file_name) {
	int32_t i;
	FILE * file_stm = fopen(file_name,"w");
	if(file_stm == NULL) return;
	for(i = DB_BEGIN; i < mob_db->size; i++)
		mobdb_io(mob_db->db[i], file_stm);
	fclose(file_stm);
}

// generic functions for getting and setting
int32_t * mobdb_id(void * field) { return &((mob_t *)field)->id; }
int32_t * mobdb_lv(void * field) { return &((mob_t *)field)->lv; }
int32_t * mobdb_hp(void * field) { return &((mob_t *)field)->hp; }
int32_t * mobdb_sp(void * field) { return &((mob_t *)field)->sp; }
int32_t * mobdb_exp(void * field) { return &((mob_t *)field)->exp; }
int32_t * mobdb_jexp(void * field) { return &((mob_t *)field)->jexp; }
int32_t * mobdb_range(void * field) { return &((mob_t *)field)->range; }
int32_t * mobdb_atk1(void * field) { return &((mob_t *)field)->atk1; }
int32_t * mobdb_atk2(void * field) { return &((mob_t *)field)->atk2; }
int32_t * mobdb_def(void * field) { return &((mob_t *)field)->def; }
int32_t * mobdb_mdef(void * field) { return &((mob_t *)field)->mdef; }
int32_t * mobdb_str(void * field) { return &((mob_t *)field)->str; }
int32_t * mobdb_agi(void * field) { return &((mob_t *)field)->agi; }
int32_t * mobdb_vit(void * field) { return &((mob_t *)field)->vit; }
int32_t * mobdb_intr(void * field) { return &((mob_t *)field)->intr; }
int32_t * mobdb_dex(void * field) { return &((mob_t *)field)->dex; }
int32_t * mobdb_luk(void * field) { return &((mob_t *)field)->luk; }
int32_t * mobdb_range2(void * field) { return &((mob_t *)field)->range2; }
int32_t * mobdb_range3(void * field) { return &((mob_t *)field)->range3; }
int32_t * mobdb_scale(void * field) { return &((mob_t *)field)->scale; }
int32_t * mobdb_race(void * field) { return &((mob_t *)field)->race; }
int32_t * mobdb_element(void * field) { return &((mob_t *)field)->element; }
int32_t * mobdb_speed(void * field) { return &((mob_t *)field)->speed; }
int32_t * mobdb_adelay(void * field) { return &((mob_t *)field)->adelay; }
int32_t * mobdb_amotion(void * field) { return &((mob_t *)field)->amotion; }
int32_t * mobdb_dmotion(void * field) { return &((mob_t *)field)->dmotion; }
int32_t * mobdb_mexp(void * field) { return &((mob_t *)field)->mexp; }
char * mobdb_sprite(void * field) { return ((mob_t *)field)->sprite; }
char * mobdb_kro(void * field) { return ((mob_t *)field)->kro; }
char * mobdb_iro(void * field) { return ((mob_t *)field)->iro; }
uint32_t * mobdb_mode(void * field) { return &((mob_t *)field)->mode; }
int32_t * mobdb_dropcardid(void * field) { return &((mob_t *)field)->dropcardid; }
int32_t * mobdb_getint(void * db, int32_t index, DBFIELD field) { return field(&(((mob_t *) db)[index])); }
char * mobdb_getstr(void * db, int32_t index, DBFIELD_STR field) { return field(&(((mob_t *) db)[index])); }
void mobdb_swap(void * db, int32_t a, int32_t b) {
	mob_t * mob_db = db;
	mob_t temp = mob_db[a];
	mob_db[a] = mob_db[b];
	mob_db[b] = temp;
}