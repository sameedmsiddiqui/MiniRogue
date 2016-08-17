#include "Dungeon.h"
#include "Player.h"
#include "Weapons.h"
#include "Scrolls.h"
#include "Monsters.h"
#include "my_utilities.h"
#include "utilities.h"
#include <iostream>
#include <string>

class Game;

// TO DO: CHANGE the number of monsters created at start of level!
//			right now, you commented the correct algorithm out and
//			replaced it with a constant!
// TO DO
// TO DO


Dungeon::Dungeon(Game* g, int l, Player* pp){

	gm = g;
	level = l;
	p = pp;

	//Fill the room with all # signs.
	for(int i = 0; i < 18; i++)
		for (int j = 0; j < 70; j++)
			grid[i][j] = '#';

	////////////////////////////////////////////
	//////////Create the dungeon grid///////////
	////////////////////////////////////////////
	// done by subdividing each whole gride
	// into 5 sections, each of which has a
	// randomly sized room linked by a corridor
	////////////////////////////////////////////

	// Create a set of room coordinates containing both the 
	// top-left and bottom-right coordinates of the rooms.
	// e.g. (rm_tl_r[0], rm_tl_c[0]) constitute
	// the first room's top left corner and
	// (rm_br_r[1], rm_br_c[1]) are bottom right
	int rm_tl_r[10] = {0,0,0,0,0,0,0,0,0,0};
	int rm_tl_c[10] = {0,0,0,0,0,0,0,0,0,0};
	int rm_br_r[10] = {0,0,0,0,0,0,0,0,0,0};
	int rm_br_c[10] = {0,0,0,0,0,0,0,0,0,0};

	for (int n = 1; n <6; n++){
			int rooms_in_section = randInt(2)+1;
			//if (rooms_in_section == 1){
			if (rooms_in_section != 81){
				int height = randInt(3,8);
				int top_r = randInt(9 - height/2 -3, 9 - height/2 +3);
				if (n != 1){
					// ensure that two adjacent rooms can always be connected by a corridor!
					while (rm_tl_r[2*(n-2)] > top_r + height -1 || rm_br_r[2*(n-2)] < top_r)
						top_r = randInt(9 - height/2 -3, 9 - height/2 +3);
				}
				int width = randInt(7,12);
				int leeway = 12 - width; // this is the amount of positions
							// to the right of the start of the section
							// that the room can be placed.
				int smallest_c = 3+13*(n-1); // this is the smallest c in the section
				int leftmost_c = randInt(smallest_c, smallest_c + leeway);
				for (int r = top_r; r < top_r + height; r++)
					for (int c = leftmost_c; c < leftmost_c+width; c++)
						grid[r][c] = ' ';
				rm_tl_r[2*(n-1)] = top_r;
				rm_br_r[2*(n-1)] = top_r + height -1;
				rm_tl_c[2*(n-1)] = leftmost_c;
				rm_br_c[2*(n-1)] = leftmost_c +width -1;

				//connect two adjacent rooms with a corridor
				if (n != 1){

					int r1 = 0;
					while (r1 < rm_tl_r[2*(n-2)] || r1 > rm_br_r[2*(n-2)])
						r1 = randInt(rm_tl_r[2*(n-1)], rm_br_r[2*(n-1)]);

					for (int c = rm_br_c[2*(n-2)]; c < rm_tl_c[2*(n-1)]; c++)
						grid[r1][c] = ' ';
				}


				//////CAUTION////////////
				// HIGHLY EXPERIMENTAL///
				/////////////////////////
				///CAUSES INFINITE LOOP//
				//EVERY ~5 ATTEMPTS!!!///
				/////////////////////////
				//purpose:
				//to add a verticle antechamber
				///////////////////////////////
				//if (rm_tl_r[2*(n-1)] > 9){
				//	int height_rm_2 = randInt(3,6);
				//	int top_r_rm_2 = randInt(1, rm_tl_r[2*(n-1)] - (height_rm_2 + 1));
				//	int width_rm_2 = randInt(7,12);
				//	int leeway_rm_2 = 12 - width_rm_2;
				//	smallest_c = 3+13*(n-1);
				//	int leftmost_c_rm_2 = randInt(smallest_c, smallest_c + leeway_rm_2);
				//	while (rm_tl_c[2*(n-1)] > leftmost_c_rm_2 + width_rm_2 -1 || rm_br_c[2*(n-1)] + width - 1 < leftmost_c_rm_2)
				//		int leftmost_c_rm_2 = randInt(smallest_c, smallest_c + leeway_rm_2);

				//	for (int r = top_r_rm_2; r < top_r_rm_2 + height_rm_2; r++)
				//		for (int c = leftmost_c_rm_2; c < leftmost_c_rm_2+width_rm_2; c++)
				//			grid[r][c] = ' ';

				//	int c2 = 0;
				//	while (c2 < rm_tl_c[2*(n-1)] || c2 > rm_br_r[2*(n-1)] + width)
				//		c2 = randInt(leftmost_c_rm_2, leftmost_c_rm_2 +width_rm_2);

				//	for (int r2 = top_r_rm_2 + height_rm_2 -1 ; r2 < rm_tl_r[2*(n-1)]; r2++)
				//		grid[r2][c2] = ' ';

				//}

			}
		}

	

	// Make a copy of the overall layout/template
	// of the grid
	for (int i = 0; i < 18; i++)
		for (int j = 0; j < 70; j++)
			basic_grid[i][j] = grid[i][j];

	int c = 0, r = 0;

	// add the golden idol if level 4
	// else add a staircase to the next level
	if (l == 4){
		while ( grid[r][c] == '#'){
			r = randInt(1,17);
			c = randInt(1,69);
		}
		objects.push_back(new golden_idol(r, c));
	}
	else {
		while ( grid[r][c] == '#'){
			r = randInt(1,17);
			c = randInt(1,69);
		}
		objects.push_back(new staircase(r, c));
	}


	// place randInt(2,3) objects in a 
	// legal location on the grid
	for (int i = 0; i < randInt(2,3); i++){
	//for (int i = 0; i < 30; i++){
		bool can_place = false;
		while (!can_place){
			r = randInt(1,17);
			c = randInt(1,69);
			if (grid[r][c] == '#')
				continue;
			for (int i = 0; i < objects.size(); i++){
				if (objects[i]->p_r() == r && objects[i]->p_c() == c)
					break;
				if (i == objects.size() - 1)
					can_place = true;
			}
		}
		int object_placed = randInt(7);

		switch(object_placed){
		case 0:
			objects.push_back(new mace(r, c));
			break;
		case 1:
			objects.push_back(new short_sword(r, c));
			break;
		case 2:
			objects.push_back(new long_sword(r, c));
			break;
		case 3:
			objects.push_back(new scroll_of_enhance_dexterity(r, c));
			break;
		case 4:
			objects.push_back(new scroll_of_enhance_health(r, c));
			break;
		case 5:
			objects.push_back(new scroll_of_improve_armor(r, c));
			break;
		case 6:
			objects.push_back(new scroll_of_raise_strength(r, c));
			break;
		}
	}



	// Place Player on the grid
	while ( grid[r][c] == '#'){
		int r = randInt(1,17);
		int c = randInt(1,69);
	}
	p->set_pos(r,c);
	actors.push_back(p);

	// determine number of monsters, then 
	// place them as appropriate.
	int num_monsters = 2+ randInt(5*(l+1));

	for (int i = 0; i < num_monsters; i++){
		bool can_place = false;
		while (!can_place){
			r = randInt(1,17);
			c = randInt(1,69);
			if (grid[r][c] == '#')
				continue;
			for (int i = 0; i < actors.size(); i++){
				if (actors[i]->p_r() == r && actors[i]->p_c() == c)
					break;
				if (i == actors.size() - 1)
					can_place = true;
			}
		}
		int actor_placed = 0;
		if (l == 2)
			actor_placed = randInt(3);
		else if (l == 3)
			actor_placed = randInt(4);
		else
			actor_placed = randInt(2);

		switch(actor_placed){
		case 0:
			actors.push_back(new Snakewoman(this, r, c));
			break;
		case 1:
			actors.push_back(new Goblin(this, r, c));
			break;
		case 2:
			actors.push_back(new Bogeyman(this, r, c));
			break;
		case 3:
			actors.push_back(new Dragon(this, r, c));
			break;
		}
	}


}

void Dungeon::display(std::string msg){
	 //reset the grid to its original state
	for (int i = 0; i < 18; i++)
		for (int j = 0; j < 70; j++)
			grid[i][j] = basic_grid[i][j];


	for (int i = 0; i < objects.size(); i++)
		grid[objects[i]->p_r()][objects[i]->p_c()] = objects[i]->display();

	for (int i = 0; i < actors.size(); i++)
		grid[actors[i]->p_r()][actors[i]->p_c()] = actors[i]->display();

	clearScreen();
	for (int i = 0; i < 18; i++){
		for (int j = 0; j < 70; j++)
			std::cout << grid[i][j];
		std::cout << std::endl;
	}

	std::cout << msg;

}

Dungeon::~Dungeon(){
	for (int i = 1; i < actors.size(); i++)
		delete actors[i];
	for (int i = 0; i <objects.size(); i++)
		delete objects[i];
}