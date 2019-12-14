all: main.out
test: main.out
	./main.out
main.out: test.o
	g++ -o main.out -pthread test.o
test.o: test.cpp 
	g++ -c -o test.o -pthread test.cpp