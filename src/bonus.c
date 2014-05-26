/*=============================================================================
   file: bonus.c
   date: 5/9/2014
 update: 5/23/2014
   auth: trickyloki3
   desc: item bonus database management
   note: very simple code
=============================================================================*/
#include "bonus.h"
static char * bonusdb_trim(const char *, const char *, int *);

bonus_w * bonusdb_init(const char * filename, const char * prefix) {
   /* bonus wrapper data */
   bonus_w * bonus_wrapper = NULL;
   bonus_t * bonus_database = NULL;
   char * bonus_filename = NULL;
   int32_t bonus_size = 0;
   int32_t bonus_count = DB_BEGIN;

   /* bonus load data */
   FILE * bonus_file = NULL;
   char bonus_buf[BUF_SIZE];                 /* item buffer */
   char bonus_fld[BUF_SIZE];                 /* field buffer */
   int32_t read_buf = 0;                     /* current item buffer index */
   int32_t read_fld = 0;                     /* current item field index */
   int32_t quote_level = 0;                  /* string literal enclosed in quotes */
   int32_t field_level = 0;
   int32_t var_state = 0;
   int32_t type_cnt = 0;
   int32_t order_cnt = 0;
   /* filter the database for valid entries per line */
   bonus_filename = bonusdb_trim(filename, prefix, &bonus_size);
   if(bonus_filename == NULL) {
      fprintf(stdout,"warn: bonusdb_load failed to filter original database file %s\n", filename);
      return NULL;
   }

   /* check if the file have at least one valid entry */
   if(bonus_size <= 0) {
      fprintf(stdout,"warn: bonusdb_load failed to detect valid entries in the original database file %s\n", filename);
      if(bonus_filename != NULL) free(bonus_filename);
      return NULL;
   }

   /* allocate memory for the database */
   bonus_database = malloc(sizeof(bonus_t) * (bonus_size + DB_BEGIN));
   if(bonus_database == NULL) {
      fprintf(stdout,"warn: bonusdb_load failed to allocate memory for database.\n");
      if(bonus_filename != NULL) free(bonus_filename);
      return NULL;
   }
   memset(bonus_database,0,sizeof(bonus_t) * (bonus_size + DB_BEGIN));

   /* open filtered database for reading */
   bonus_file = fopen(bonus_filename, "r");
   if(bonus_file == NULL) {
      fprintf(stdout,"warn: itemdb_load failed to open filtered database file %s.\n", bonus_filename);
      if(bonus_database != NULL) free(bonus_database);
      if(bonus_filename != NULL) free(bonus_filename);
      return NULL;
   }

   /* load the database into memory */
   while(fgets(bonus_buf, BUF_SIZE, bonus_file) != NULL) {
      read_buf = 0;
      read_fld = 0;
      quote_level = 0;
      field_level = 0;
      var_state = 0;
      type_cnt = 0;
      order_cnt = 0;

      /* read the bonus entry */
      while(1) {
         /* check if reading quote */
         if(bonus_buf[read_buf] == '\"' && !quote_level)
            quote_level++;
         /* check if closing quote */
         else if(bonus_buf[read_buf] == '\"' && quote_level)
            quote_level--;

         /* check if delimiter for field */
         if(!quote_level && (isspace(bonus_buf[read_buf]) || bonus_buf[read_buf] == ',' || bonus_buf[read_buf] == ';' || bonus_buf[read_buf] == '\0')) {
            bonus_fld[read_fld] = '\0';
            switch(field_level) {
               case 0: bonus_database[bonus_count].pref = convert_string(bonus_fld); break;
               case 1: bonus_database[bonus_count].buff = convert_string(bonus_fld); break;
               case 2: bonus_database[bonus_count].attr = convert_integer(bonus_fld, 16); break;
               case 3: bonus_database[bonus_count].desc = convert_string(bonus_fld); break;
               case 4: bonus_database[bonus_count].type_cnt = convert_integer(bonus_fld, 10); 
                       bonus_database[bonus_count].type = malloc(sizeof(int32_t) * bonus_database[bonus_count].type_cnt);
                       break;
               default: 
                  if(var_state < bonus_database[bonus_count].type_cnt) {
                     bonus_database[bonus_count].type[type_cnt] = bonus_fld[0];
                     var_state++;
                     type_cnt++;
                  } else if(bonus_database[bonus_count].order == NULL) {
                     bonus_database[bonus_count].order_cnt = convert_integer(bonus_fld, 10); 
                     bonus_database[bonus_count].order = malloc(sizeof(int32_t) * bonus_database[bonus_count].order_cnt);
                  } else {
                     bonus_database[bonus_count].order[order_cnt] = convert_integer(bonus_fld, 10); 
                     order_cnt++;
                  }
                  break;
            }
            read_fld = 0;
            field_level++;

            /* skip all other whitespace */
            while(isspace(bonus_buf[read_buf+1]) && bonus_buf[read_buf+1] != '\0') read_buf++;
         /* copy from bonus buffer to field buffer */
         } else {
            bonus_fld[read_fld] = bonus_buf[read_buf];
            read_fld++;
         }

         /* finish reading the bonus */
         if(bonus_buf[read_buf] == '\0' || bonus_buf[read_buf] == '\n' || bonus_buf[read_buf] == ';') break;
         read_buf++;
      }

      /* check for missing brackets */
      if(quote_level)
         fprintf(stdout,"warn: missing quote %s: %s", filename, bonus_buf);

      bonus_count++;
   }

   /* clean up loading resources */
   fclose(bonus_file);
   remove(bonus_filename);
   free(bonus_filename);

   /* return the item wrapper */
   bonus_wrapper = malloc(sizeof(bonus_w));
   bonus_wrapper->db = bonus_database;
   bonus_wrapper->size = bonus_size + DB_BEGIN;
   return bonus_wrapper;
}

