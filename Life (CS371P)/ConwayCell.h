// ---------
// ConwayCell.h
// ---------

#ifndef ConwayCell_h
#define ConwayCell_h

#include "Handle.h"
#include <cassert>  // assert
#include <iostream> // cout, endl
#include "AbstractCell.h"

using namespace std;

class ConwayCell : public AbstractCell {
	public:
		string _name;
		char _symbol;
		int _age;

		ConwayCell() : AbstractCell(), _name("ConwayCell"), _age(-1) {
			_symbol = '.'; 
		}

		ConwayCell(bool state) : AbstractCell(state){
			_symbol = state ? '*' : '.';
		}

		char symbol() { return _symbol; }

		bool nextGen(int num){
			if ( !AbstractCell::isAlive() && num == 3){
				AbstractCell::respawn();
				_symbol = '*';
				return true;
			} else if (AbstractCell::isAlive() && (num < 2 || num > 3)){
				AbstractCell::kill();
				_symbol = '.';
				return false;
			}
			return AbstractCell::isAlive();
		}

		virtual ConwayCell* clone() const {
			return new ConwayCell(*this);
		}

		void respawn(){
			AbstractCell::respawn();
			_symbol = '*';
		}

		string name(){
			return _name;
		}

		int age(){
			return _age;
		}
};

#endif // ConwayCell_h
