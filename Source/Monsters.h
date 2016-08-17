#ifndef MONSTERS_H
#define MONSTERS_H

#include "Actor.h"
#include "utilities.h"
#include "my_utilities.h"
#include <string>


class Bogeyman : public Actor {
public:
	Bogeyman(Dungeon* d, int r, int c) : Actor(d, r, c, randInt(5,10), randInt(2,3), randInt(2,3), 2, new short_sword, 'B', "the Bogeyman"){;}
	std::string move(Actor* target);
private:
	;
};

class Snakewoman : public Actor {
public:
	Snakewoman(Dungeon* d, int r, int c) : Actor(d, r, c, randInt(3,6), 2, 3, 3, new magic_fangs, 'S', "the Snakewoman"){;}
	std::string move(Actor* target);
private:
	;
};

class Dragon : public Actor {
public:
	Dragon(Dungeon* d, int r, int c) : Actor(d, r, c, randInt(20,25), 4, 4, 4, new long_sword, 'D', "the Dragon"){;}
	std::string move(Actor* target);
private:
	;
};

class Goblin : public Actor {
public:
	Goblin(Dungeon* d, int r, int c) : Actor(d, r, c, randInt(15,20), 3, 1, 1, new short_sword, 'G', "the Goblin"){;}
	std::string move(Actor* target);
private:
	;
};

#endif//MONSTERS_H