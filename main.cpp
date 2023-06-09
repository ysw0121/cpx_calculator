//#define debug
#define RECORD
#include<iostream>
#include<fstream>
#include"complex.h"
using namespace std;

void help() {
	cout << "\n可以计算复数及其四则运算，包括辐角主值arg( )，共轭复数 cjg( )，模 |  |，乘方 a^b，加减乘除+ - * /" << endl;
	cout << "请注意 括号个数和空括号，以及全部要英文输入法！" << endl;
	cout << "请注意：以实数、“|”、负号、”i” 或者“（”开头，以实数、“|”、“i”或者“）”结尾" << endl;
	cout << "请注意：操作符 后面不能是“）”或者操作符（加减乘除）；实数后面不能是左“（”，“ | ”或者实数" << endl;
	cout << "请注意：i前面可以是加减乘除、实数、“）”，(括号内的结果必须是实数)；i后面可以是“）”、操作符（加减乘除）不能是“（”、”i”、“ | ”或者实数 "<<endl;
	cout << "请注意：“（”后面可以是“（”、实数、“i”，”|”，不可以是“）”或者加减乘除 "<<endl;
	cout << "请注意：“）”后面可以是“）”，”i”、操作符（加减乘除）、”^”，不可以是“（”或者实数 "<<endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
}




void error(string s, int errpos) {
	int i = errpos;
	for (int j = 0;j<i; j++)cout << s[j];
	printf("\033[1;4;5;31m%c\033[0m", s[i]);
	for (int j = i + 1; j < s.size(); j++)cout << s[j];
}