bonus_w * bonusdb_deinit(bonus_w * bonus_db) {
   int32_t i = 0;
   bonus_t bonus;
   if(bonus_db != NULL) {
      if(bonus_db->db != NULL) {
         for(i = DB_BEGIN; i < bonus_db->size; i++) {
            bonus = bonus_db->db[i];
            if(bonus.pref != NULL) free(bonus.pref);
            if(bonus.buff != NULL) free(bonus.buff);
            if(bonus.desc != NULL) free(bonus.desc);
            if(bonus.type != NULL) free(bonus.type);
            if(bonus.order != NULL) free(bonus.order);
         }
         free(bonus_db->db);
      }
      free(bonus_db);
   }
   return NULL;
}

void bonusdb_io(bonus_t bonus, FILE * file_stm) {
   int32_t i;
   fprintf(file_stm,"%s %s,0x%02x,%s,%d,",bonus.pref, bonus.buff, bonus.attr, bonus.desc, bonus.type_cnt);
   for(i = 0; i < bonus.type_cnt; i++) fprintf(file_stm,"%c,",bonus.type[i]);
   fprintf(file_stm,"%d,",bonus.order_cnt);
   for(i = 0; i < bonus.order_cnt - 1; i++) fprintf(file_stm,"%d,",bonus.order[i]);
   fprintf(file_stm,"%d;\n",bonus.order[i]);
}

void bonusdb_read(bonus_w * bonus_db) {
   int32_t i;
   for(i = DB_BEGIN; i < bonus_db->size; i++)
      bonusdb_io(bonus_db->db[i],stdout);
}

void bonusdb_write(bonus_w * bonus_db, char * file) {
   int32_t i;
   FILE * file_stm = fopen(file,"w");
   if(file_stm == NULL) return;

   for(i = DB_BEGIN; i < bonus_db->size; i++)
      bonusdb_io(bonus_db->db[i], file_stm);
   
   fclose(file_stm);
}

static char * bonusdb_trim(const char * filename, const char * prefix, int * size) {
   char * trim_filename = NULL;
   FILE * bonusdb_file = NULL;
   FILE * bonusdb_trim = NULL;
   int32_t bonusdb_size = 0;

   char bonus_buf[BUF_SIZE];
   char bonus_fld[BUF_SIZE];
   int32_t i = 0;

   /* check if paramaters are valid */
   if(filename == NULL || prefix == NULL || size == NULL) {
      fprintf(stdout,"warn: bonusdb_trim detected NULL paramaters.\n");
      return NULL;
   }

   /* failed to allocate temporary filename */
   trim_filename = random_string(16);
   if(trim_filename == NULL) {
      fprintf(stdout,"warn: bonusdb_trim temporary filename failed to allocate memory.\n");
      return NULL;
   }

   /* failed to open original or temporary files */
   bonusdb_file = fopen(filename,"r");
   bonusdb_trim = fopen(trim_filename,"w");
   if(bonusdb_file == NULL || bonusdb_trim == NULL) {
      fprintf(stdout,"warn: bonusdb_trim failed to open %s or %s\n.", trim_filename, filename);
      if(trim_filename != NULL) free(trim_filename);
      fclose(bonusdb_file);
      fclose(bonusdb_trim);
      return NULL;
   }

   /* filter bonus database for valid entries only */
   while(fgets(bonus_buf, sizeof(bonus_buf), bonusdb_file) != NULL) {
      bonus_fld[0] = '\0';
      substr_delimit(bonus_buf, bonus_fld, ' ');
      if(strlen(bonus_fld) >= strlen(prefix))
         if(bonus_buf[0] != '/')
            if(ncs_strcmp(prefix, bonus_fld) == 0) {
               fprintf(bonusdb_trim, "%s",bonus_buf);
               bonusdb_size++;
            }
   }

   *size = bonusdb_size;
   fclose(bonusdb_file);
   fclose(bonusdb_trim);
   return trim_filename;
}

char * bonusdb_pref(void * field) { return ((bonus_t *)field)->pref; }
char * bonusdb_buff(void * field) { return ((bonus_t *)field)->buff; }
int * bonusdb_attr(void * field) { return &((bonus_t *)field)->attr; }
int * bonusdb_getint(void * db, int index, DBFIELD field) { return field(&(((bonus_t *) db)[index])); }
char * bonusdb_getstr(void * db, int index, DBFIELD_STR field) { return field(&(((bonus_t *) db)[index])); }
int bonusdb_getsizeof(void) { return sizeof(bonus_t); }
void bonusdb_swap(void * db, int a, int b) {
   bonus_t * bonus_db = db;
   bonus_t temp = bonus_db[a];
   bonus_db[a] = bonus_db[b];
   bonus_db[b] = temp;
}