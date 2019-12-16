all: main.out
test: main.out
	./main.out
main.out: test.o
	g++ -o main.out test.cpp Threads.cpp -lpthread
test.o: test.cpp 
	g++ -o test test.cpp Threads.cpp -lpthread