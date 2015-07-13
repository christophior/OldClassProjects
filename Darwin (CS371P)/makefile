all:
	make run
	make test

diff: RunDarwin
	RunDarwin > RunDarwin.tmp
	diff RunDarwin.out RunDarwin.tmp
	rm RunDarwin.tmp

doc:
	doxygen Doxyfile

log:
	git log > Darwin.log

RunDarwin: Darwin.h Darwin.c++ RunDarwin.c++
	g++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin

run: RunDarwin
	RunDarwin

runv: RunDarwin
	valgrind RunDarwin

TestDarwin: Darwin.h Darwin.c++ TestDarwin.c++
	g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lcppunit -ldl

test: TestDarwin
	TestDarwin

testv: TestDarwin
	valgrind TestDarwin

turnin-list:
	turnin --list reza cs371ppj4

turnin-submit:
	turnin --submit reza cs371ppj4 Darwin.zip

turnin-verify:
	turnin --verify reza cs371ppj4

zip:
	zip -r Darwin.zip html/ makefile Darwin.c++ Darwin.h Darwin.log Darwin.pdf \
	RunDarwin.c++ RunDarwin.out                                                \
	TestDarwin.c++ TestDarwin.out

clean:
	rm -f RunDarwin
	rm -f TestDarwin
	rm -f *.tmp