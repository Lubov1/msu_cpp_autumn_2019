#include <iostream>
#include <stdlib.h>
#include <exception>
#include "alloc.h"
using namespace std;


LinearAllocator::LinearAllocator(size_t max){
	offset=0;
	maxSize=max;
	char *ptr=new char[maxSize];
	ptr_start=ptr;
}
char* LinearAllocator::alloc(size_t size){
	if(maxSize-offset>=size){
		int cur_offset=offset;
		offset+=size;
		ptr=ptr+cur_offset;
		return ptr;
	}
	return NULL;
}
void LinearAllocator::reset(){
	offset=0;
}
LinearAllocator::~LinearAllocator(){
	delete [] ptr_start;
}
