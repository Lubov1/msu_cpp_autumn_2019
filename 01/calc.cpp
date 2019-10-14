#include <iostream>
#include <cstdint>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using std::cout;

class calc
{
	char s[500];	//обрабатываемая строка
	int cur=0;		//позиция текущего символа в s
	char c;			// текущий символ
public:
	calc(const char*p);
	char get_sym();	//получаем следующий символ
	int f_add();
	int f_mult();
	int f_otric();
	int f_int();
};
	calc::calc(const char*p){
		strcpy(s,p);
		c=get_sym();
		cout<< f_add();
	}
	char calc::get_sym(){
		if(s[cur]==' ')
			for(;s[cur]==' ';cur++);
		return s[cur++];
	}
	int calc::f_int(){
		char str[20];
		int i;
		for( i=0;c>='0' && c<='9';i++){
			str[i]=c;
			c=get_sym();
		}
		str[i]='\0';
		return atoi(str);
	}
	int calc::f_otric(){
		int res;
			if(c=='-'){
				c=get_sym();
				return f_int()*(-1);
			}
			else return f_int();
	}
	int calc::f_mult(){
		int res=f_otric();
		int k;
		while(c=='*' || c=='/'){
			if(c=='*'){
				c=get_sym();
				res*=f_otric();
			}
			else{
				c=get_sym();
				k=f_otric();
				if(k==0)
					throw "!!! деление на ноль";
				res/=k;
			}
		}
		return res;
	}
	int calc::f_add(){

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
		throw "!!! неправильное кол-во аргументов";
		calc A(argv[1]);
	}
	catch(const char*u){
		cout<<u;
		return 1;
	}
	return 0;
}