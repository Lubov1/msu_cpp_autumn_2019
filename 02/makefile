all: main.out
test: main.out
	./main.out
main.out: alloc.o test.o
	g++ -o main.out alloc.o test.o
test.o: test.cpp 
	g++ -c -o test.o test.cpp 
alloc.o: alloc.cpp 
	g++ -c -o alloc.o alloc.cpp