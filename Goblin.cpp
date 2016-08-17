//int MAX_STEPS = 15;
#include "Dungeon.h"
#include <iostream>
#include <math.h>

// The overall design of this algorithm is as follows:
// Starting at the goblin's "real" position, the algorithm checks to see if the goblin can take a
// valid step in any direction such that that step will allow the goblin to reach the Player (within.
// fifteen steps). If there are multiple such valid steps that lead to the Player, the function
// returns the one with the shortest path length.


// declaration of a function defined later on in this code.
bool path(char grid[][70], int g_r, int g_c, int p_r, int p_c, int &next_move, int &path_length, int MAX_STEPS);

// The helper function through which the recursive call for a Goblin's path is executed.
// Returns the direction of the first step in the shortest path from (g_r, g_c) to (p_r, p_c)
// -1 = no path within 15 steps, otherwise next step is:
// 0 = down, 1 = right, 2 = up, 3 = left 
int Optimal_move(Dungeon* d, int g_r, int g_c, int p_r, int p_c, int MAX_STEPS){

	// Create an editable copy of the game grid. The recursive call path
	// will then modify this copy in determining the optimal move.
	char editable_grid[18][70]; 
	for (int i = 0; i < 18; i++)
		for (int j = 0; j <70; j++)
			editable_grid[i][j] = d->at_pos(i,j);

	int next_move, path_length = 0;


	path(editable_grid, g_r, g_c, p_r, p_c, next_move, path_length, MAX_STEPS );

	return next_move;
}

