#include <iostream>
#include <stdlib.h>
#include <exception>
#include "alloc.h"

using namespace std;
int main(){
	int max_size=20;
	int size=10;
	LinearAllocator A(max_size);

	char* p=A.alloc(size);
	if (p==NULL)
		cout<<"error!! нулевой указатель"<<endl;
	p=A.alloc(max_size-size);
	if (p==NULL)
		cout<<"error!! нулевой указатель"<<5<<endl;
	p=A.alloc(1);
	if (p!=NULL)
		cout<<"error!! ненулевой указатель"<<1<<endl;

	A.reset();

	p=A.alloc(size);
	if (p==NULL)
		cout<<"error!! нулевой указатель"<<endl;
	p=A.alloc(1);
	if (p==NULL)
		cout<<"error!! нулевой указатель"<<endl;
	p=A.alloc(0);
	if (p==NULL)
		cout<<"error!! нулевой указатель"<<endl;
	p=A.alloc(max_size-size);
	if (p!=NULL)
		cout<<"error!! ненулевой указатель"<<endl;
	p=A.alloc(size);
	if (p!=NULL)
		cout<<"error!! ненулевой указатель"<<endl;
	
	A.reset();

	p=A.alloc(max_size);
	if (p==NULL)
		cout<<"error!! нулевой указатель"<<endl;
	p=A.alloc(1);
	if (p!=NULL)
		cout<<"error!! ненулевой указатель"<<endl;
	
}