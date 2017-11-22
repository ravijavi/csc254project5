tombstones.o: tombstones.h

foo1: tombstones.o
	g++ -ggdb -o foo1 examples/foo1.cpp tombstones.o
foo2: tombstones.o
	g++ -ggdb -o foo2 examples/foo2.cpp tombstones.o
foo3: tombstones.o
	g++ -ggdb -o foo3 examples/foo3.cpp tombstones.o
foo4: tombstones.o
	g++ -ggdb -o foo4 examples/foo4.cpp tombstones.o
foo5: tombstones.o
	g++ -ggdb -o foo5 examples/foo5.cpp tombstones.o
foo6: tombstones.o
	g++ -ggdb -o foo6 examples/foo6.cpp tombstones.o
foo7: tombstones.o
	g++ -ggdb -o foo7 examples/foo7.cpp tombstones.o
foo8: tombstones.o
	g++ -ggdb -o foo8 examples/foo8.cpp tombstones.o


clean:
	rm *.o
