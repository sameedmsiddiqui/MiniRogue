#ifndef DUNGEON_H
#define DUNGEON_H

#include "Game.h"
#include <vector>
#include <string>
using std::vector;
using std::string;


class Actor;
class Object;
class Player;


class Dungeon{
public:	
	Dungeon(Game* g, int l, Player* pp);
	// TO DO: IMPLEMENT DESTRUCTOR!
	~Dungeon();
	char at_pos(int r, int c) const {return grid[r][c];}
	void setMap(int r, int c, char value) {grid[r][c] = value;}
	Game* game() { return gm;}
	void display(string msg);
	vector<Actor*>& Actors() {return actors;}
	vector<Object*>& Objects() {return objects;}
	Player* player() {return p;}

private:
	Game* gm;
	int level;
	char grid[18][70];
	char basic_grid[18][70];
	vector<Actor*> actors;
	vector<Object*> objects;
	Player* p;
};




#endif//DUNGEON_H