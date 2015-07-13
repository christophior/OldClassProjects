// ---------
// Cell.h
// ---------

#ifndef Cell_h
#define Cell_h

#include "Handle.h"
#include <cassert>  // assert
#include <iostream> // cout, endl
#include "AbstractCell.h"
#include "FredkinCell.h"
#include "ConwayCell.h"

using namespace std;

struct Cell : public Handle<AbstractCell>{

	Cell(AbstractCell* p) : Handle<AbstractCell>(p){ }
	Cell (const Cell& that) : Handle<AbstractCell> (that) {}

	char symbol(){
		return get()->symbol();
	}

	bool nextGen(int num){
		if (get()->nextGen(num)){
			if (symbol() == '2'){
				delete _p;
      			_p = new ConwayCell(true);
			}
		}
		return isAlive();
		/*if ( !isAlive() && (num == 3 || num == 1) ){
			respawn();
			get()._symbol = (age() < 10) ? '0' + age() : '+';
			return true;
		} else if (isAlive() && (num == 0 || num == 2 || num == 4) ){
			kill();
			get()._symbol = '-';
			return false;
		} else if (isAlive()){
			++(get()._age);
			get()._symbol = (age() < 10) ? '0' + age() : '+';
		}
		return isAlive();	*/
		
		//return get()->nextGen(num);

	}

	bool isAlive(){
		return get()->isAlive(); 
	}

	void kill(){
		return get()->kill();
	}

	void respawn(){
		return get()->respawn();
	}

	string name(){
		return get()->name();
	}

	int age(){
		return get()->age();
	}

/*
	----provided----
	Cell(const Cell& that);
	~Cell();
	Cell& operator = (const Cell& that);
*/

};

#endif // Cell_h