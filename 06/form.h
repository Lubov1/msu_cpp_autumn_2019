#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <exception>
using namespace std;

class Format{
	vector<string> mas;
public:
	template <class T>
	void process(T&& val){
		stringstream y;
		y << val;
		mas.push_back(move(y.str()));
	}
	template <class T, class... ArgsT>
	void process(T&& val, ArgsT&&...args){
		process(forward<T>(val));
		process(forward<ArgsT>(args)...);
	}
	template <class... ArgsT>
	string operator()(const string& str, ArgsT&&... args){
		int counter_param = 0;
		stringstream s;
		string param_num;
		unsigned int k;
		process(forward<ArgsT>(args)...);
		for(unsigned int j=0; j < str.length();){
			if (str[j] == '{'){
				counter_param++;
				j++;
				if (j < str.length())
					for(;j < str.length() && str[j] != '}';j++)
						param_num.push_back(move(str[j]));
					if (str[j++] != '}')
						throw runtime_error("нет закрывающей скобки");
					k = stoi(param_num);
					if (k >= mas.size())
						throw runtime_error("неправильное кол-во параметров");
					s << mas[k];
					param_num.clear();
				
			}
			else
				s << str[j++];
		}
		string d = string(s.str());
		mas.clear();
		return d;
	}

};
