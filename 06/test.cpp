#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <exception>
#include <cassert>
#include "form.h"
using namespace std;

int main(){
	try{
		Format format;
		int p = 9;
		string d = "www";
		float g = 1.3;
		auto text = format("{1}+{1} = {0}", 2, "one");
		assert(text == "one+one = 2");

		text = format("{1} = {0}", 2, "one");
		assert(text == "one = 2");

		text = format("{1} = {0} = {4} = {2} {3}", 2, "one", p ,d ,g ,3.4 );
		assert(text == "one = 2 = 1.3 = 9 www");

	}
	catch(exception& p){
		cout << p.what();
	}

}