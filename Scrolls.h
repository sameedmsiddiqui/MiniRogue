#ifndef SCROLLS_H
#define SCROLLS_H

#include "Object.h"
#include "Player.h"
#include <string>

class Dungeon;

class Scroll: public Object{
public:
	Scroll(std::string n, int r, int c, std::string m) : Object(n, '?', r, c), message(m){;}
	virtual ~Scroll(){;}
	virtual void read(Player* p) = 0;
	std::string read_message() {return message;}
private:
	std::string message;

};

class scroll_of_teleportation : public Scroll{
public:
	scroll_of_teleportation(int r, int c) : Scroll("scroll of teleportation", r, c, "You feel your body wrenched in space and time. \n"){;}
	void read(Player* p, Dungeon* d){;}
	void read(Player* p);
};

class scroll_of_improve_armor : public Scroll{
public:
	scroll_of_improve_armor(int r, int c) : Scroll("scroll of improve armor", r, c, "Your armor glows blue."){;}
	void read(Player* p);
};

class scroll_of_raise_strength : public Scroll{
public:
	scroll_of_raise_strength(int r, int c) : Scroll("scroll of strength", r, c, "Your muscles bulge."){;}
	void read(Player* p);
};

class scroll_of_enhance_health : public Scroll{
public:
	scroll_of_enhance_health(int r, int c) : Scroll("scroll of enhance health", r, c, "You feel your heart beating stronger."){;}
	void read(Player* p);
};

class scroll_of_enhance_dexterity : public Scroll{
public:
	scroll_of_enhance_dexterity(int r, int c) : Scroll("scroll of enhance dexterity", r, c, "You feel like less of a klutz."){;}
	void read(Player* p);
};


#endif//SCROLLS_H