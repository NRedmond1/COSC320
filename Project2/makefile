Prog2: main.o
	g++ -o Prog2 main.o
main.o: main.cpp functions.h hash.h
	g++ -c main.cpp -g -std=c++11 -Wall
clean:
	rm -f Prog2 main.o
rebuild:
	make clean
	make
