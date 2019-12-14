all: main.out
test: main.out
	valgrind --tool=memcheck ./main.out
main.out: sort.o
	g++ -o main.out -pthread sort.o
test.o: test.cpp 
	g++ -c -o test.o -pthread sort.cpp