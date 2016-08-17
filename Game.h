// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class Player;
class Dungeon;
class Actor;
// You may add data members and other member functions to this class.




class Game
{
public:
	Game(int goblinSmellDistance);
	void play();
	int Goblin_smell_distance() { return Goblin_Smell_distance;}
	int lvl(){return level;}
	void next_level();
private:
	int Goblin_Smell_distance;
	int level;
	Player* p;
	Dungeon* d;
};

#endif // GAME_INCLUDED
