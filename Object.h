#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object{
public:
	Object(std::string n, char d, int r, int c) : o_name(n), disp(d), p_r_(r), p_c_(c) {;}
	virtual ~Object(){;}
	std::string name(){return o_name;}
	//what character is displayed by this object on the grid
	char display() const {return disp;}
	// Note: if the object is carried by an Actor, it's coordinates will be -1,-1
	int p_r() const {return p_r_;}
	int p_c() const {return p_c_;}
private:
	std::string o_name;
	char disp;
	int p_r_;
	int p_c_;

};


// The golden idol and the staircase are included in this file because these two classes will ALWAYS
// be present in any modification of the game: some element (you can call it something other than
// "golden idol") will always be needed to call the end of the game, and you will always need stairs
// to go across dungeon levels. 

class golden_idol : public Object{
public:
	golden_idol(int r, int c) : Object("golden idol", '&', r, c){;}
};

class staircase : public Object{
public:
	staircase(int r, int c) : Object("staircase", '>', r, c){;}
};

#endif//OBJECT_H