bool examination(string s) {
	int cnt = 0;
	int cntl = 0;
	
	for (int i = 0; i < s.size(); i++) {
		
		if (!isdigit(s[i]) && s[i] != 'a' && s[i] != 'r' && s[i] != 'g' && s[i] != 'i' && s[i] != 'c' && s[i] != 'j' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '^' && s[i] != '|' && s[i] != '(' && s[i] != ')' && s[i] != '.') {
			cout << "错误：不是可执行的字符：";
			error(s, i);
			return 0;
		}
		
		else if ((s[0] == '+' || s[0] == '*' || s[0] == '/'||isalpha(s[0])) && isdigit(s[1])&&s.size()>1) {
			cout << "错误：符号错误：";
			error(s, 0);
			return 0;
		}
		else if (i<s.size()-1&&(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')&&(s[i+1]==')'|| s[i+1] == '+' || s[i+1] == '-' || s[i+1] == '*' || s[i+1] == '/')) {
			cout << "错误：运算符相连：";
			error(s, i+1);
			return 0;
		}
		else if (s[i] == '.' && i < s.size() - 1 && i>0 &&( !isdigit(s[i + 1]) || !isdigit(s[i - 1]))) {
			cout << "错误：小数点位置错误";
			error(s, i);
			return 0;
		}
		else if (s[0] == '.') {
			cout << "错误：小数点位置错误";
			error(s, 0);
			return 0;
		}
		else if (i < s.size() - 2 && s[i] == 'i' && s[i + 1] == ')' && s[i + 2] == 'i') {
			cout << "错误：此括号内应为实数：";
			error(s, i + 2);
			return 0;
		}
		else if ((i< s.size() - 1) && s[i] == 'i' && (s[i + 1] == 'i' || s[i + 1] == '(' )) {
			cout << "错误：i 后面不能是该符号：";
			error(s, i + 1);
			return 0;
		}
		else if (i < s.size() - 1 && isdigit(s[i]) &&  s[i + 1] == '(') {
			cout << "错误：实数后面不能是该符号：";
			error(s, i + 1);
			return 0;
		}
		else if (s[i] == '|') {
			cntl++;
			if (i != 0) {
				if ((isdigit(s[i - 1])||s[i-1]=='i') && cntl % 2 == 1) {
					cout << "错误：后面不能有 “|”：";
					error(s, i );
					return 0;
				}
				else if (((i < s.size() - 1)) && cntl % 2 == 0 && (s[i + 1] == 'i' || isdigit(s[i + 1]))) {
					cout << "错误：“|”后面不能再加数：";
					error(s, i + 1);
					return 0;
				}
				else if (s[i - 1] == '|' && cntl % 2 == 0) {
					cout << "错误：不能为空括号：";
					error(s, i );
					return 0;
				}
				else if( (i<s.size() -1)&&(s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '^' || s[i + 1] == '|' || s[i + 1] == ')')&&cntl%2==1){
					cout << "错误：符号位置错误：";
					error(s, i + 1);
					return 0;
				}
			}
		}

		else if (((i < s.size() - 1)) && s[i] == '(' && (s[i + 1] == ')' || s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/')) {
			cout << "错误：“(” 后面不能是该符号：";
			error(s, i + 1);
			return 0;
		}
		else if (((i < s.size() - 2)) && s[i] == '/' && s[i + 1] == '0' && s[i + 2] != '.') {
			cout << "错误：除数不能为 0！：";
			error(s, i + 1);
			return 0;
		}
		else if ((((i < s.size() - 1))) && s[i] == '^' && (s[i + 1] == '-' || s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '^' || s[i + 1] == 'a' || s[i + 1] == 'c' || s[i + 1] == 'r' || s[i + 1] == 'g' || s[i + 1] == 'j' || s[i + 1] == ')')) {
			cout << "错误：“^”后面不能是该符号：";
			error(s, i + 1);
			return 0;
		}
		else if (((s.size()>=2))&&s[s.size() - 2] == '/' && s[s.size() - 1] == '0') {
			cout << "错误：除数不能为 0！：";
			error(s,s.size()-1);
			return 0;
		}
		else if (((i < s.size() - 1)) && s[i] == ')' && (s[i + 1] == '(' || isdigit(s[i + 1]) ) ){
			cout << "错误：“)” 后面不能是该符号：";
			error(s, i + 1);
			return 0;
		}
		else {
			if (s[i] == '(')cnt++;
			if (s[i] == ')')cnt--;
			if (cnt < 0) {
				cout << "错误：括号不匹配：";
				error(s, i );
				return 0;
			}
		}
	}if (cnt != 0) {
			cout << "错误：括号不匹配：";
			error(s, s.find("("));
			return 0;
		}
	if (cntl % 2 == 1) {
		cout << "错误：括号不匹配：";
		error(s, s.find("|"));
		return 0;
	}
	if (!isdigit(s[s.size() -1]) && s[s.size() - 1] != 'i' && s[s.size() - 1] != '|' && s[s.size() - 1] != ')') {
		cout << "错误：表达式不完整：";
		error(s, s.size() - 1);
		return 0;
	}
	int kk = 0,kpos=0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			while (s[i] != ')') {
				i++;
				if (s[i] == '|') {
					kk++;
					kpos = i;
				}
			}
			if (kk % 2 == 1) {
				cout << "错误：括号不匹配：";
				error(s, kpos);
				return 0;
			}
		}
	}


	return 1;
}
// 处理字符串，使 arg 等变为操作符
string deal(string s) {
	if(s[0]=='-')s.insert(0, "0");

	while (s.find("arg") != -1) {
		int pos = s.find("arg");
		s.replace(pos, 3, "a");
	}
	while (s.find("cjg") != -1) {
		int pos = s.find("cjg");
		s.replace(pos, 3, "c");
	}
	int num = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '|') {
			num++;
			if (num % 2 == 1) {
				if (i < s.size() - 1) {
					if (s[i + 1] == '-' ) {
						s.insert(i + 1, "0");
					}
				}
				
				if (i > 0) {
					if (s[i - 1] == ')' ) {
						s.insert(i, "*");
					}
				}
				
			}
		}
	}

	for (int i = 0; i < s.size(); i++) {
		if (isdigit(s[i])) {
			if((i<s.size()-2)){
				if (s[i + 1] == 'i' && s[i + 2] == '^') {
					s.insert(i + 1, "*");
				}
			}
		}
	}

	while (s.find("|") != -1) {
		int pos = s.find("|");
		s.replace(pos, 1, "m(");
		pos=s.find("|",pos+1);
		s.replace(pos, 1, ")");
	}

	for (int i = 0; i < s.size(); i++) {
		if( i<s.size() - 1){
			if (s[i] == '(' && s[i + 1] == '-') {
				s.insert(i+1,"0");
			}
		}
	}
	for (int i = 0; i < s.size(); i++) {
		if (i < s.size() - 1) {
			if (s[i] == ')' && s[i + 1] == 'i') {
				s.insert(i + 1, "*");
			}
		}
	}
	
	return s;
}

void oper() {
	string s;
	cout << "-------------------------------欢迎来到计算器-----------------------------" << endl;
	Complex c;
	while (s != "quit") {
		cout << endl;
		cout << "\n请输入算式，如需结束请输入quit，如需查看规则，输入help" << endl;
		cout << "-------------------------------------------------------------------" << endl;
		cout << ">>>  ";
		getline(cin,s);
		if (s == "help") {
			help();
			continue;
		}
		if (s == "quit") {
			break;
		}
		bool exam=examination(s);
		if (s != "quit" && exam) {
			string tem = s;
			s = deal(s);
#ifdef debug
			cout << s;//test
#endif
			cout<<c.calculate(s);
#ifdef RECORD
			bool istr = c.calculate(s).inf(c.calculate(s));
			if (!istr) {
				ofstream fout("record.txt", ios::app);
				if (!fout) {
					cerr << "open error!" << endl;
					exit(1);
				}
				else fout << tem << "=" << c.calculate(s) << endl;
				fout.close();
			}
			#endif
		}
	}
	cout << "-------------------------------欢迎下次使用-----------------------------" << endl;
	cout << "\n请输入任意字符结束程序！" << endl;
	//cin.ignore(100, '\n');
	cin.get();
}



int main() {
	oper();
	return 0;
}