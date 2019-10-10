all: sum_by_rows.o sum_by_stlb.o
sum_by_rows.o: sum_by_rows.cpp 
	g++ sum_by_rows.cpp -o sum_by_rows --std=c++11 -O2
sum_by_stlb.o: sum_by_stlb.cpp 
	g++ sum_by_stlb.cpp -o sum_by_stlb --std=c++11 -O2
clean:
	rm main.out sum_by_rows.o sum_by_stlb.o  
run:
	./sum_by_rows
	./sum_by_stlb