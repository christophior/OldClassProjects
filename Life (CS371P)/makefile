all:
	make run
	make test

diff: RunLife
	RunLife > RunLife.tmp
	diff RunLife.out RunLife.tmp
	rm RunLife.tmp

doc:
	doxygen Doxyfile

log:
	git log > Life.log

RunLife: AbstractCell.c++ AbstractCell.h Cell.h ConwayCell.c++ ConwayCell.h FredkinCell.c++ FredkinCell.h Handle.h Life.h RunLife.c++
	g++ -pedantic -std=c++0x -Wall AbstractCell.c++ ConwayCell.c++ FredkinCell.c++ RunLife.c++ -o RunLife

run: RunLife
	RunLife

runv: RunLife
	valgrind RunLife

TestLife: AbstractCell.c++ AbstractCell.h Cell.h ConwayCell.c++ ConwayCell.h FredkinCell.c++ FredkinCell.h Handle.h Life.h TestLife.c++
	g++ -pedantic -std=c++0x -Wall AbstractCell.c++ ConwayCell.c++ FredkinCell.c++ TestLife.c++ -o TestLife -lcppunit -ldl

test: TestLife
	TestLife

testv: TestLife
	valgrind TestLife

turnin-list:
	turnin --list reza cs371ppj5

turnin-submit:
	turnin --submit reza cs371ppj5 Life.zip

turnin-verify:
	turnin --verify reza cs371ppj5

zip:
	zip -r Life.zip html/ makefile     \
	AbstractCell.c++ AbstractCell.h    \
	Cell.h                             \
	ConwayCell.c++ ConwayCell.h        \
	FredkinCell.c++ FredkinCell.h      \
	Handle.h                           \
	Life.h Life.log Life.pdf           \
	RunLife.c++ RunLife.out            \
	RunLifeCell.in                     \
	RunLifeConway.in RunLifeFredkin.in \
	TestLife.c++ TestLife.out

clean:
	rm -f RunLife
	rm -f TestLife
	rm -f *.tmp