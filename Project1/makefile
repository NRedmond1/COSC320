main: main.o matrix.o
	g++ -std=c++11 main.o matrix.o -o Project1
main.o: main.cpp matrix.h
	g++ -c main.cpp
matrix.o: matrix.cpp matrix.h
	g++ -c matrix.cpp
clean:
	rm main.o matrix.o
