// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2013
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin > RunDarwin.out

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
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"
// ----
// main
// ----

int main () {
    using std::cout;
    using std::ios_base;
    using std::invalid_argument;
    using std::out_of_range;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O




    // ----
    // food
    // ----
    Species food("food");
    /*
     0: left
     1: go 0
    */
    food.addInstruction(left);
    food.addInstruction(go, 0);

    // ------
    // hopper
    // ------
    Species hopper("hopper");
    /*
     0: hop
     1: go 0
    */
    hopper.addInstruction(hop);
    hopper.addInstruction(go, 0);

    // -----
    // rover
    // -----
    Species rover("rover");
    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
    rover.addInstruction(if_enemy, 9);
    rover.addInstruction(if_empty, 7);
    rover.addInstruction(if_random, 5);
    rover.addInstruction(left);
    rover.addInstruction(go, 0);
    rover.addInstruction(right);
    rover.addInstruction(go, 0);
    rover.addInstruction(hop);
    rover.addInstruction(go, 0);
    rover.addInstruction(infect);
    rover.addInstruction(go, 0);

    // ----
    // trap
    // ----
    Species trap("trap");
    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
    trap.addInstruction(if_enemy, 3);
    trap.addInstruction(left);
    trap.addInstruction(go, 0);
    trap.addInstruction(infect);
    trap.addInstruction(go, 0);

    // ----
    // best
    // ----
    Species best("best");
    /*
     0: if_enemy 9
     1: if_empty 7
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
    best.addInstruction(if_enemy, 6);
    best.addInstruction(if_empty, 4);
    best.addInstruction(right);
    best.addInstruction(go, 0);
    best.addInstruction(hop);
    best.addInstruction(go, 0);
    best.addInstruction(infect);
    best.addInstruction(go, 0);

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);
        Darwin one(8, 8);       
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0) Creature
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        one.addCreature(food,east,0,0);
        one.addCreature(hopper,north, 3,3);
        one.addCreature(hopper,east,3,4);
        one.addCreature(hopper,south,4,4);
        one.addCreature(hopper,west,4,3);
        one.addCreature(food,north,7,7);
        one.run(cout, 5);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        Darwin two(7,9);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        two.addCreature(trap,south,0,0);
        two.addCreature(hopper,east,3,2);
        two.addCreature(rover,north,5,4);
        two.addCreature(trap,west,6,8);
        two.run(cout, 5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        Darwin three(72, 72);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print every 100th grid.
        */

        int n = 72;
        int mod = n*n;
        for(int i = 0; i < 10; ++i){
            int pos = rand() % mod;
            int dir = rand() % 4;
            three.addCreature(food, static_cast<direction_t>(dir), (pos/n), (pos%n)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % mod;
            int dir = rand() % 4;
            three.addCreature(hopper, static_cast<direction_t>(dir), (pos/n), (pos%n)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % mod;
            int dir = rand() % 4;
            three.addCreature(rover, static_cast<direction_t>(dir), (pos/n), (pos%n)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % mod;
            int dir = rand() % 4;
            three.addCreature(trap, static_cast<direction_t>(dir), (pos/n), (pos%n)); 
        }
        three.run(cout, 1000, 100);

    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        Darwin four(72, 72);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */

        int n = 72;
        int mod = n*n;
        for(int i = 0; i < 10; ++i){
            int pos = rand() % mod;
            int dir = rand() % 4;
            four.addCreature(food, static_cast<direction_t>(dir), (pos/n), (pos%n)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % mod;
            int dir = rand() % 4;
            four.addCreature(hopper, static_cast<direction_t>(dir), (pos/n), (pos%n)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % mod;
            int dir = rand() % 4;
            four.addCreature(rover, static_cast<direction_t>(dir), (pos/n), (pos%n)); 
        }
        for(int i = 0; i < 10; ++i){
            int pos = rand() % mod;
            int dir = rand() % 4;
            four.addCreature(trap, static_cast<direction_t>(dir), (pos/n), (pos%n)); 
        }
        for(int i = 0; i < 10; ++i) {
            int pos = rand() % mod;
            int dir = rand() % 4;
            four.addCreature(best, static_cast<direction_t>(dir), (pos/n), (pos%n));
        }
        four.run(cout, 1000, 100);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------
    // test5
    // ------------


    try {
        cout << "*** Darwin test5 ***" << endl;
        srand(0);
        Darwin five(1, 1);
        five.addCreature(food, north, 0, 0);
        five.run(cout, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

    // ------------
    // test6
    // ------------


    try {
        cout << "*** Darwin test6 ***" << endl;
        srand(0);
        Darwin six(3, 1);
        six.addCreature(hopper, south, 0, 0);
        six.run(cout, 3);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

    // ------------
    // test7
    // ------------


    try {
        cout << "*** Darwin test7 ***" << endl;
        srand(0);
        Darwin seven(1, 3);
        seven.addCreature(hopper, east, 0, 0);
        seven.run(cout, 3);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

    // ------------
    // test8
    // ------------


    try {
        cout << "*** Darwin test8 ***" << endl;
        srand(0);
        Darwin eight(1, 3);
        eight.addCreature(trap, east, 0, 0);
        eight.addCreature(food, east, 0, 1);
        eight.addCreature(food, east, 0, 2);
        eight.run(cout, 2);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

    // ------------
    // test9
    // ------------


    try {
        cout << "*** Darwin test9 ***" << endl;
        srand(0);
        Darwin nine(1, 3);
        nine.addCreature(trap, east, 0, 0);
        nine.addCreature(food, south, 0, 1);
        nine.addCreature(food, west, 0, 2);
        nine.run(cout, 3);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

    // ------------
    // test10
    // ------------


    try {
        cout << "*** Darwin test10 ***" << endl;
        srand(0);
        Darwin ten(1, 3);
        ten.addCreature(food, east, 0, 0);
        ten.addCreature(food, north, 0, 1);
        ten.addCreature(trap, west, 0, 2);
        ten.run(cout, 3);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

    // ------------
    // test11
    // ------------


    try {
        cout << "*** Darwin test11 ***" << endl;
        srand(0);
        Darwin eleven(1, 3);
        eleven.addCreature(hopper, east, 0, 0);
        eleven.addCreature(hopper, east, 0, 1);
        eleven.run(cout, 3);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

    // ------------
    // test12
    // ------------


    try {
        cout << "*** Darwin test12 ***" << endl;
        srand(0);
        Darwin twelve(1, 3);
        twelve.addCreature(hopper, west, 0, 1);
        twelve.addCreature(hopper, west, 0, 2);
        twelve.run(cout, 2);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

    // ------------
    // test13
    // ------------


    try {
        cout << "*** Darwin test13 ***" << endl;
        srand(0);
        Darwin thirteen(1, 3);
        thirteen.addCreature(hopper, west, 0, 1);
        thirteen.addCreature(trap, west, 0, 2);
        thirteen.run(cout, 2);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        

    // ------------
    // test14
    // ------------


    try {
        cout << "*** Darwin test14 ***" << endl;
        srand(0);
        Darwin fourteen(1,3);
        fourteen.addCreature(rover, east, 0, 0);
        fourteen.addCreature(food, north, 0, 1);
        fourteen.addCreature(trap, west, 0, 2);
        fourteen.run(cout, 3);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}