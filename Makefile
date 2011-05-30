FLAGS=-Wall -O3 -ffast-math -funroll-loops

all:	test

Cover_Tree_Point.o: Cover_Tree_Point.h Cover_Tree_Point.cc
	g++ -c $(FLAGS) Cover_Tree_Point.cc

test: test.cc Cover_Tree.h Cover_Tree_Point.o Cover_Tree_Point.h Cover_Tree_Point.cc
	g++ $(FLAGS) -o test test.cc Cover_Tree.h Cover_Tree_Point.o

clean:
	rm *.o
