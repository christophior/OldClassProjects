// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <ostream>
#include <vector>
#include <sstream>

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"


#define private public
#define protected public
#include "Darwin.h"


// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {

    // ---------
    // directionString
    // ---------
    void test_direction_string_1() {
        
        CPPUNIT_ASSERT(directionString(north) == "north");
    }

    void test_direction_string_2(){
        CPPUNIT_ASSERT(directionString(west) == "west");
    }

    void test_direction_string_3(){
        CPPUNIT_ASSERT(directionString(south) == "south");
    }

    // --------------------
    // Species::Constructor
    // --------------------
    void test_species_constructor_1() {
        Species s("troy");
        CPPUNIT_ASSERT(s._name == 't');
        CPPUNIT_ASSERT(s._instructions.size() == 0);
    }

    void test_species_constructor_2(){
        Species s("chris");
        CPPUNIT_ASSERT(s._name == 'c');
        CPPUNIT_ASSERT(s._instructions.size() == 0);
    }

    void test_species_constructor_3(){
        Species s("michael");
        CPPUNIT_ASSERT(s._name == 'm');
        CPPUNIT_ASSERT(s._instructions.size() == 0);
    }

    // -------------------
    // Species::getInstruction
    // -------------------

    void test_species_getInstruction_1(){
        Species s("test");
        s.addInstruction(go, 1);
        CPPUNIT_ASSERT(s.getInstruction(0)._instruction == go);
    }

    void test_species_getInstruction_2() {
        Species s("test");
        s.addInstruction(hop);
        s.addInstruction(go, 0);
        CPPUNIT_ASSERT(s.getInstruction(0)._instruction == hop);
        CPPUNIT_ASSERT(s.getInstruction(1)._instruction == go);
    }

    void test_species_getInstruction_3() {
        Species s("test");
        s.addInstruction(hop);
        s.addInstruction(go, 0);
        CPPUNIT_ASSERT(s.getInstruction(0)._n == -1);
        CPPUNIT_ASSERT(s.getInstruction(1)._n == 0);
    }

    // -------------------
    // Species::name
    // -------------------

    void test_species_name_1(){
        Species s("troy");
        CPPUNIT_ASSERT(s.name() == 't');
    }

    void test_species_name_2() {
        Species s("michael");
        CPPUNIT_ASSERT(s.name() == 'm');
    }

    void test_species_name_3() {
        Species s("chris");
        CPPUNIT_ASSERT(s.name() == 'c');
    }


    // ------------------
    // Species::addInstruction
    // ------------------

    void test_species_addInstruction_1() {
        Species s("test");
        s.addInstruction(hop);
        s.addInstruction(go, 0);
        CPPUNIT_ASSERT(s._instructions.size() == 2);
    }

    void test_species_addInstruction_2() {
        Species s("test");
        s.addInstruction(hop);
        s.addInstruction(go, 0);
        CPPUNIT_ASSERT(s._instructions[0]._instruction == hop);
        CPPUNIT_ASSERT(s._instructions[1]._instruction == go);
    }

    void test_species_addInstruction_3() {
        Species s("test");
        s.addInstruction(hop);
        s.addInstruction(go, 0);
        CPPUNIT_ASSERT(s._instructions[0]._n == -1);
        CPPUNIT_ASSERT(s._instructions[1]._n == 0);
    }

    // ---------------------
    // Creature::constructor
    // ---------------------

    void test_creature_constructor_1() {
        Species s("test");
        Creature c(s);
        CPPUNIT_ASSERT(c._species._name == 't');
        CPPUNIT_ASSERT(c._programCounter == 0);
        CPPUNIT_ASSERT(c._runCounter == 1);
    }

    void test_creature_constructor_2() {
        Species s("test");
        Creature c(s, 1);
        CPPUNIT_ASSERT(c._species._name == 't');
        CPPUNIT_ASSERT(c._programCounter == 1);
        CPPUNIT_ASSERT(c._runCounter == 1);
    }

    void test_creature_constructor_3() {
        Species s("test");
        Creature c(s, 1, 2);
        CPPUNIT_ASSERT(c._species._name == 't');
        CPPUNIT_ASSERT(c._programCounter == 1);
        CPPUNIT_ASSERT(c._runCounter == 2);
    }

    // ---------------
    // Creature::infect
    // ---------------

    void test_creature_infect_1() {
        Species s1("test1");
        Species s2("test2");
        Creature c1(s1);
        Creature c2(s2);
        c1.infect(c2);
        CPPUNIT_ASSERT(c1._species == c2._species);
    }

    void test_creature_infect_2() {
        Species s1("test1");
        Species s2("test2");
        Creature c1(s1, 2);
        Creature c2(s2, 3);
        c1.infect(c2);
        CPPUNIT_ASSERT(c1._programCounter == 2);
        CPPUNIT_ASSERT(c2._programCounter == 0);
    }

    void test_creature_infect_3() {
        Species s1("test1");
        Species s2("test2");
        Creature c1(s1, 2, 2);
        Creature c2(s2, 3, 1);
        c1.infect(c2);
        CPPUNIT_ASSERT(c1._runCounter == 2);
        CPPUNIT_ASSERT(c2._runCounter == 1);
    }

    // --------------
    // Creature::hasTurn
    // --------------

    void test_creature_hasTurn_1() {
        Species s("test");
        Creature c(s);
        CPPUNIT_ASSERT(c.hasTurn(1));
    }

    void test_creature_hasTurn_2() {
        Species s("test");
        Creature c(s);
        CPPUNIT_ASSERT(!c.hasTurn(-1));
    }

    void test_creature_hasTurn_3() {
        Species s("test");
        Creature c(s, 0, 3);
        CPPUNIT_ASSERT(c.hasTurn(3));
    }

    // ------------------
    // Creature::takeTurn
    // ------------------

    void test_creature_takeTurn_1() {
        Species s("test");
        s.addInstruction(left);
        s.addInstruction(go, 0);
        Creature c(s);
        Board b(Species("."), nulldirection, 8, 8);
        b.addCreature(c, east, 0, 0);
        c.takeTurn(b, 0, 0);
        CPPUNIT_ASSERT(c._programCounter == 1);
        CPPUNIT_ASSERT(c._runCounter == 2);
    }

    void test_creature_takeTurn_2() {
        Species s("test");
        s.addInstruction(if_empty, 3);
        s.addInstruction(left);
        s.addInstruction(go, 0);
        s.addInstruction(right);
        s.addInstruction(go, 0);
        Creature c(s);
        Board b(Species("."), nulldirection, 8, 8);
        b.addCreature(c, east, 0, 0);
        c.takeTurn(b, 0, 0);
        CPPUNIT_ASSERT(c._programCounter == 4);
        CPPUNIT_ASSERT(c._runCounter == 2);
    }

    void test_creature_takeTurn_3() {
        Species s("test");
        s.addInstruction(if_empty, 3);
        s.addInstruction(left);
        s.addInstruction(go, 0);
        s.addInstruction(right);
        s.addInstruction(go, 0);
        Creature c(s);
        Board b(Species("."), nulldirection, 8, 8);
        b.addCreature(c, west, 0, 0);
        c.takeTurn(b, 0, 0);
        CPPUNIT_ASSERT(c._programCounter == 2);
        CPPUNIT_ASSERT(c._runCounter == 2);
    }

    // -------------------
    // Creature::name
    // -------------------

    void test_creature_name_1() {
        Species s("troy");
        Creature c(s);
        CPPUNIT_ASSERT(c.name() == 't');
    }

    void test_creature_name_2() {
        Species s("chris");
        Creature c(s);
        CPPUNIT_ASSERT(c.name() == 'c');
    }

    void test_creature_name_3() {
        Species s("michael");
        Creature c(s);
        CPPUNIT_ASSERT(c.name() == 'm');
    }

    // -------------------
    // Creature::sameSpecies
    // -------------------

    void test_creature_sameSpecies_1() {
        Species s("test");
        Creature c1(s);
        Creature c2(s);
        CPPUNIT_ASSERT(c1.sameSpecies(c2));
    }

    void test_creature_sameSpecies_2() {
        Species s1("test");
        Species s2("bob");
        Creature c1(s1);
        Creature c2(s2);
        CPPUNIT_ASSERT(!c1.sameSpecies(c2));
    }

    void test_creature_sameSpecies_3() {
        Species s1("test");
        Species s2("troy");
        Creature c1(s1);
        Creature c2(s2);
        CPPUNIT_ASSERT(c1.sameSpecies(c2));
    }

    // -----------------
    // Board::Contructor
    // -----------------

    void test_board_constructor_1() {
        Board b(Species("."), nulldirection, 8, 8);
        CPPUNIT_ASSERT(b._defaultCreature.name() == '.');
        CPPUNIT_ASSERT(b._defaultDirection == nulldirection);
        CPPUNIT_ASSERT(b._x == 8);
        CPPUNIT_ASSERT(b._y == 8);
        CPPUNIT_ASSERT((b._board.size() * b._board[0].size()) == (8*8));
    }

    void test_board_constructor_2() {
        Board b(Species("test"), east, 9, 7);
        CPPUNIT_ASSERT(b._defaultCreature.name() == 't');
        CPPUNIT_ASSERT(b._defaultDirection == east);
        CPPUNIT_ASSERT(b._x == 9);
        CPPUNIT_ASSERT(b._y == 7);
        CPPUNIT_ASSERT((b._board.size() * b._board[0].size()) == (9*7));
    }

    void test_board_constructor_3() {
        Board b(Species("."), nulldirection, 72, 72);
        CPPUNIT_ASSERT(b._defaultCreature.name() == '.');
        CPPUNIT_ASSERT(b._defaultDirection == nulldirection);
        CPPUNIT_ASSERT(b._x == 72);
        CPPUNIT_ASSERT(b._y == 72);
        CPPUNIT_ASSERT((b._board.size() * b._board[0].size()) == (72*72));
    }

    // -----------
    // Board::addCreature
    // -----------

    void test_board_addCreature_1() {
        Board b(Species("."), nulldirection, 8, 8);
        Species s("test");
        Creature c(s);
        b.addCreature(c, east, 0, 0);
        CPPUNIT_ASSERT(b._board[0][0].first == c);
        CPPUNIT_ASSERT(b._board[0][0].second == east);
    }

    void test_board_addCreature_2() {
        Board b(Species("."), nulldirection, 8, 8);
        Species s("test");
        Creature c(s);
        b.addCreature(c, west, 7, 7);
        CPPUNIT_ASSERT(b._board[7][7].first == c);
        CPPUNIT_ASSERT(b._board[7][7].second == west);
    }

    void test_board_addCreature_3() {
        Board b(Species("."), nulldirection, 8, 8);
        Species s("test");
        Creature c1(s);
        Creature c2(s);
        b.addCreature(c1, east, 0, 0);
        b.addCreature(c2, west, 7, 7);
        CPPUNIT_ASSERT(b._board[0][0].first == c1);
        CPPUNIT_ASSERT(b._board[0][0].second == east);
        CPPUNIT_ASSERT(b._board[7][7].first == c2);
        CPPUNIT_ASSERT(b._board[7][7].second == west);
    }

    // -------------------
    // Board::doInstruction
    // -------------------

    void test_board_doInstruction_1() {
        Board b(Species("."), nulldirection, 8, 8);
        Species s("test");
        Creature c(s);
        b.addCreature(c, east, 0, 0);
        Instruction i(left, -1);
        b.doInstruction(i, 0, 0);
        CPPUNIT_ASSERT(b._board[0][0].first == c);
        CPPUNIT_ASSERT(b._board[0][0].second == north);
    }

    void test_board_doInstruction_2(){
        Board b(Species("."), nulldirection, 8, 8);
        Species s("test");
        Creature c(s);
        b.addCreature(c, east, 0, 0);
        Instruction i(right, -1);
        b.doInstruction(i, 0, 0);
        CPPUNIT_ASSERT(b._board[0][0].first == c);
        CPPUNIT_ASSERT(b._board[0][0].second == south);
    }

    void test_board_doInstruction_3() {
        Board b(Species("."), nulldirection, 8, 8);
        Species s("test");
        Creature c(s);
        b.addCreature(c, east, 0, 0);
        Instruction i(hop, -1);
        b.doInstruction(i, 0, 0);
        CPPUNIT_ASSERT(b._board[0][0].first == Creature(Species(".")));
        CPPUNIT_ASSERT(b._board[0][0].second == nulldirection);
        CPPUNIT_ASSERT(b._board[0][1].first == c);
        CPPUNIT_ASSERT(b._board[0][1].second == east);
    }

    // ------------------------
    // Board::print
    // ------------------------

    void test_board_print_1(){
        Board b(Species("."), nulldirection, 2, 2);
        std::ostringstream out1;
        b.print(out1);
        std::ostringstream out2;
        out2 << "  01" << endl;
        out2 << "0 .." << endl;
        out2 << "1 .." << endl;
        out2 << endl;
        CPPUNIT_ASSERT(out1.str() == out2.str());
    }

    void test_board_print_2() {
        Board b(Species("."), nulldirection, 1, 20);
        std::ostringstream out1;
        b.print(out1);
        std::ostringstream out2;
        out2 << "  01234567890123456789" << endl;
        out2 << "0 ...................." << endl;
        out2 << endl;
        CPPUNIT_ASSERT(out1.str() == out2.str());
    }

    void test_board_print_3() {
        Board b(Species("."), nulldirection, 2, 2);
        Species s("test");
        Creature c(s);
        b.addCreature(c, east, 0, 0);
        std::ostringstream out1;
        b.print(out1);
        std::ostringstream out2;
        out2 << "  01" << endl;
        out2 << "0 t." << endl;
        out2 << "1 .." << endl;
        out2 << endl;
        CPPUNIT_ASSERT(out1.str() == out2.str());
    }

    // -----------------------------
    // Board::run
    // -----------------------------

    void test_board_run_1() {
        Species s("test");
        s.addInstruction(left);
        s.addInstruction(go, 0);
        Creature c(s);
        Board b(Species("."), nulldirection, 8, 8);
        b.addCreature(c, east, 0, 0);
        b.run(1);
        CPPUNIT_ASSERT(b._board[0][0].first._programCounter == 1);
        CPPUNIT_ASSERT(b._board[0][0].first._runCounter == 2);
        CPPUNIT_ASSERT(b._board[0][0].second == north);
    }

    void test_board_run_2() {
        Species s("test");
        s.addInstruction(if_empty, 3);
        s.addInstruction(left);
        s.addInstruction(go, 0);
        s.addInstruction(right);
        s.addInstruction(go, 0);
        Creature c(s);
        Board b(Species("."), nulldirection, 8, 8);
        b.addCreature(c, east, 0, 0);
        b.run(1);
        CPPUNIT_ASSERT(b._board[0][0].first._programCounter == 4);
        CPPUNIT_ASSERT(b._board[0][0].first._runCounter == 2);
        CPPUNIT_ASSERT(b._board[0][0].second == south);
    }

    void test_board_run_3() {
        Species s("test");
        s.addInstruction(hop);
        s.addInstruction(go, 0);
        Creature c(s);
        Board b(Species("."), nulldirection, 8, 8);
        b.addCreature(c, south, 0, 0);
        b.run(1);
        CPPUNIT_ASSERT(b._board[1][0].first._programCounter == 1);
        CPPUNIT_ASSERT(b._board[1][0].first._runCounter == 2);
        CPPUNIT_ASSERT(b._board[1][0].second == south);
    }

    // --------------
    // Board::isValid
    // --------------

    void test_board_isValid_1() {
        Board b(Species("."), nulldirection, 2, 2);
        CPPUNIT_ASSERT(b.isValid(0,0));
    }

    void test_board_isValid_2() {
        Board b(Species("."), nulldirection, 2, 2);
        CPPUNIT_ASSERT(!b.isValid(-1,0));
        CPPUNIT_ASSERT(!b.isValid(0,-1));
        CPPUNIT_ASSERT(!b.isValid(-1,-1));
    }

    void test_board_isValid_3() {
        Board b(Species("."), nulldirection, 2, 2);
        CPPUNIT_ASSERT(!b.isValid(2,0));
        CPPUNIT_ASSERT(!b.isValid(0,2));
        CPPUNIT_ASSERT(!b.isValid(2,2));
    }

    // ---------------
    // Board::isFree
    // ---------------

    void test_board_isFree_1(){
        Board b(Species("."), nulldirection, 2, 2);
        CPPUNIT_ASSERT(b.isFree(0,0));
    }

    void test_board_isFree_2(){
        Board b(Species("."), nulldirection, 2, 2);
        Species s("test");
        Creature c(s);
        b.addCreature(c, east, 0, 0);
        CPPUNIT_ASSERT(!b.isFree(0,0));
    }

    void test_board_isFree_3(){
        Species s("test");
        s.addInstruction(hop);
        s.addInstruction(go, 0);
        Creature c(s);
        Board b(Species("."), nulldirection, 8, 8);
        b.addCreature(c, south, 0, 0);
        CPPUNIT_ASSERT(!b.isFree(0,0));
        b.run(1);
        CPPUNIT_ASSERT(b.isFree(0,0));
    }

    // ----
    // Darwin::Constructor
    // ----

    void test_darwin_constructor_1() {
        Darwin d(8, 8);
        CPPUNIT_ASSERT(d._board._x == 8);
        CPPUNIT_ASSERT(d._board._y == 8);
        CPPUNIT_ASSERT(d._runCounter == 0);
    }

    void test_darwin_constructor_2() {
        Darwin d(9, 7);
        CPPUNIT_ASSERT(d._board._x == 9);
        CPPUNIT_ASSERT(d._board._y == 7);
        CPPUNIT_ASSERT(d._runCounter == 0);
    }

    void test_darwin_constructor_3() {
        Darwin d(0, 0);
        CPPUNIT_ASSERT(d._board._x == 0);
        CPPUNIT_ASSERT(d._board._y == 0);
        CPPUNIT_ASSERT(d._runCounter == 0);
    }
    
    // ------------------
    // Darwin::addCreature
    // ------------------

    void test_darwin_addCreature_1() {
        Darwin d(8,8);
        Species s("test");
        d.addCreature(s, east, 0, 0);
        CPPUNIT_ASSERT(d._board._board[0][0].first._species == s);
    }

    void test_darwin_addCreature_2() {
        Darwin d(8,8);
        Species s("test");
        d.addCreature(s, east, 7, 7);
        CPPUNIT_ASSERT(d._board._board[7][7].first._species == s);
    }

    void test_darwin_addCreature_3() {
        Darwin d(8,8);
        Species s("test");
        d.addCreature(s, east, 0, 0);
        d.addCreature(s, west, 7, 7);
        CPPUNIT_ASSERT(d._board._board[0][0].second == east);    
        CPPUNIT_ASSERT(d._board._board[7][7].second == west);
    }

    // ---------
    // Darwin::run
    // ---------

    void test_darwin_run_1() {
        Darwin d(1,1);
        Species s("test");
        s.addInstruction(left);
        s.addInstruction(go, 0);
        std::ostringstream out1;
        std::ostringstream out2;
        out2 << "Turn = 0." << endl;
        out2 << "  0" << endl;
        out2 << "0 ." << endl;
        out2 << endl;
        out2 << "Turn = 1." << endl;
        out2 << "  0" << endl;
        out2 << "0 ." << endl;
        out2 << endl;
        d.run(out1, 1);

        CPPUNIT_ASSERT(d._runCounter == 2);
        CPPUNIT_ASSERT(out1.str() == out2.str());
    }

    void test_darwin_run_2() {
        Darwin d(1,1);
        Species s("test");
        s.addInstruction(left);
        s.addInstruction(go, 0);
        d.addCreature(s, east, 0, 0);
        std::ostringstream out1;
        std::ostringstream out2;
        out2 << "Turn = 0." << endl;
        out2 << "  0" << endl;
        out2 << "0 t" << endl;
        out2 << endl;
        out2 << "Turn = 1." << endl;
        out2 << "  0" << endl;
        out2 << "0 t" << endl;
        out2 << endl;
        d.run(out1, 1);

        CPPUNIT_ASSERT(d._runCounter == 2);
        CPPUNIT_ASSERT(out1.str() == out2.str());
        CPPUNIT_ASSERT(d._board._board[0][0].second == north);
    }

    void test_darwin_run_3() {
        Darwin d(1,2);
        Species s("test");
        s.addInstruction(hop);
        s.addInstruction(go, 0);
        d.addCreature(s, west, 0, 1);
        std::ostringstream out1;
        std::ostringstream out2;
        out2 << "Turn = 0." << endl;
        out2 << "  01" << endl;
        out2 << "0 .t" << endl;
        out2 << endl;
        out2 << "Turn = 1." << endl;
        out2 << "  01" << endl;
        out2 << "0 t." << endl;
        out2 << endl;
        d.run(out1, 1);

        CPPUNIT_ASSERT(d._runCounter == 2);
        CPPUNIT_ASSERT(out1.str() == out2.str());
    }

    void test_darwin_run_4() {
        Darwin d(1,1);
        Species s("test");
        s.addInstruction(left);
        s.addInstruction(go, 0);
        std::ostringstream out1;
        std::ostringstream out2;
        out2 << "Turn = 0." << endl;
        out2 << "  0" << endl;
        out2 << "0 ." << endl;
        out2 << endl;
        out2 << "Turn = 5." << endl;
        out2 << "  0" << endl;
        out2 << "0 ." << endl;
        out2 << endl;
        d.run(out1, 5, 5);

        CPPUNIT_ASSERT(d._runCounter == 6);
        CPPUNIT_ASSERT(out1.str() == out2.str());
    }

    // ---------
    // TestSuite
    // ---------
    CPPUNIT_TEST_SUITE(TestDarwin);

    CPPUNIT_TEST(test_direction_string_1);
    CPPUNIT_TEST(test_direction_string_2);
    CPPUNIT_TEST(test_direction_string_3);

    CPPUNIT_TEST(test_species_constructor_1);
    CPPUNIT_TEST(test_species_constructor_2);
    CPPUNIT_TEST(test_species_constructor_3);

    CPPUNIT_TEST(test_species_getInstruction_1);
    CPPUNIT_TEST(test_species_getInstruction_2);
    CPPUNIT_TEST(test_species_getInstruction_3);

    CPPUNIT_TEST(test_species_name_1);
    CPPUNIT_TEST(test_species_name_2);
    CPPUNIT_TEST(test_species_name_3);

    CPPUNIT_TEST(test_species_addInstruction_1);
    CPPUNIT_TEST(test_species_addInstruction_2);
    CPPUNIT_TEST(test_species_addInstruction_3);

    CPPUNIT_TEST(test_creature_constructor_1);
    CPPUNIT_TEST(test_creature_constructor_2);
    CPPUNIT_TEST(test_creature_constructor_3);

    CPPUNIT_TEST(test_creature_infect_1);
    CPPUNIT_TEST(test_creature_infect_2);
    CPPUNIT_TEST(test_creature_infect_3);

    CPPUNIT_TEST(test_creature_hasTurn_1);
    CPPUNIT_TEST(test_creature_hasTurn_2);
    CPPUNIT_TEST(test_creature_hasTurn_3);

    CPPUNIT_TEST(test_creature_takeTurn_1);
    CPPUNIT_TEST(test_creature_takeTurn_2);
    CPPUNIT_TEST(test_creature_takeTurn_3);

    CPPUNIT_TEST(test_creature_name_1);
    CPPUNIT_TEST(test_creature_name_2);
    CPPUNIT_TEST(test_creature_name_3);

    CPPUNIT_TEST(test_creature_sameSpecies_1);
    CPPUNIT_TEST(test_creature_sameSpecies_2);
    CPPUNIT_TEST(test_creature_sameSpecies_3);

    CPPUNIT_TEST(test_board_constructor_1);
    CPPUNIT_TEST(test_board_constructor_2);
    CPPUNIT_TEST(test_board_constructor_3);

    CPPUNIT_TEST(test_board_addCreature_1);
    CPPUNIT_TEST(test_board_addCreature_2);
    CPPUNIT_TEST(test_board_addCreature_3);

    CPPUNIT_TEST(test_board_doInstruction_1);
    CPPUNIT_TEST(test_board_doInstruction_2);
    CPPUNIT_TEST(test_board_doInstruction_3);

    CPPUNIT_TEST(test_board_print_1);
    CPPUNIT_TEST(test_board_print_2);
    CPPUNIT_TEST(test_board_print_3);

    CPPUNIT_TEST(test_board_run_1);
    CPPUNIT_TEST(test_board_run_2);
    CPPUNIT_TEST(test_board_run_3);


    CPPUNIT_TEST(test_board_isValid_1);
    CPPUNIT_TEST(test_board_isValid_2);
    CPPUNIT_TEST(test_board_isValid_3);

    CPPUNIT_TEST(test_board_isFree_1);
    CPPUNIT_TEST(test_board_isFree_2);
    CPPUNIT_TEST(test_board_isFree_3);


    CPPUNIT_TEST(test_darwin_constructor_1);
    CPPUNIT_TEST(test_darwin_constructor_2);
    CPPUNIT_TEST(test_darwin_constructor_3);

    CPPUNIT_TEST(test_darwin_addCreature_1);
    CPPUNIT_TEST(test_darwin_addCreature_2);
    CPPUNIT_TEST(test_darwin_addCreature_3);

    CPPUNIT_TEST(test_darwin_run_1);
    CPPUNIT_TEST(test_darwin_run_2);
    CPPUNIT_TEST(test_darwin_run_3);
    CPPUNIT_TEST(test_darwin_run_4);

    CPPUNIT_TEST_SUITE_END();
};

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
