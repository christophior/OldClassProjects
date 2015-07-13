// ---------
// Fredkin.h
// ---------

#ifndef FredkinCell_h
#define FredkinCell_h

#include "Handle.h"
#include <cassert>  // assert
#include <iostream> // cout, endl
#include "AbstractCell.h"

using namespace std;

class FredkinCell : public AbstractCell {
	public:
		const string _name;
		int _age;
		char _symbol;

		FredkinCell() : AbstractCell(false), _name("FredkinCell") { 
			_age = 0;
			_symbol = '-';
		}

		FredkinCell(bool state) : AbstractCell(state) { 
			_age = 0;
			_symbol = state ? '0' : '-';
		}

		char symbol(){ return _symbol; }

		bool nextGen(int num){
			if ( !AbstractCell::isAlive() && (num == 3 || num == 1) ){
				AbstractCell::respawn();
				_symbol = (_age < 10) ? '0' + _age : '+';
				return true;
			} else if (AbstractCell::isAlive() && (num == 0 || num == 2 || num == 4) ){
				AbstractCell::kill();
				_symbol = '-';
				return false;
			} else if (AbstractCell::isAlive()){
				++_age;
				_symbol = (_age < 10) ? '0' + _age : '+';
			}
			return AbstractCell::isAlive();
		}

		virtual FredkinCell* clone() const {
			return new FredkinCell(*this);
		}

		void respawn(){
			AbstractCell::respawn();
			_symbol = (_age < 10) ? '0' + _age : '+';
		}

		int age(){
			return _age;
		}

		string name(){
			return _name;
		}

};

#endif // FredkinCell_h
