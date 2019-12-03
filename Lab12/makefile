Lab12: main.o
	g++ -o Lab12 main.o
main.o: main.cpp graph.h
	g++ -c main.cpp -g -std=c++11 -Wall
clean:
	rm -f Lab12 main.o
rebuild:
	make clean
	make
