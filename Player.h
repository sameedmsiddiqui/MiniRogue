#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Object.h"
#include "Dungeon.h"
#include <vector>
#include <string>

class Player : public Actor{
public:
	Player(Dungeon* d, int r, int c) : Actor(d, r, c, 20, 2, 2, 2, new short_sword, '@', "Player"), max_hit_points(20){;}
	std::string move(int direction);
	int max_hp() {return max_hit_points;}
	void change_max_hp(int n){ max_hit_points += n;}
	std::string view_inventory(char ch);
	void add_to_inventory(Object* o){inventory.push_back(o);}
	std::string pickup_object();
	bool pick_stairs();
private:
	int max_hit_points;
	vector<Object*> inventory;
};




#endif//PLAYER_H