bool path(char grid[][70], int g_r, int g_c, int p_r, int p_c, int &next_move, int &path_length, int MAX_STEPS){


	// If the path length is 0, we need to check for two things: (1) If another monster is next to the player, 
	// the monster is essentially an obstacle for the goblin because that monster will always continue to be
	// next to the player. Thus we have to treat that monster as an obstacle.
	//  e.g. in the following situation:
	//
	//                          G@SG
	//                           G  
	//
	//		we want the rightmost goblin's next move to be:
	//
	//							   G
	//                          G@S
	//                           G                      
	// 
	//		so that it ends up like this:
	// 
	//							 G  
	//                          G@S
	//                           G     
	// 
	// (2) the goblin's recursive formula does not normally treat snakes and other actors as pure obstacles, because 
	//		they are not: they can move. However, this poses a problem if the goblin is currently next to another 
	//		monster: sometimes the shortest path to the player is *through* that monster, but obviously such a move
	//		cannot be made. In such an instance we must treat that monster as an obstacle.
	if (path_length == 0){ 
		
		// first we check to see if the Player is in a corridor or at the entrance of a corridor. If it is, we know
		// that there is no way for a Goblin to go around another goblin while in a corridor, so we never treat a 
		// monster monster that is next to a player and in/around a corridor as an obstacle. It should be noted that
		// this is necessary because a monster is ONLY treated as an obstacle if it is next to the goblin calling this
		// function or if it is next to the player.
		// this variable "remembers" if we're preventing this functionality.
		bool go_around = true;

		if (grid[p_r+1][p_c] == '#' && grid[p_r-1][p_c] == '#') // Player is in a corridor
			go_around = false;
		else if (grid[p_r+1][p_c+1] == '#' && grid[p_r-1][p_c+1] == '#' && p_c < g_r)
			// player is to the immediate left of the corridor, and the goblin is either
			// in the corridor or outside of the corridor's left exit.
			go_around = false;
		else if (grid[p_r+1][p_c-1] == '#' && grid[p_r-1][p_c-1] == '#' && p_c > g_r)
			// player is to the immediate left of the corridor, and the goblin is either
			// in the corridor or outside of the corridor's left exit.
			go_around = false;
		
		if (go_around){
			int num_match = 0;
			if (grid[p_r+1][p_c] == 'g' || grid[p_r+1][p_c] == 'G' || grid[p_r+1][p_c] == 'B' || grid[p_r+1][p_c] == 'S'){
				// The following code checks if the goblin next to the player happens to be next to the corridor. If so, we also don't
				// implement the go_around feature, because we don't want a wall to obstruct the openning of a corridor.
				if (!(grid[p_r][p_c+1] == '#' && grid[p_r+2][p_c+1] == '#' || grid[p_r][p_c-1] == '#' && grid[p_r+2][p_c-1] == '#') ){
					grid[p_r+1][p_c] = '#';
					num_match++;
				}
			}
			if (grid[p_r][p_c+1] == 'g' || grid[p_r][p_c+1] == 'G' || grid[p_r][p_c+1] == 'B' || grid[p_r][p_c+1] == 'S'){
				if (!(grid[p_r-1][p_c+2] == '#' && grid[p_r+1][p_c+2] == '#' || grid[p_r-1][p_c] == '#' && grid[p_r+1][p_c] == '#') ){
					grid[p_r][p_c+1] = '#';
					num_match++;
				}
			}
			if (grid[p_r-1][p_c] == 'g' || grid[p_r-1][p_c] == 'G' || grid[p_r-1][p_c] == 'B' || grid[p_r-1][p_c] == 'S'){
				if (!(grid[p_r-2][p_c+1] == '#' && grid[p_r][p_c+1] == '#' || grid[p_r-2][p_c-1] == '#' && grid[p_r][p_c-1] == '#') ){
					grid[p_r-1][p_c] = '#';
					num_match++;
				}
			}
			if (grid[p_r][p_c-1] == 'g' || grid[p_r][p_c-1] == 'G' || grid[p_r][p_c-1] == 'B' || grid[p_r][p_c-1] == 'S'){
				if (!(grid[p_r-1][p_c] == '#' && grid[p_r+1][p_c] == '#' || grid[p_r-1][p_c-2] == '#' && grid[p_r+1][p_c-2] == '#') ){
					grid[p_r][p_c-1] = '#';
					num_match++;
				}
			}

			// if the Player is being blocked on all four sides, a fifth goblin then tracks the player by 
			// targetting the goblin next to the player in the shortest path to the player.
			if (num_match == 4){
				path_length++;
				int path_rp1 = abs(p_c - g_c) + abs(p_r+1 - g_r);
				int path_rn1 = abs(p_c - g_c) + abs(p_r-1 - g_r);
				int path_cp1 = abs(p_c+1 - g_c) + abs(p_r - g_r);
				int path_cn1 = abs(p_c-1 - g_c) + abs(p_r - g_r);

				int lowest = 0;
				// which records which of the four blocked paths to the goblin is shortest
				int which = 0;
				if (path_rp1 < path_rn1){
					lowest = path_rp1;
					int which = 1;
				}
				else lowest = path_rn1;

				if (lowest > path_cp1){
					int which = 2;
					lowest = path_cp1;
				}
				if (lowest > path_cn1){
					int which = 3; 
				}

				switch(which){
				case 0:
					p_r--;
					break;
				case 1:
					p_r++;
					break;
				case 2:
					p_c++;
					break;
				case 3:
					p_c--;
					break;
				}
			}

			// check if there is a monster directly next to the goblin, in which case
			// that monster is treated as an obstacle;

			if (grid[g_r][g_c+1] == 'G' || grid[g_r][g_c+1] == 'g' || grid[g_r][g_c+1] == 'S' || grid[g_r][g_c+1] == 'B' || grid[g_r][g_c+1] == 'D')
				grid[g_r][g_c+1] = '#';
			if (grid[g_r][g_c-1] == 'G' || grid[g_r][g_c-1] == 'g' || grid[g_r][g_c-1] == 'S' || grid[g_r][g_c-1] == 'B' || grid[g_r][g_c-1] == 'D')
				grid[g_r][g_c-1] = '#';
			if (grid[g_r-1][g_c] == 'G' || grid[g_r-1][g_c] == 'g' || grid[g_r-1][g_c] == 'S' || grid[g_r-1][g_c] == 'B' || grid[g_r-1][g_c] == 'D')
				grid[g_r-1][g_c] = '#';
			if (grid[g_r+1][g_c] == 'G' || grid[g_r+1][g_c] == 'g' || grid[g_r+1][g_c] == 'S' || grid[g_r+1][g_c] == 'B' || grid[g_r+1][g_c] == 'D')
				grid[g_r+1][g_c] = '#';
		}
	}
	path_length++;	// increment the length of the path from the goblin's initial position to the coordinate of the current recursive call.

	int temp_length = path_length;		// Needed because we will have multiple recursive calls in this function, and each call needs
										// to be inputted the same initial path length.

	if (path_length > MAX_STEPS)
		return false;

	// Check if from the current position in this recursive call you can directly reach 
	// the player after one step. If so, end this recursive branch.
	if (g_r + 1 == p_r && g_c == p_c){
		next_move = -1;
		return true;
	}
	if ( g_r == p_r && g_c + 1 == p_c){
		next_move = -1;
		return true;
	}
	if (g_r -1 == p_r && g_c == p_c){
		next_move = -1;
		return true;
	}
	if (g_r == p_r && g_c -1 == p_c){
		next_move = -1;
		return true;
	}


	// Each traversable grid-location should have, once traversed, a numberical value indicating the 
	// length of the shortest path that has thusfar through all of the other recursive calls led 
	// to this grid locaiton. Only call new recursive implementations of this funciton if the current path
	// has a shorter path length to that point than the previous shortest path
	if (grid[g_r][g_c] == 'g' || grid[g_r][g_c] == 'G' || grid[g_r][g_c] == 'B' || grid[g_r][g_c] == 'S' || grid[g_r][g_c] == ' ' || grid[g_r][g_c] == ')' || grid[g_r][g_c] == '>' || grid[g_r][g_c] == '&' || grid[g_r][g_c] == '?' || grid[g_r][g_c] < MAX_STEPS+1 && grid[g_r][g_c] > path_length)
		grid[g_r][g_c] = path_length;

	// Set this to greater than the possible steps, so if we get a path of MAX_STEPS, that path will be
	// less than min_path_length = MAX_STEPS+1 
	int min_path_length = MAX_STEPS+1;

	next_move = -1;				// This represents the direction of the first step in 
								// the shortest path from (g_r, g_c) to (p_r, p_c)
								// -1 = no path within 15 steps, otherwise next step is:
								// 0 = down, 1 = right, 2 = up, 3 = left 
	
	int dummy_next_move = -1; // needed to feed into recursive calls to grid

	// The recursive calls should only be made if a particular adjacent step is both not an obstacle and if the current path length
	// is shorter than the previously shortest path length that has already traversed it.
	if (grid[g_r+1][g_c] == 'g' || grid[g_r+1][g_c] == 'G' || grid[g_r+1][g_c] == 'B' || grid[g_r+1][g_c] == 'S' || grid[g_r+1][g_c] == ' ' || grid[g_r+1][g_c] == ')' || grid[g_r+1][g_c] == '>' || grid[g_r+1][g_c] == '&' || grid[g_r+1][g_c] == '?' || grid[g_r+1][g_c] < MAX_STEPS+1 && grid[g_r+1][g_c] > path_length){
		if (path(grid, g_r + 1, g_c,  p_r,  p_c, dummy_next_move, temp_length, MAX_STEPS)){
			// if there exists a path from that step to the Player, then we must see if the length of the path is shorter
			// than the length of the paths from all of our other possible steps from this point.
			if (min_path_length > temp_length){
				min_path_length = temp_length;
				next_move = 0;
			}
		}
		temp_length = path_length;
	}
	if (grid[g_r][g_c+1] == 'g' || grid[g_r][g_c+1] == 'G' || grid[g_r][g_c+1] == 'B' || grid[g_r][g_c+1] == 'S' || grid[g_r][g_c+1] == ' ' || grid[g_r][g_c+1] == ')' || grid[g_r][g_c+1] == '>' || grid[g_r][g_c+1] == '&' || grid[g_r][g_c+1] == '?' || grid[g_r][g_c+1] < MAX_STEPS+1 && grid[g_r][g_c+1] > path_length){
		if (path(grid, g_r, g_c + 1,  p_r,  p_c, dummy_next_move, temp_length, MAX_STEPS)){
			if (min_path_length > temp_length){
				min_path_length = temp_length;
				next_move = 1;
			}
		}
		temp_length = path_length;
	}
	if (grid[g_r-1][g_c] == 'g' || grid[g_r-1][g_c] == 'G' || grid[g_r-1][g_c] == 'B' || grid[g_r-1][g_c] == 'S' || grid[g_r-1][g_c] == ' ' || grid[g_r-1][g_c] == ')' || grid[g_r-1][g_c] == '>' || grid[g_r-1][g_c] == '&' || grid[g_r-1][g_c] == '?' || grid[g_r-1][g_c] < MAX_STEPS+1 && grid[g_r-1][g_c] > path_length){
		if (path(grid, g_r-1, g_c,  p_r,  p_c, dummy_next_move, temp_length, MAX_STEPS)){
			if (min_path_length > temp_length){
				min_path_length = temp_length;
				next_move = 2;
			}
		}
		temp_length = path_length;
	}
	if (grid[g_r][g_c-1] == 'g' || grid[g_r][g_c-1] == 'G' || grid[g_r][g_c-1] == 'B' || grid[g_r][g_c-1] == 'S' || grid[g_r][g_c-1] == ' ' || grid[g_r][g_c-1] == ')' || grid[g_r][g_c-1] == '>' || grid[g_r][g_c-1] == '&' || grid[g_r][g_c-1] == '?' || grid[g_r][g_c-1] < MAX_STEPS+1 && grid[g_r][g_c-1] > path_length){
		if (path(grid, g_r, g_c - 1,  p_r,  p_c, dummy_next_move, temp_length, MAX_STEPS)){
			if (min_path_length > temp_length){
				min_path_length = temp_length;
				next_move = 3;
			}
		}
	}

	// path_length is a pass-by-parameter variable, so we want to change it to the minimum path length
	path_length = min_path_length;
	if (path_length <= MAX_STEPS)
		return true;

	return false;
}
