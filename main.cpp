#include<iostream>
#include"complex.h"
using namespace std;
int main() {
	string s;
	cout << "-------------------------------��ӭ����������-----------------------------"<<endl;
	Complex c;
	while (s != "quit") {
		cout << endl;
		cout << "��������ʽ���������������quit" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << ">>>";
		cin >> s;
		c.display();
	}
	return 0;
}