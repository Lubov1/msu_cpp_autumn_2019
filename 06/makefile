all: main.out
test: main.out
	./main.out
main.out: test.o
	g++ -o main.out test.o
test.o: test.cpp 
	g++ -c -o test.o test.cpp