// Test item_bonus.c / mob.c
#include "const.h"
#include "mob.h"
#include "skill.h"

int main(int argc, char * argv[]) {
   //const_w * const_db = (const_w *) load("db/const.txt", constdb_trim, constdb_load, sizeof(const_t));
   //hpsort_str(const_db->db, const_db->size, constdb_name, constdb_getstr, constdb_swap);
   //constdb_read(const_db);
   //constdb_unload(const_db);

   //mob_w * mob_db = (mob_w *) load("db/mob_db.txt", general_trim, mobdb_load, sizeof(mob_t));
   //hpsort_str(mob_db->db, mob_db->size, mobdb_sprite, mobdb_getstr, mobdb_swap);
   //mobdb_write(mob_db, "new_mob_db.txt");
   //mobdb_unload(mob_db);

   skill_w * skill_db = (skill_w *) load("db/skill_db.txt", general_trim, skilldb_load, sizeof(skill_t));
   //skilldb_read(skill_db);
   hpsort_str(skill_db->db, skill_db->size, skilldb_name, skilldb_getstr, skilldb_swap);
   skilldb_write(skill_db,"new_skill_db.txt");
   skilldb_unload(skill_db);
   exit(EXIT_SUCCESS);
}