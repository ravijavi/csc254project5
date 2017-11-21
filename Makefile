tombstones.o: tombstones.h

foo1: tombstones.o
	g++ -ggdb -o foo1 examples/foo1.cpp tombstones.o



clean:
	rm *.o
