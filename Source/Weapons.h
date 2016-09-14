#ifndef WEAPONS_H
#define WEAPONS_H


#include <string>
#include "Object.h"
class Weapon : public Object{
public:
	Weapon(std::string n, int r, int c, int dex, int dam, std::string attack_text) : Object(n, ')', r, c), dext(dex), damg(dam), attack_call(attack_text){;}
		// r and c are the row and column, respectively, where the weapon is to be displayed
	virtual ~Weapon(){;}
	int dexterity() const{ return dext;}
	int damage() const {return damg;}
	std::string attack_action();
private:
	int dext;
	int damg;
	std::string attack_call;
};


class mace : public Weapon{
public:
	mace(int r, int c) : Weapon("mace", r, c, 0, 2, "swings"){;}
	mace() : Weapon("mace", -1, -1, 0, 2, "swings"){;}
	// NOTE TO SELF: you could later replace the above two implementations with
	// mace(int r = -1, int c = -1) : Weapon("mace", r, c, 0, 2, "swings"){;}
};

class short_sword : public Weapon{
public:
	short_sword(int r, int c) : Weapon("short sword", r, c, 0, 2, "slashes"){;}
	short_sword() : Weapon("short sword", -1, -1, 0, 2, "slashes"){;}
};

class long_sword : public Weapon{
public:
	long_sword(int r, int c) : Weapon("long sword", r, c, 0, 2, "swings"){;}
	long_sword() : Weapon("long sword", -1, -1, 0, 2, "swings"){;}
};

class magic_fangs : public Weapon{
public:
	magic_fangs(int r, int c) : Weapon("magic fangs", r, c, 0, 2, "strikes"){;}
	magic_fangs() : Weapon("magic fangs", -1, -1, 0, 2, "strikes"){;}
};

class magic_axe : public Weapon{
public:
	magic_axe(int r, int c) : Weapon("magic axe", r, c, 0, 2, "chops"){;}
};


#endif//WEAPONS_H
