#include <cstdlib>
#include "Actor.h"
#include "Dungeon.h"
#include <cmath>
#include "Monsters.h"
#include "utilities.h"
#include "my_utilities.h"
#include <string>
#include "Player.h"

using namespace std;

std::string Bogeyman::move(Actor* target){
	if (isAsleep() > 0){ 
		change_sleep(-1);
		return "";
	}

	// check if the Bogeyman is within smelling distance of the target.
	if (abs(p_c() - target->p_c()) + abs(p_r() - target->p_r()) > 5)
		return "NO MOVE";


	//check if the Bogeyman can makea valid move in the turn;
	if (target->p_c() > p_c() && (dungeon()->at_pos(p_r(), p_c()+1) == ')' || dungeon()->at_pos(p_r(), p_c()+1) == '>' || dungeon()->at_pos(p_r(), p_c()+1) == '&' || dungeon()->at_pos(p_r(), p_c()+1) == '?' || dungeon()->at_pos(p_r(), p_c()+1) == ' ')){
		dungeon()->setMap(p_r(), p_c(),' ');
		set_pos(p_r(), p_c()+1);
		dungeon()->setMap(p_r(), p_c()+1, 'B');
		return "";
	}

	else if (target->p_c() < p_c() && (dungeon()->at_pos(p_r(), p_c()-1) == ')' || dungeon()->at_pos(p_r(), p_c()-1) == '>' || dungeon()->at_pos(p_r(), p_c()-1) == '&' || dungeon()->at_pos(p_r(), p_c()-1) == '?' || dungeon()->at_pos(p_r(), p_c()-1) == ' ')){
		dungeon()->setMap(p_r(), p_c(),' ');
		set_pos(p_r(), p_c()-1);
		dungeon()->setMap(p_r(), p_c()-1, 'B');
		return ""; 
	}
	
	else if (target->p_r() > p_r() && (dungeon()->at_pos(p_r()+1, p_c()) == ')' || dungeon()->at_pos(p_r()+1, p_c()) == '>' ||  dungeon()->at_pos(p_r()+1, p_c()) == '&' || dungeon()->at_pos(p_r()+1, p_c()) == '?' || dungeon()->at_pos(p_r()+1, p_c()) == ' ')){
		dungeon()->setMap(p_r(), p_c(),' ');
		set_pos(p_r()+1, p_c()+1);
		dungeon()->setMap(p_r()+1, p_c(), 'B');
		return ""; 
	}

	else if (target->p_r() < p_r() && (dungeon()->at_pos(p_r()-1, p_c()) == ')' || dungeon()->at_pos(p_r()-1, p_c()) == '>' || dungeon()->at_pos(p_r()-1, p_c()) == '?' || dungeon()->at_pos(p_r()-1, p_c()) == '&' || dungeon()->at_pos(p_r()-1, p_c()) == ' ')){
		dungeon()->setMap(p_r(), p_c(),' ');
		set_pos(p_r() -1 , p_c());
		dungeon()->setMap(p_r()-1, p_c(), 'B');
		return ""; 
	}

	else if (dungeon()->at_pos(p_r(), p_c()+1) == '@'){
		return attack(dungeon()->player());
	}
	
	else if (dungeon()->at_pos(p_r()+1, p_c()) == '@'){
		return attack(dungeon()->player());
	}

	else if (dungeon()->at_pos(p_r(), p_c()-1) == '@'){
		return attack(dungeon()->player());
	}
	
	else if (dungeon()->at_pos(p_r()-1, p_c()) == '@'){
		return attack(dungeon()->player());
	}
	
	

	return "NO MOVE";
}

std::string Snakewoman::move(Actor* target){
	if (isAsleep() > 0){ 
		change_sleep(-1);
		return "";
	}

	// check if the Snakewoman is within smelling distance of the target.
	if (abs(p_c() - target->p_c()) + abs(p_r() - target->p_r()) > 3){
		return "NO MOVE";
	}
	

	//check if the Snakwoman can makea valid move in the turn;
	if (target->p_c() > p_c() && ( dungeon()->at_pos(p_r(), p_c()+1) == ')' || dungeon()->at_pos(p_r(), p_c()+1) == '>' || dungeon()->at_pos(p_r(), p_c()+1) == '&' || dungeon()->at_pos(p_r(), p_c()+1) == '?' || dungeon()->at_pos(p_r(), p_c()+1) == ' ')){
		dungeon()->setMap(p_r(), p_c(),' ');
		set_pos(p_r(), p_c()+1);
		dungeon()->setMap(p_r(), p_c(), 'S');
		return "";
	}
	else if (target->p_c() < p_c() && (dungeon()->at_pos(p_r(), p_c()-1) == ')' || dungeon()->at_pos(p_r(), p_c()-1) == '>' || dungeon()->at_pos(p_r(), p_c()-1) == '?' || dungeon()->at_pos(p_r(), p_c()-1) == '&' || dungeon()->at_pos(p_r(), p_c()-1) == ' ')){
		dungeon()->setMap(p_r(), p_c(),' ');
		set_pos(p_r(), p_c()-1);
		dungeon()->setMap(p_r(), p_c(), 'S');

		return ""; 
	}
	else if (target->p_r() > p_r() && (dungeon()->at_pos(p_r()+1, p_c()) == ')' || dungeon()->at_pos(p_r()+1, p_c()) == '&'  || dungeon()->at_pos(p_r()+1, p_c()) == '>' || dungeon()->at_pos(p_r()+1, p_c()) == '?' || dungeon()->at_pos(p_r()+1, p_c()) == ' ')){
		dungeon()->setMap(p_r(), p_c(),' ');
		set_pos(p_r()+1, p_c());
		dungeon()->setMap(p_r(), p_c(), 'S');
		return ""; 
	}

	else if (target->p_r() < p_r() && (dungeon()->at_pos(p_r()-1, p_c()) == ')' || dungeon()->at_pos(p_r()-1, p_c()) == '&'  || dungeon()->at_pos(p_r()-1, p_c()) == '>' || dungeon()->at_pos(p_r()-1, p_c()) == '?' || dungeon()->at_pos(p_r()-1, p_c()) == ' ')){
		dungeon()->setMap(p_r(), p_c(),' ');
		set_pos(p_r()-1, p_c());
		dungeon()->setMap(p_r(), p_c(), 'S');
		return ""; 
	}

	else if (dungeon()->at_pos(p_r(), p_c()+1) == '@'){
		return attack(dungeon()->player());
	}

	else if (dungeon()->at_pos(p_r(), p_c()-1) == '@'){
		return attack(dungeon()->player());
	}

	else if (dungeon()->at_pos(p_r()+1, p_c()) == '@'){
		return attack(dungeon()->player());
	}
	
	else if (dungeon()->at_pos(p_r()-1, p_c()) == '@'){
		return attack(dungeon()->player());
	}

	return "NO MOVE";

}

