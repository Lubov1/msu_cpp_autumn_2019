all: test.o
test: test.o
	./main.out
test.o: Matrix.cpp test.cpp
	g++ -o main.out Matrix.cpp test.cpp