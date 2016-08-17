// Game.cpp
#include <iostream>
#include "Actor.h"
#include "Game.h"
#include "utilities.h"
#include "Player.h"
#include "Dungeon.h"
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::to_string;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
	level = 0;
	Goblin_Smell_distance = goblinSmellDistance;
	p = new Player(nullptr, 1, 1);
	d = new Dungeon(this, level, p);
	p->set_dungeon(d);
	p->add_to_inventory(new short_sword);
}

// this is a function used by Game to decide which monster is closer to the Player.
bool a_is_closer_than_b (Actor* a, Actor* b);


void Game::play()
{
	cout << "Press q to exit game." << endl;

	string msg = "Dungeon Level: " + to_string(level);
	msg = msg + ", Hit points: " + to_string(p->hp()) + ", Armor: " + to_string(p->arm()) +
		", Strength: " + to_string(p->str()) +", Dexterity: " + to_string(p->dext()) + "\n"; 

	bool won_game = false;
	bool next_level = false;

	while (true){

		if (next_level){
			msg = "Dungeon Level: " + to_string(level) + ", Hit points: " + to_string(p->hp()) + ", Armor: " + to_string(p->arm()) +
			", Strength: " + to_string(p->str()) +", Dexterity: " + to_string(p->dext()) + "\n\n"; 
			next_level = false;
		}

		d->display(msg);

		if (p->hp() <= 0 || won_game){
			msg += "\n hp: " + to_string(p->hp());
			cout << msg;
			break;
		}

		msg = "Dungeon Level: " + to_string(level) + ", Hit points: " + to_string(p->hp()) + ", Armor: " + to_string(p->arm()) +
			", Strength: " + to_string(p->str()) +", Dexterity: " + to_string(p->dext()) + "\n\n"; 

		char instruction = getCharacter();

		// this string will be used to later check if we obtained the golden idol.
		std::string picked_up_message = ""; 

		// Check if the player is asleep. If so, don't take any input from Player and decrement sleep counter.
		if (p->isAsleep() > 0){
			p->change_sleep(-1);
		}
		
		// If the player is not asleep, then interpret the player's command.
		// Note that if a player attempts to move into a space occupied by some actor,
		// the player attacks that actor!
		else {
			switch(instruction){
			case 'j': 
				msg+= p->move(0);
				break;
			case 'l':
				msg+=p->move(1);
				break;
			case 'k':
				msg+=p->move(2);
				break;
			case 'h':
				 msg+=p->move(3);
				break;
			case 'q': return;
				break;
			case 'i':
			case 'w':
			case 'r':
				msg = p->view_inventory(instruction);
				break;
			case 'g':
				picked_up_message = p->pickup_object();
				if (picked_up_message == "You pick up the golden idol \nCongratulations, you won! \n")
					won_game = true;
				msg += picked_up_message;
				break;
			case 'c':
				p->change_max_hp(50-p->max_hp());
				p->change_hp_by(50-p->hp());
				p->change_str_by(9-p->str());
				// message must be reset because stats have changed!
				msg = "Dungeon Level: " + to_string(level) + ", Hit points: " + to_string(p->hp()) + ", Armor: " + to_string(p->arm()) +
			", Strength: " + to_string(p->str()) +", Dexterity: " + to_string(p->dext()) + "\n\n"; 

				break;

			case '>':
				next_level = p->pick_stairs();
				break;
			default: ;
			}
		}

		// needed to prevent monsters from attacking even after Player has taken the stairs!
		if(!next_level){

			// We need a way to record if the move was a failure. This may be misleading because
			// a move may have failed because when a particular monster was called, it was being 
			// blocked by another monster that had not yet attempted a move. Thus, it is possible
			// that even though initially this monster was unable to move, at the end of the turn,
			// the blocking monster may have moved out of the way; this means then that a monster
			// that had failed an earlier move should try again in the same turn to see if it is
			// now unblocked.
			// we record this by vector<int> failed_moved
			vector<int> failed_move;

			// We will make an actor move before actors that are further from the Player than it.
			vector<Actor*> traverse_order;

			for (int i = 0; i <d->Actors().size(); i++){
				traverse_order.push_back(d->Actors()[i]);
			}

			sort(traverse_order.begin(), traverse_order.end(), a_is_closer_than_b);

			for(int i = 0; i < d->Actors().size(); i++)
			{
				string move_returned = (traverse_order[i])->move(d->player());
					if(move_returned == "NO MOVE" ){
							failed_move.push_back(i);
					}
					else msg += move_returned;
			}

			int prev_vector_size;
			do{
				prev_vector_size = failed_move.size();
				vector<int> failed_again;
				for (int i = 0; i < failed_move.size(); i++){
					string move_returned = (traverse_order[failed_move[i]])->move(d->player());
					if(move_returned== "NO MOVE" )
						failed_again.push_back(failed_move[i]);
					else msg+= move_returned;
				}
				failed_move = failed_again;
			}while(failed_move.size() < prev_vector_size);
				// if in a previous iteration of this loop, we were not able to make
				// any additional moves whatsoever, that means that all of the failed
				// moves are because the monsters are stuck.
		}
	}
}

bool a_is_closer_than_b (Actor* a, Actor* b){

	Player* p = a->dungeon()->player();

	int a_distance = abs(a->p_c() - p->p_c()) + abs(a->p_r() - p->p_r());
	int b_distance = abs(b->p_c() - p->p_c()) + abs(b->p_r() - p->p_r());

	return a_distance < b_distance;
}


void Game::next_level(){
	//delete d;
	level++;
	Dungeon* temp = d;
	d = new Dungeon(this, level, p);
	p->set_dungeon(d);
	delete temp;
}