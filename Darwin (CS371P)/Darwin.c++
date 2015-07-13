#include <cstdlib>
#include <cctype>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include "Darwin.h"

using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::min;
using std::max;
using std::ostream;
using std::cout;
using std::endl;

#define INSTR_DBG 0
/**
 *	takes in direction_t and outputs the string representation
 *	@param direction_t d
 *	@return string
 */
string directionString(direction_t d) {
	switch(d) {
		case west:
			return "west";
			break;
		case north:
			return "north";
			break;
		case east:
			return "east";
			break;
		case south:
			return "south";
			break;
		case nulldirection:
		default:
			return "ERROR";
			break;
	}
}

// Species class

/**
 *	constructs a species by taking in it's name and storing the first 
 *	letter of the name (lowercased) 
 *	@param string name
 */
Species::Species(string name) {
	_name = tolower(name[0]);
}

/**
 *	returns a species instruction at a given index of it's instruction list
 *	@param int index
 *	@return Instruction
 */
Instruction Species::getInstruction(int index) {
	return _instructions[index];
}

/**
 *	returns char representation for a species
 *	@return char
 */
char Species::name(){
	return _name;
}

/**
 *	add an instruction along with the number it's associated with to 
 *	a species instruction list
 *	@param instruction_t instruction
 *	@param int num
 */
void Species::addInstruction(instruction_t instruction, int num){
	Instruction i(instruction, num);
	_instructions.push_back(i);
}


// Creature Class

/**
 *	construct a Creature of a certain species with a set program and run counter
 *	@param Species species
 *	@param int programCounter
 *	@param int runCounter
 */
Creature::Creature(Species species, int programCounter, int runCounter)
	: _species(species), _programCounter(programCounter), _runCounter(runCounter)
{ }

/**
 *	takes in a Creature and changes the input Creature's species and program counter
 *	@param Creature& that
 *	@return Creature
 */
Creature Creature::infect(Creature& that) {
	that._species = _species;
	that._programCounter = 0;
	return that;
}

/**
 *	returns whether or not a creature can move for a given turn on the board
 *	@param int runCounter
 *	@return bool
 */
bool Creature::hasTurn(int runCounter) {
	return runCounter == _runCounter;
}

/**
 *	a creature at a certain spot on the board performs a move
 *	@param Board& board
 *	@param int x
 *	@param int y
 */
void Creature::takeTurn(Board& board, int x, int y) {
	Instruction instruction = _species.getInstruction(_programCounter);
	if (instruction._n < 0)
		++_runCounter;
	++_programCounter;
	bool jump = board.doInstruction(instruction, x, y);
	if (jump)
		_programCounter = instruction._n;
	while(instruction._n >= 0) {
		instruction = _species.getInstruction(_programCounter);
		if (instruction._n < 0)
			++_runCounter;
		++_programCounter;
		jump = board.doInstruction(instruction, x, y);
		if (jump)
			_programCounter = instruction._n;
	}
}

/**
 *	returns a Creature's Species' character representation
 *	@return char
 */
char Creature::name(){
	return _species.name();
}

/**
 *	returns whether or not two creatures are of the same species
 *	@param const Creature& that
 *	@return bool
 */
bool Creature::sameSpecies(const Creature& that) {
	return _species == that._species;
}


// Board Class

/**
 *	creates a board with dimensions x, y and prefills the board 
 *	with defaultCreatures(nullCreatures)  
 *	@param Species defaultSpecies
 *	@param direction_t defaultDirection
 *	@param int x
 *	@param int y
 */
Board::Board(Species defaultSpecies, direction_t defaultDirection, int x, int y)
	: _defaultCreature(defaultSpecies, -1, -1), _defaultDirection(defaultDirection), _x(x), _y(y) {
	for (int i = 0; i < _x; ++i) {
		vector< pair <Creature, direction_t > > row;
		for (int j = 0; j < _y; ++j) {
			row.push_back(make_pair(_defaultCreature, _defaultDirection));
		}
		_board.push_back(row);
	}
}

/**
 *	adds a creature that is facing a certain direction on the board with position x,
 *	@param Creature creature
 *	@param direction_t direction
 *	@param int x
 *	@param int y
 */
void Board::addCreature(Creature creature, direction_t direction, int x, int y) {
	_board[x][y] = make_pair(creature, direction);
}

/**
 *	tells if a control instruction has passed, otherwise returns false
 *	@param const Instruction& instruction
 *	@param int x1
 *	@param int y1
 *	@return bool
 */
