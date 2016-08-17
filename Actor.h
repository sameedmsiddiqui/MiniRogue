#ifndef ACTOR_H
#define ACTOR_H

#include "Dungeon.h"
#include "Object.h"
#include "Weapons.h"
#include <string>

class Actor{
public:
	Actor(Dungeon* d, int r, int c, int hp, int str, int dext, int armr, Weapon* weap, char disp, std::string n) : dung(d), r_coord(r), 
		c_coord(c), hit_points(hp), strength(str), dexterity(dext), armour(armr), equipped_weapon(weap), sleep(0), display_char(disp), nm(n) {;}
	virtual ~Actor(){delete equipped_weapon;}
	int isAsleep() { return sleep;}
	int change_sleep(int n);
	// return true if the attacker is able to (e.g. is in range) attack target
	std::string attack(Actor* target);
	char display() {return display_char;}
	// return -1 if the attacker will move, else return 
	// 0 = down, 1 = right, 2 = up, 3 = left 
	virtual string move(Actor* target) {return "";}
	virtual string move(int direction) {return "";}
	void set_pos(int r, int c){ r_coord = r; c_coord = c;}
	int p_r(){ return r_coord;}
	int p_c(){ return c_coord;}
	Dungeon*& dungeon(){return dung;}
	void set_dungeon(Dungeon* d){dung = d;}
	void set_weapon(Weapon* w){ equipped_weapon = w;}
	Weapon* weapon(){ return equipped_weapon;}
	int hp() {return hit_points;}
	int str(){ return strength;}
	int dext() {return dexterity;}
	int arm() {return armour;}
	void change_hp_by(int h) {hit_points += h;}
	void change_str_by(int h) {strength += h;}
	void change_dext_by(int h) {dexterity += h;}
	void change_arm_by(int h) {armour += h;}
	std::string name() {return nm;}
private:
	int display_char;
	int r_coord;
	int c_coord;
	Weapon* equipped_weapon;
	int hit_points;
	int strength;
	int dexterity;
	int armour;
	Dungeon* dung;
	int sleep;
	std::string nm;
};




#endif//ACTOR_H