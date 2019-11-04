all: test.o
test: test.o
	./main.out
test.o: BigInt.cpp test.cpp
	g++ -o main.out BigInt.cpp test.cpp