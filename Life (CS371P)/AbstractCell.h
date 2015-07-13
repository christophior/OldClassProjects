// ---------
// AbstractCell.h
// ---------

#ifndef AbstractCell_h
#define AbstractCell_h

#include "Handle.h"
#include <cassert>  // assert
#include <iostream> // cout, endl

using namespace std;

class AbstractCell{

    public:
        bool _isAlive;

    	AbstractCell(){
            _isAlive = false;
    	}

        AbstractCell(bool state){
            _isAlive = state;
        }

    	//given
    	//AbstractCell(const AbstractCell& that);

        //get the character symbol for the cell
        virtual char symbol() = 0;

        //progress a generation and return if alive
        virtual bool nextGen(int num) = 0;

        //clone a cell 
        virtual AbstractCell* clone() const = 0;
        
    	virtual ~AbstractCell(){ }

        //returns cells state
        bool isAlive(){ return _isAlive; }

        //kills the cell 
        void kill(){ _isAlive = false; }

        //brings the cell back to life
        virtual void respawn() { _isAlive = true; }

        virtual string name() = 0;

        virtual int age() = 0;

};


#endif // AbstractCell_h