all: calc

run: calc
	./calc 9+5*2
test: calc
	python3 test.py

calc: calc.cpp
	g++ -o calc calc.cpp 