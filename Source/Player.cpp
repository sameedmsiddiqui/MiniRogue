#include "Player.h"
#include "utilities.h"
#include "Actor.h"
#include "Dungeon.h"
#include <iostream>
#include <string>
#include "Scrolls.h"
#include "Weapons.h"

std::string Player::move(int direction){

	if(trueWithProbability(.1))
		if(hp() < Player::max_hp() )
			change_hp_by(1);
	change_sleep(-1);

	int r = p_r();
	int c = p_c();


	switch(direction){
	case 0:
		r = r+1;
		break;
	case 1:
		c = c+1;
		break;
	case 2:
		r = r-1;
		break;
	case 3:
		c = c-1;
		break;
	default:
		;
	}
	
	string msg = "";

	if(dungeon()->at_pos(r,c) == ' ' || dungeon()->at_pos(r,c) == ')' || dungeon()->at_pos(r,c) == '>' || dungeon()->at_pos(r,c) == '?' || dungeon()->at_pos(r,c) == '&' ){
		dungeon()->setMap(p_r(),p_c(), ' ');
		set_pos(r, c);
		dungeon()->setMap(p_r(),p_c(), 'P');
		return "";
	}
	else if(dungeon()->at_pos(r,c) == 'B' || dungeon()->at_pos(r,c) == 'D' || dungeon()->at_pos(r,c) == 'S' || dungeon()->at_pos(r,c) == 'G'){
		int i = 0;
		for (; i < dungeon()->Actors().size(); i++)
			if (dungeon()->Actors()[i]->p_c() == c && dungeon()->Actors()[i]->p_r() == r)
				break;
		msg = attack(dungeon()->Actors()[i]);
	}

	return msg;
}


std::string Player::view_inventory(char ch){
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	clearScreen();
	std::cout << "Inventory: " << std::endl;
	for (int i = 0; i <inventory.size(); i++){
		std::cout << " " << alphabet[i] << ". " << inventory[i]->name() << std::endl;
	}

	char instruction = getCharacter();

	std::string msg = "Dungeon Level: " + std::to_string(dungeon()->game()->lvl()) + ", Hit points: " + std::to_string(hp()) + ", Armor: " + std::to_string(arm()) +
			", Strength: " + std::to_string(str()) +", Dexterity: " + std::to_string(dext()) + "\n\n"; 

	if (ch == 'i')
		return msg;

	// Check if the user entered an alphabet that corresponds to an item in the inventory.
	bool valid = false;
	int index = -2;
	for (int i = 0; i < inventory.size(); i++){
		if (instruction == alphabet[i]){
			valid = true;
			index = i;
			break;
		}
	}

	if (valid){
		if (ch == 'w'){
			Weapon* wp = dynamic_cast<Weapon*>(inventory[index]);
			if (wp != nullptr){
				set_weapon(wp);
				msg = msg + "You are wielding " + wp->name() + "\n";
			}
			else{
				msg = msg + "You can't wield a " + inventory[index]->name() + "\n";
			}
		}
		else if (ch == 'r'){
			Scroll* sp = dynamic_cast<Scroll*>(inventory[index]);
			if (sp != nullptr){
				sp->read(this);
				inventory.erase(inventory.begin() + index);
				msg = "Dungeon Level: " + std::to_string(dungeon()->game()->lvl()) + ", Hit points: " + std::to_string(hp()) + ", Armor: " + std::to_string(arm()) +
					", Strength: " + std::to_string(str()) +", Dexterity: " + std::to_string(dext()) + "\n\n";
				msg = msg + "You read the scroll called " + sp->name() + "\n" + sp->read_message() + "\n";
			}
			else{
				msg = msg + "You can't read a " + inventory[index]->name() + "\n";
			}
		}
	}

	return msg;
}


std::string Player::pickup_object(){

	int i = 0;
	for (; i < dungeon()->Objects().size(); i++){
		if (dungeon()->Objects()[i]->p_c() == p_c() && dungeon()->Objects()[i]->p_r() == p_r()){
			break;
		}
	}

	if (dungeon()->Objects().size() == i)
			return "";

	staircase* stp = dynamic_cast<staircase*>(dungeon()->Objects()[i]);
	if (stp != nullptr){
		return "";
	}
	
	if (inventory.size() >= 26)
		return "Your knapsack is full; you can't pick that up. \n";
	
	inventory.push_back(dungeon()->Objects()[i]);
	dungeon()->Objects().erase(dungeon()->Objects().begin() + i);

	Weapon* wp = dynamic_cast<Weapon*>(inventory[inventory.size()-1]);
	if (wp != nullptr){
		return "You pick up " + inventory[inventory.size()-1]->name() +  "\n";
	}

	Scroll* sp = dynamic_cast<Scroll*>(inventory[inventory.size()-1]);
	if (sp != nullptr){
		return "You pick up a scroll called " + inventory[inventory.size()-1]->name() +  "\n";
	}

	// TO DO
	// this is where you can implement picking up the golden idol!
	return "You pick up the golden idol \nCongratulations, you won! \n";
}

bool Player::pick_stairs(){

	int i = 0;
	for (; i < dungeon()->Objects().size(); i++){
		if (dungeon()->Objects()[i]->p_c() == p_c() && dungeon()->Objects()[i]->p_r() == p_r()){
			break;
		}
	}

	if (dungeon()->Objects().size() == i)
			return false;

	staircase* stp = dynamic_cast<staircase*>(dungeon()->Objects()[i]);
	if (stp == nullptr){
		return false;
	}

	dungeon()->game()->next_level();
	return true;
}