#include<iostream>
#include"complex.h"
using namespace std;
int main() {
	string s;
	cout << "-------------------------------欢迎来到计算器-----------------------------"<<endl;
	Complex c;
	while (s != "quit") {
		cout << endl;
		cout << "请输入算式，如需结束请输入quit" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << ">>>";
		cin >> s;
		c.display();
	}
	return 0;
}