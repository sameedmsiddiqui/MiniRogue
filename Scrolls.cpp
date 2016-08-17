#include "Object.h"
#include "Scrolls.h"
#include "Player.h"
#include "my_utilities.h"
#include "Dungeon.h"

void scroll_of_teleportation::read(Player* p){
	int r = 0, c = 0;

	Dungeon* d = p->dungeon();

	// generate a random coordinate that is a valid destination for the player.
	do{
		r = randInt(1,16);
		c = randInt(1,68);
	} while(!(d->at_pos(r,c) == ' ' || d->at_pos(r,c) == ')' || d->at_pos(r,c) == '>' || d->at_pos(r,c) == '?'));

	p->set_pos(r,c);
}

void scroll_of_improve_armor::read(Player* p){
	p->change_arm_by(randInt(1,3));
}


void scroll_of_raise_strength::read(Player* p){
	p->change_str_by(randInt(1,3));
}


void scroll_of_enhance_health::read(Player* p){
	p->change_max_hp(randInt(3,8));
}

void scroll_of_enhance_dexterity::read(Player* p){
	p->change_dext_by(1);
}
