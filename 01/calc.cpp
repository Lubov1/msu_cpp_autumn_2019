#include <iostream>
#include <cstdint>
#include <chrono>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <exception>

using namespace std;
class My_exception : public exception{
	string m_error;
public:
	My_exception(const string &error):m_error(error){}
	const char* what() const noexcept{
		return m_error.c_str();
	}
};
class Calc{
	string s;	//обрабатываемая строка
	int cur=0;		//позиция текущего символа в s
	char c;			// текущий символ
public:
	int result;

	Calc(const string &s);
	char get_sym();	//получаем следующий символ
	int f_add();
	int f_mult();
	int f_ynary_minus();
	int f_int();
};
	Calc::Calc(const string & p){
		s=p;
		c=get_sym();
		result=f_add();
	}
	char Calc::get_sym(){
		if(s[cur]==' ')
			for(;s[cur]==' ';cur++);
		return s[cur++];
	}
	int Calc::f_int(){
		string str;
		int i;
		for( i=0;c>='0' && c<='9';i++){
			str[i]=c;
			c=get_sym();
		}
		str[i]='\0';

		try{
			i=stoi(str);
		}
		catch (const exception & err){
			cout<<"!!!"<<err.what();
			return 1;
		}
		return i;

	}
	int Calc::f_ynary_minus(){
		int res;
			if(c=='-'){
				c=get_sym();
				return f_int()*(-1);
			}
			else return f_int();
	}
	int Calc::f_mult(){
		int res=f_ynary_minus();
		int k;
		while(c=='*' || c=='/'){
			if(c=='*'){
				c=get_sym();
				res*=f_ynary_minus();
			}
			else{
				c=get_sym();
				k=f_ynary_minus();
				if(k==0){
					cout <<"!!! деление на ноль";
					return 1;
				}
				res/=k;
			}
		}
		return res;
	}
	int Calc::f_add(){

		int res=f_mult();
		while((c=='+' || c=='-') && c!='\0'){
			if(c=='+'){
				c=get_sym();
				res+=f_mult();
			}
			else{
				c=get_sym();
				res-=f_mult();	
			}
		}
		return res;

	}



int main(int argc, char const *argv[])
{

	try{
		if(argc!=2)
		throw My_exception("!!! неправильное кол-во аргументов");
		Calc A(argv[1]);
		cout<< A.result;
	}
	catch (My_exception &err){
    	cout<<err.what();
		return 1;
	}
	return 0;
}