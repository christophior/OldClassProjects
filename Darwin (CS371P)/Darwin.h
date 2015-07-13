#ifndef DARWIN_H
#define DARWIN_H

#include <iostream>
#include <ostream>
#include <cctype>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::min;
using std::max;
using std::ostream;
using std::cout;
using std::endl;

enum direction_t {
	west = 0,
	north = 1,
	east = 2,
	south = 3,
	nulldirection
};

enum instruction_t {
	hop,
	left,
	right,
	infect,
	if_empty,
	if_wall,
	if_random,
	if_enemy,
	go
};

string directionString(direction_t);
class Creature;
class Board;

struct Instruction {
	instruction_t _instruction;
	int _n;
	Instruction(const instruction_t& instruction, int n)
		: _instruction(instruction), _n(n) 
	{}
};

class Species {
	private:
		char _name;
	public:
		vector<Instruction> _instructions;
		friend bool operator==(const Species& lhs, const Species& rhs) {
			return lhs._name == rhs._name;
		}
		Species(string name);
		Instruction getInstruction(int index);
		char name();
		void addInstruction(instruction_t instruction, int num = -1);
};

class Creature {
	private:
		Species  _species;
		int  _programCounter;
		int  _runCounter;
	public:
		
		friend bool operator==(const Creature& lhs, const Creature& rhs) {
			return lhs._species == rhs._species;
		}
		Creature(Species species, int programCounter = 0, int runCounter = 1);
		Creature infect(Creature& that);
		bool hasTurn(int runCounter);
		void takeTurn(Board& board, int x, int y);
		char name();
		bool sameSpecies(const Creature& that);
};

class Board {
	private:
	  Creature _defaultCreature;
	  direction_t _defaultDirection;
	  int _x;
	  int _y;
		vector< vector< pair< Creature, direction_t > > >  _board;
		// tells if space in given direction from x,y is free
		bool isValid(int x, int y);
		bool isFree(int x, int y);

	public:
		Board(Species defaultSpecies, direction_t defaultDirection, int x, int y);
		void addCreature(Creature creature, direction_t direction, int x, int y);
		// return true if control passed
		// return false o.w.
		bool doInstruction(const Instruction& instruction, int x1, int y1);
		void print(ostream& out);
		// running the board goes through every space and gives each creature a turn
		void run(int runCounter);
};

class Darwin {
	private:
		Board _board;
		int _runCounter;

	public:
		Darwin(int x, int y);
		void addCreature(Species species, direction_t direction, int x, int y);
		void run(ostream& out, int totalRuns, int intervalPrint = 1);
};

#endif