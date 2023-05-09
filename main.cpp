#include<iostream>
#include"complex.h"
using namespace std;

void help() {
	cout << "\n���Լ��㸴�������������㣬����������ֵarg( )������� cjg( )��ģ |  |���˷� a^b���Ӽ��˳�+ - * /" << endl;
	cout << "��ע�� ���Ÿ����Ϳ����ţ��Լ�ȫ��ҪӢ�����뷨��" << endl;
	cout << "��ע�⣺��ʵ������|�������š���i�� ���ߡ�������ͷ����ʵ������|������i�����ߡ�������β" << endl;
	cout << "��ע�⣺������ ���治���ǡ��������߲��������Ӽ��˳�����ʵ�����治�����󡰣������� | ������ʵ��" << endl;
	cout << "��ע�⣺iǰ������ǼӼ��˳���ʵ������������(�����ڵĽ��������ʵ��)��i��������ǡ����������������Ӽ��˳��������ǡ���������i������ | ������ʵ�� "<<endl;
	cout << "��ע�⣺��������������ǡ�������ʵ������i������|�����������ǡ��������߼Ӽ��˳� "<<endl;
	cout << "��ע�⣺��������������ǡ���������i�������������Ӽ��˳�������^�����������ǡ���������ʵ�� "<<endl;
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
	//   i|3| ��|+�����д�����
	for (int i = 0; i < s.size(); i++) {
		if (!isdigit(s[i]) && s[i] != 'a' && s[i] != 'r' && s[i] != 'g' && s[i] != 'i' && s[i] != 'c' && s[i] != 'j' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '^' && s[i] != '|' && s[i] != '(' && s[i] != ')' && s[i] != '.') {
			cout << "���󣺲��ǿ�ִ�е��ַ���";
			error(s, i);
			return 0;
		}
		else if (i<s.size()-1&&(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')&&(s[i+1]==')'|| s[i+1] == '+' || s[i+1] == '-' || s[i+1] == '*' || s[i+1] == '/')) {
			cout << "���������������";
			error(s, i+1);
			return 0;
		}
		else if (s[i] == '.' && i < s.size() - 1 && i>0 &&( !isdigit(s[i + 1]) || !isdigit(s[i - 1]))) {
			cout << "����С����λ�ô���";
			error(s, i);
			return 0;
		}
		else if (s[0] == '.') {
			cout << "����С����λ�ô���";
			error(s, 0);
			return 0;
		}
		else if (i < s.size() - 2 && s[i] == 'i' && s[i + 1] == ')' && s[i + 2] == 'i') {
			cout << "���󣺴�������ӦΪʵ����";
			error(s, i + 2);
			return 0;
		}
		else if ((i< s.size() - 1) && s[i] == 'i' && (s[i + 1] == 'i' || s[i + 1] == '(' )) {
			cout << "����i ���治���Ǹ÷��ţ�";
			error(s, i + 1);
			return 0;
		}
		
		else if ((i < s.size() - 1) && s[i] == '(' && (s[i + 1] == ')' || s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/')) {
			cout << "���󣺡�(�� ���治���Ǹ÷��ţ�";
			error(s, i + 1);
			return 0;
		}
		else if (i < s.size() - 2 && s[i] == '/' && s[i + 1] == '0' && s[i + 2] != '.') {
			cout << "���󣺳�������Ϊ 0����";
			error(s, i + 1);
			return 0;
		}
		else if (s[s.size() - 2] == '/' && s[s.size() - 1] == '0') {
			cout << "���󣺳�������Ϊ 0����";
			error(s,s.size()-1);
			return 0;
		}
		else if ((i < s.size() - 1) && s[i] == ')' && (s[i + 1] == '(' || isdigit(s[i + 1]) ) ){
			cout << "���󣺡�)�� ���治���Ǹ÷��ţ�";
			error(s, i + 1);
			return 0;
		}
		else {
			if (s[i] == '(')cnt++;
			if (s[i] == ')')cnt--;
			if (cnt < 0) {
				cout << "�������Ų�ƥ�䣺";
				error(s, i );
				return 0;
			}
		}
	}if (cnt != 0) {
			cout << "�������Ų�ƥ�䣺";
			error(s, s.find("("));
			return 0;
		}
	return 1;
}
// �����ַ�����ʹ arg �ȱ�Ϊ������
string deal(string s) {
	while (s.find("arg") != -1) {
		int pos = s.find("arg");
		s.replace(pos, 3, "a");
	}
	while (s.find("cjg") != -1) {
		int pos = s.find("cjg");
		s.replace(pos, 3, "c");
	}
	while (s.find("|") != -1) {
		int pos = s.find("|");
		pos=s.find("|",pos+1);
		s.replace(pos, 1, ")");
		pos = s.find("|");
		s.replace(pos, 1, "m(");
	}
	return s;
}

void oper() {
	string s;
	cout << "-------------------------------��ӭ����������-----------------------------" << endl;
	Complex c;
	while (s != "quit") {
		cout << endl;
		cout << "\n��������ʽ���������������quit������鿴��������help" << endl;
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
			s = deal(s);
			cout<<c.calculate(s);
			//c.display();
		}
	}
	cout << "-------------------------------��ӭ�´�ʹ��-----------------------------" << endl;
	cin.ignore(100, '\n');
	cout << "\n�����������ַ���������" << endl;
	cin.get();
}



int main() {
	oper();
	return 0;
}