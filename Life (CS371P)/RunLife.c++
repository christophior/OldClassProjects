// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------

/*
To run the program:
    % make RunLife
    % make run

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <fstream>

#include "Handle.h"
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include "Life.h"

using namespace std;

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ------------------
    // Conway Cell 109x69
    // ------------------
    int row, col;

    try {
        cout << "*** Life<ConwayCell> 109x69 ***" << endl << endl;

        fstream file("RunLifeConway.in");
        file >> row;
        file >> col;
        
        Life<ConwayCell> x(row, col, ConwayCell());

        for (int i = 0; i<row; ++i){
            for (int j = 0; j<col; ++j){
                char currentSymbol;
                file >> currentSymbol;
                if (currentSymbol == '*'){
                    x.respawn(i, j);
                }
            }
        }

        x.print();
        cout <<endl;
        for (int r = 1; r<10; ++r){
            x.run(1);
            x.print();
            cout<<endl;
        }
        x.run(274);
        x.print();
        cout<<endl;

        x.run(40);
        x.print();
        cout<<endl;

        x.run(2177);
        x.print();
        cout<<endl;

        /*
        read RunLifeConway.in // assume all Conway cells
        Simulate 283 moves.
        Print the first 10 grids (i.e. 0, 1, 2...9).
        Print the 283rd grid.
        Simulate 40 moves.
        Print the 323rd grid.
        Simulate 2177 moves.
        Print the 2500th grid.
        */

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {

        cout << "*** Life<FredkinCell> 20x20 ***" << endl;
        
        fstream file("RunLifeFredkin.in");
        file >> row;
        file >> col;
        
        Life<FredkinCell> x(row, col, FredkinCell());

        for (int i = 0; i<row; ++i){
            for (int j = 0; j<col; ++j){
                char currentSymbol;
                file >> currentSymbol;
                if (currentSymbol != '-'){
                    x.respawn(i, j);
                }
            }
        }

        x.print();
        cout <<endl;
        x.run(1);
        x.print();
        cout<<endl;
        x.run(1);
        x.print();
        cout<<endl;
        x.run(1);
        x.print();
        cout<<endl;
        x.run(1);
        x.print();
        cout<<endl;
        x.run(1);
        x.print();
        cout<<endl;

        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Simulate 5 moves.
        Print every grid (i.e. 0, 1, 2...5)
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<Cell> 20x20 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Simulate 5 moves.
        Print every grid (i.e. 0, 1, 2...5)
        */
        fstream file("RunLifeCell.in");
        file >> row;
        file >> col;
        
        Life<Cell> x(row, col, Cell(new FredkinCell()) );

        for (int i = 0; i<row; ++i){
            for (int j = 0; j<col; ++j){
                char currentSymbol;
                file >> currentSymbol;
                if (currentSymbol != '-'){
                    x.respawn(i, j);
                }
            }
        }

        x.print();
        cout<<endl;
        x.run(1);
        x.print();
        cout<<endl;
        x.run(1);
        x.print();
        cout<<endl;
        x.run(1);
        x.print();
        cout<<endl;
        x.run(1);
        x.print();
        cout<<endl;
        x.run(1);
        x.print();


    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}