//TO DO: SEE if it's possible for a dragon to die!

std::string Dragon::move(Actor* target){

	if (isAsleep() > 0){ 
		change_sleep(-1);
		return "";
	}

	if(trueWithProbability(.1))
		if(hp()!=25)
			change_hp_by(1);

	if (dungeon()->at_pos(p_r(), p_c()+1) == '@'){
		return attack(dungeon()->player());
	}
	
	else if (dungeon()->at_pos(p_r()+1, p_c()) == '@'){
		return attack(dungeon()->player());
	}

	else if (dungeon()->at_pos(p_r(), p_c()-1) == '@'){
		return attack(dungeon()->player());
	}
	
	else if (dungeon()->at_pos(p_r()-1, p_c()) == '@'){
		return attack(dungeon()->player());
	}

	// we wont return no move, because Dragon's don't move. 
	return "";
}

// declartion for goblin's move function in goblin.cpp
int Optimal_move(Dungeon* d, int g_r, int g_c, int p_r, int p_c, int MAX_STEPS);

std::string Goblin::move(Actor* target){
	if (isAsleep() > 0){ 
		change_sleep(-1);
		return "";
	}

	int i = Optimal_move(dungeon(), p_r(), p_c(), target->p_r(), target->p_c(), dungeon()->game()->Goblin_smell_distance());

	switch(i){
	case 0:
		if (dungeon()->at_pos(p_r()+1,p_c()) == ' ' || dungeon()->at_pos(p_r()+1,p_c()) == ')' || dungeon()->at_pos(p_r()+1,p_c()) == '>' ||dungeon()->at_pos(p_r()+1,p_c()) == '&' || dungeon()->at_pos(p_r()+1,p_c()) == '?'){
			dungeon()->setMap(p_r(), p_c(),' ');
			set_pos(p_r()+1, p_c());
			dungeon()->setMap(p_r(), p_c(), 'g');
		}
		else if (dungeon()->at_pos(p_r()+1,p_c()) == '@')
			return attack(dungeon()->player());
		break;
	case 1:
		if (dungeon()->at_pos(p_r(),p_c()+1) == ' ' || dungeon()->at_pos(p_r(),p_c()+1) == ')' || dungeon()->at_pos(p_r(),p_c()+1) == '>' ||dungeon()->at_pos(p_r(),p_c()+1) == '&' || dungeon()->at_pos(p_r(),p_c()+1) == '?'){
			dungeon()->setMap(p_r(), p_c()+1,' ');
			set_pos(p_r(), p_c()+1);
			dungeon()->setMap(p_r(), p_c(), 'g');
		}
		else if (dungeon()->at_pos(p_r(),p_c()+1) == '@')
			return attack(dungeon()->player());
		break;
	case 2:
		if (dungeon()->at_pos(p_r()-1,p_c()) == ' ' || dungeon()->at_pos(p_r()-1,p_c()) == ')' || dungeon()->at_pos(p_r()-1,p_c()) == '>' ||dungeon()->at_pos(p_r()-1,p_c()) == '&' || dungeon()->at_pos(p_r()-1,p_c()) == '?'){
			dungeon()->setMap(p_r(), p_c(),' ');
			set_pos(p_r()-1, p_c());
			dungeon()->setMap(p_r(), p_c(), 'g');
		}
		break;
	case 3:
		if (dungeon()->at_pos(p_r(),p_c()-1) == ' ' || dungeon()->at_pos(p_r(),p_c()-1) == ')' || dungeon()->at_pos(p_r(),p_c()-1) == '>' ||dungeon()->at_pos(p_r(),p_c()-1) == '&' || dungeon()->at_pos(p_r(),p_c()-1) == '?'){
			dungeon()->setMap(p_r(), p_c(),' ');
			set_pos(p_r(), p_c()-1);
			dungeon()->setMap(p_r(), p_c(), 'g');
		}
		else if (dungeon()->at_pos(p_r(),p_c()-1) == '@')
			return attack(dungeon()->player());
		break;
	case -1:
		if (dungeon()->at_pos(p_r()+1,p_c()) == '@')
			return attack(dungeon()->player());
		else if (dungeon()->at_pos(p_r(),p_c()+1) == '@')
			return attack(dungeon()->player());
		else if (dungeon()->at_pos(p_r()-1,p_c()) == '@')
			return attack(dungeon()->player());
		else if (dungeon()->at_pos(p_r(),p_c()-1) == '@')
			return attack(dungeon()->player());
		break;
	default:
		;
	}

	if (i == -1)
		return "NO MOVE";
	else return "";
}