bool Board::doInstruction(const Instruction& instruction, int x1, int y1) {
	bool ret;
	Creature& creature1 = _board[x1][y1].first;
	direction_t& direction1 = _board[x1][y1].second;
	int x2, y2;

	switch(direction1) {
		case west:
			x2 = x1;
			y2 = y1-1;
			break;
		case north:
			x2 = x1-1;
			y2 = y1;
			break;
		case east:
			x2 = x1;
			y2 = y1+1;
			break;
		case south:
			x2 = x1+1;
			y2 = y1;
			break;
		default:
			x2 = x1;
			y2 = y1;
			break;
	}

	// Creature& creature2 = (isValid(x2, y2))? _board[x2][y2].first : _defaultCreature;

	if (INSTR_DBG) cout << "creature at (" << x1 << "," << y1 << ")" << " ";
	switch (instruction._instruction) {
		// action cases
		case hop:
			if (isValid(x2, y2) && isFree(x2, y2)) {
				_board[x2][y2] = make_pair(creature1, direction1);
				_board[x1][y1] = make_pair(_defaultCreature, _defaultDirection);
				if (INSTR_DBG) cout << "successfully hops to (" << x2 << "," << y2 << ")." << endl;
			}
			else {
				if (INSTR_DBG) cout << "unsuccessfully hops to (" << x2 << "," << y2 << ")." << endl;
			}
			ret = false;
			break;
		case left:
			if (INSTR_DBG) cout << "turned left from " << directionString(direction1) << " to ";
			direction1 = static_cast<direction_t>((direction1 - 1 + 4) % 4); // add 4 here to make sure we aren't negative
			if (INSTR_DBG) cout << directionString(direction1) << endl;
			ret = false;
			break;
		case right:
			if (INSTR_DBG) cout << "turned right from " << directionString(direction1) << " to ";
			direction1 = static_cast<direction_t>((direction1 + 1) % 4);
			if (INSTR_DBG) cout << directionString(direction1) << endl;
			ret = false;
			break;
		case infect:
			if (isValid(x2, y2) && !isFree(x2, y2) && !creature1.sameSpecies(_board[x2][y2].first)) {
				_board[x2][y2] = make_pair(creature1.infect(_board[x2][y2].first), _board[x2][y2].second);
				if (INSTR_DBG) cout << "infected enemy at (" << x2 << "," << y2 << ")." << endl;
			}
			else {
				if (INSTR_DBG) cout << "did not infect enemy at (" << x2 << "," << y2 << ")." << endl;
			}
			ret = false;
			break;
		// control cases
		case if_empty:
			if (isValid(x2, y2) && isFree(x2, y2)) {
				ret = true;
				if (INSTR_DBG) cout << "found an empty space at (" << x2 << "," << y2 << ")." << endl;
			}
			else {
				ret = false;
				if (INSTR_DBG) cout << "did not find and empty space at (" << x2 << "," << y2 << ")." << endl;
			}
			break;
		case if_wall:
			if (!isValid(x2, y2)) {
				ret = true;
				if (INSTR_DBG) cout << "found a wall at (" << x2 << "," << y2 << ")." << endl;
			}
			else {
				ret = false;
				if (INSTR_DBG) cout << "did not find a wall at (" << x2 << "," << y2 << ")." << endl;
			}
			break;
		case if_random:
			{

			int r = rand();
			if (r % 2 == 1) {
				ret = true;
				if (INSTR_DBG) cout << "got odd random number " << r << "." << endl;
			}
			else {
				ret = false;
				if (INSTR_DBG) cout << "got even random number " << r << "." << endl;
			}

			}
			break;
		case if_enemy:
			if (isValid(x2, y2) && !isFree(x2, y2) && !creature1.sameSpecies(_board[x2][y2].first)) {
				ret = true;
				if (INSTR_DBG) cout << "found an enemy at (" << x2 << "," << y2 << ")." << endl;
			}
			else {
				ret = false;
				if (INSTR_DBG) cout << "did not find an enemy at (" << x2 << "," << y2 << ")." << endl;
			}
			break;
		case go:
			if (INSTR_DBG) cout << "did go." << endl;
			ret = true;
			break;
		default:
			ret = false;
			break;
	}
	return ret;
}

/**
 *	prints out the board to an output stream
 *	@param ostream& out
 */
void Board::print(ostream& out) {
	out << "  ";
	for (int j = 0; j < _y; ++j) {
		out << (j % 10);
	}
	out << endl;

	for (int i = 0; i < _x; ++i) {
		for (int j = 0; j < _y; ++j) {
			if (j == 0)
				out << (i % 10) << " ";
			out << _board[i][j].first.name();
		}
		out << endl;
	}
	out << endl;
}

/**
 *	runs the board through every space and gives each creature a turn
 *	@param int runCounter
 */
void Board::run(int runCounter) {
	for (int i = 0; i < _x; ++i) {
		for (int j = 0; j < _y; ++j) {
			Creature& c = _board[i][j].first;
			if(c.hasTurn(runCounter)) {
				c.takeTurn(*this, i, j);
			}
		}
	}
}

/**
 *	checks if a coordinate is valid on the board
 *	@param int x1
 *	@param int y1
 *	@return bool
 */
bool Board::isValid(int x, int y) {
	return x >= 0 && x < _x && y >= 0 && y < _y;
}

/**
 *	tells if a space in a certain direction from x, y is free
 *	@param int x
 *	@param int y
 *	@return bool
 */
bool Board::isFree(int x, int y) {
	return _board[x][y].first == _defaultCreature;
}


/**
 *	creatures a Darwin object which initializes the board and 
 *	keeps the board run count
 *	@param int x
 *	@param int y
 */
Darwin::Darwin(int x, int y) 
	: _board(Species("."), nulldirection, x, y), _runCounter(0)
{ }

/**
 *	gets a given species and creates a creature and adds it to the board
 *	@param Species species
 *	@param const direction_t direction
 *	@param int x
 *	@param int y
 */
void Darwin::addCreature(Species species, direction_t direction, int x, int y){
	Creature creature(species);
	_board.addCreature(creature, direction, x, y);
}

/**
 *	runs the Darwin program a certain number of times with the board being
 *	printed out at a specified interval
 *	@param ostream& out
 *	@param int totalRuns
 *	@param int intervalPrint
 */
void Darwin::run(ostream& out, int totalRuns, int intervalPrint){
	out << "Turn = " << _runCounter << "." << endl;
	_board.print(out);

	++_runCounter;
	while(_runCounter <= totalRuns){
		_board.run(_runCounter);

		if (!(_runCounter % intervalPrint)){
			out << "Turn = " << _runCounter << "." << endl;
			_board.print(out);
		}

		++_runCounter;
	}
}