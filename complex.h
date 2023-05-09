//复数Complex类
//后面加 const表示函数不可以修改class的成员


#ifndef CPX
#define CPX
#include <iostream>
#include<cmath>
#include<stack>
#include<string>
#include<cstdlib>
#include<cctype>
using namespace std;
class Complex{
private:
	double real;
	double imag;

public:
	Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

	Complex operator+(Complex& c) const {
		return Complex(real + c.real, imag + c.imag);
	}
	Complex operator-(Complex& c) const {
		return Complex(real - c.real, imag - c.imag);
	}
	Complex operator*(Complex& c) const {
		return Complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
	}
	Complex operator/(Complex& c) const {
		double r = c.real * c.real + c.imag * c.imag;
		return Complex((real * c.real + imag * c.imag) / r, (imag * c.real - real * c.imag) / r);
	}
	bool operator==(Complex& c)const {
		if (c.real == real && c.imag == imag)return true;
		else return false;
	}
	friend ostream &operator<<(ostream& out,const Complex&c){
		out << "\n>>>  结果是：";
		if (c.imag == 0)out <<c. real;
		else if (c.real == 0)out << c.imag << "i";
		else if (c.imag > 0)out <<c.real << "+" << c.imag << "i";
		else out << c.real << c.imag << "i";
		return out;
	}
	//模长
	double module() const {
		return sqrt(real * real + imag * imag);
	}
	//辐角主值
	double arg() const {
		if (imag == 0 && real == 0)return 0;
		else if (imag >= 0 && real > 0)return atan(imag / real);
		else if (real == 0 && imag > 0)return acos(0.0);
		else if (real < 0 && imag>0)return acos(-1.0) - atan(imag / real);
		else if (real < 0 && imag == 0)return acos(-1.0);
		else if (real < 0 && imag < 0)return atan(imag / real) - acos(-1.0);
		else if (real == 0 && imag < 0)return -acos(0.0);
		else if (real > 0 && imag < 0)return atan(imag / real);
	}
	//共轭
	Complex cjg() const {
		return Complex(real, -imag);
	}
	//乘方
	Complex operator^(int n) {
		double m = module();
		double a = arg();
		return Complex(pow(m, n) * cos(a * n), pow(m, n) * sin(a * n));
	}

	Complex calcu(Complex c1, Complex c2,char op) {
		if (op == '+') {
			return c1.operator+(c2);
		}
		else if (op == '-') {
			return c1.operator-(c2);
		}
		else if (op == '*') {
			return c1.operator*(c2);
		}
		else if (op == '/') {
			return c1.operator/(c2);
		}
		else if (op == '^') {
			return c1.operator^(c2.real);
		}
		else if (op == '|') {
			return Complex(c1.module(), 0);
		}
		else if (op == 'i') {
			return Complex(0, 1);
		}
		else if (op == 'a') {
			return c1.arg();
		}
		else if (op == 'c') {
			return c1.cjg();
		}
	}
	int priority(char c) {
		int i;
		switch (c) {
			case '(':i = 5; break;
			case ')':i  =5; break;
			case '-':i  =1; break;
			case '+':i  =1; break;
			case '*':i  =2; break;
			case '/':i  =2; break;
			case '^':i  =3; break;
			case 'a':i  =4; break;
			case 'c':i=4; break;
			case'|':i=4; break;
			default:i = -1; break;
		}
		return i;
	}

	//逆波兰运算
	Complex calculate(string s) {
		stack<char> op;
		stack<Complex> num;
		for (int i = 0; i < s.size();) {
			if (isdigit(s[i])) {
				int j = i + 1;
				while (isdigit(s[j]) || s[j] == '.')j++;
				string str = s.substr(i, j - i);
				num.push(Complex(atof(str.c_str()), 0));
				i = j;
			}
			else if (s[i] == 'i') {
				num.push(Complex(0, 1));
				i++;
			}
			else if (s[i] == 'a') {
				op.push('a');
				i++;
			}
			else if (s[i] == 'c') {
				op.push('c');
				i++;
			}
			else if (s[i] == '|') {
				op.push('|');
				i++;
			}
			else if (s[i] == '(') {
				op.push('(');
				i++;
			}
			else if (s[i] == ')') {
				while (op.top() != '(') {
					Complex c2 = num.top();
					num.pop();
					Complex c1 = num.top();
					num.pop();
					num.push(calcu(c1, c2, op.top()));
					op.pop();
				}
				op.pop();
				i++;
			}
			else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
				while (!op.empty() && priority(s[i]) <= priority(op.top())) {
					Complex c2 = num.top();
					num.pop();
					Complex c1 = num.top();
					num.pop();
					num.push(calcu(c1, c2, op.top()));
					op.pop();
				}
				op.push(s[i]);
				i++;
			}
			else i++;
		}
		while (!op.empty()) {
			Complex c2 = num.top();
			num.pop();
			Complex c1 = num.top();
			num.pop();
			num.push(calcu(c1, c2, op.top()));
			op.pop();
		}
		return num.top();
	}

	void display() const {//可能无用
		cout << "\n>>>  结果是：";
		if (real == 0 && imag == 0) {
			cout << 0<<endl;
		}
		else if (real == 0) {
			cout << imag << "i"<<endl;
		}
		else if (imag == 0) {
			cout << real<<endl;
		}
		else {
			cout << real << "+" << imag << "i"<<endl;
		}
	}

	//析构
	~Complex() {};
	
};

#endif
