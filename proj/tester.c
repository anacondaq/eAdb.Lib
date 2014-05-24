#include "skill.h"
#include "produce.h"
#include "pet.h"
#include "mob.h"
#include "merc.h"
#include "const.h"
#include "bonus.h"
#include "item.h"

int main(int argc, char * argv[]) {
   /*
   skill_w * skill_db = skilldb_init("db/skill_db.txt");
   skilldb_deinit(skill_db);

   produce_w * produce_db = producedb_init("db/produce_db.txt");
   producedb_write(produce_db,"produce_db_new.txt");
   producedb_deinit(produce_db);

   pet_w * pet_db = petdb_init("db/pet_db.txt");
   petdb_write(pet_db, "pet_db_new.txt");
   petdb_deinit(pet_db);

   mob_w * mob_db = mobdb_init("db/mob_db.txt");
   mobdb_write(mob_db, "mob_db_new.txt");
   mobdb_deinit(mob_db);

   merc_w * merc_db = mercdb_init("db/mercenary_db.txt");
   mercdb_write(merc_db, "mercenary_db_new.txt");
   mercdb_deinit(merc_db);

   const_w * const_db = constdb_init("db/const.txt");
   constdb_write(const_db,"const_db_new.txt");
   constdb_deinit(const_db);

   bonus_w * bonus_db = bonusdb_init("db/item_bonus.txt","bonus",BONUS1_FIELD_COUNT);
   bonusdb_write(bonus_db,"item_bonus_new.txt");
   bonusdb_read(bonus_db);
   bonusdb_deinit(bonus_db);
   */

   item_w * item_db = itemdb_init("db/item_db.txt");
   itemdb_writeall(item_db,"item_db_new.txt");
   itemdb_deinit(item_db);
   
   return 0;
}