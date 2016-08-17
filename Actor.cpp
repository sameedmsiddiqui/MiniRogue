#include "Actor.h"
#include "Weapons.h"
#include "utilities.h"
#include "my_utilities.h"
#include "Scrolls.h"
#include <string>


// to do: make move have a return type of -1, but also have a extra parameter called message that's passed by reference
//			which will be modified to contain the attacking message. 
std::string Actor::attack(Actor* target) {
	if (target->hp() <= 0)
		return "this dragon is supposed to be dead \n";
	
	int attackerPoints = dexterity  + equipped_weapon->dexterity();
	int defenderPoints = target->dext() + target->arm(); 

	string msg = this->name() + " slashes " + equipped_weapon->name() + " at " + target->name() + " and ";

	if (randInt(attackerPoints) >= randInt(defenderPoints)){
		msg += "hits";
		target->change_hp_by(-1*randInt(strength + equipped_weapon->damage() ));

		if (target->hp() <= 0){
			msg += " dealing a final blow";

			if (target->name() != "Player"){
				dungeon()->setMap(target->p_r(), target->p_c(), ' ');
				int i = 0;
				for (; i < dungeon()->Actors().size(); i++)
					if (dungeon()->Actors()[i]->p_c() == target->p_c() && dungeon()->Actors()[i]->p_r() == target->p_r())
						break;

				// implement dropping functionality.
				int z = 0;
				// check if an object exists at the monster's death location
				for (; z < dungeon()->Objects().size(); z++){
					if (dungeon()->Objects()[z]->p_c() == target->p_c() && dungeon()->Objects()[z]->p_r() == target->p_r()){
						break;
					}
				}
				// if no object exists, then that means z was incremented all the way to Objects.size
				if (z == dungeon()->Objects().size()){
					int ii = -1;
					if (target->name() == "the Dragon"){
						ii = randInt(0,4);
					}
					else if (target->name() == "the Snakewoman"){
						if (trueWithProbability(.3333))
							ii = 5;
					}

					else if (target->name() == "the Goblin"){
						if (trueWithProbability(.33333))
							ii = randInt(5,6);
					}
					else if (target->name() == "the Bogeyman"){
						if (trueWithProbability(.1))
							ii = 6;
					}

					int cc = target->p_c();
					int rr = target->p_r();
					switch(ii){
					case 0:
						dungeon()->Objects().push_back(new scroll_of_teleportation(rr, cc));
						break;
					case 1:
						dungeon()->Objects().push_back(new scroll_of_enhance_dexterity(rr, cc));
						break;
					case 2:
						dungeon()->Objects().push_back(new scroll_of_enhance_health(rr, cc));
						break;
					case 3:
						dungeon()->Objects().push_back(new scroll_of_improve_armor(rr, cc));
						break;
					case 4:
						dungeon()->Objects().push_back(new scroll_of_raise_strength(rr, cc));
						break;
					case 5:
						dungeon()->Objects().push_back(new magic_fangs(rr, cc));
						break;
					case 6:
						dungeon()->Objects().push_back(new magic_axe(rr, cc));
						break;
					}
				}

				delete target;
				dungeon()->Actors().erase(dungeon()->Actors().begin() + i);
			}	
		}
		else if (equipped_weapon->name() == "magic fangs"){
			if(trueWithProbability(.2)){
				target->change_sleep(randInt(2,6));
				msg += " putting " + target->name() + " to sleep";
			}
		}

		msg+= ".\n";
		return msg;
	}

	msg += "misses. \n";
	return msg;
}

// this function is a helper function for attack and increases a character's sleep time
// if it has been just hit with another magic fang such that the new sleep time is 
// greater than the time remaining.
int Actor::change_sleep(int n){
	if (n == -1 && sleep > 0)
		sleep--;
	else if (n > sleep && n > 0)
		sleep = n;
	return sleep;
}