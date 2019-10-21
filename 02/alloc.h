#include <iostream>
#include <stdlib.h>
#include <exception>

using namespace std;
class LinearAllocator
{
	char* ptr;
	char* ptr_start;

	int offset;
	int maxSize;
public:
    LinearAllocator(size_t max);
    char* alloc(size_t size);
    void reset();
    ~LinearAllocator();
};