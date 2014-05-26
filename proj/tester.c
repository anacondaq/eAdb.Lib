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

   item_w * item_db = itemdb_init("db/item_db.txt");
   itemdb_writeall(item_db,"item_db_new.txt");
   itemdb_deinit(item_db);
   */

   bonus_w * bonus_db1 = bonusdb_init("db/item_bonus.txt","bonus");
   bonus_w * bonus_db2 = bonusdb_init("db/item_bonus.txt","bonus2");
   bonus_w * bonus_db3 = bonusdb_init("db/item_bonus.txt","bonus3");
   bonus_w * bonus_db4 = bonusdb_init("db/item_bonus.txt","bonus4");
   bonus_w * bonus_db5 = bonusdb_init("db/item_bonus.txt","bonus5");
   
   bonusdb_write(bonus_db1,"item_bonus1.txt");
   bonusdb_write(bonus_db2,"item_bonus2.txt");
   bonusdb_write(bonus_db3,"item_bonus3.txt");
   bonusdb_write(bonus_db4,"item_bonus4.txt");
   bonusdb_write(bonus_db5,"item_bonus5.txt");
   /*
   bonusdb_read(bonus_db1);
   bonusdb_read(bonus_db2);
   bonusdb_read(bonus_db3);
   bonusdb_read(bonus_db4);
   bonusdb_read(bonus_db5);
   */
   bonusdb_deinit(bonus_db1);
   bonusdb_deinit(bonus_db2);
   bonusdb_deinit(bonus_db3);
   bonusdb_deinit(bonus_db4);
   bonusdb_deinit(bonus_db5);
   return 0;
}