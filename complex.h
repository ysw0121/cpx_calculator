//复数Complex类
//后面加 const表示函数不可以修改class的成员


#ifndef CPX
#define CPX
#include <iostream>
#include<cmath>
#include<stack>
#include<vector>
#include<string>
#include<cstdlib>
#include<cctype>
#include <stdexcept>
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
		try {
			if (r== 0)throw runtime_error("错误：除数不能为0");
		}
		catch (runtime_error err) {
			printf("\n\033[1;4;5;31m%s\033[0m", err.what());
			cout << endl;
			return Complex(INFINITY,INFINITY);
		}
		Complex res = Complex((real * c.real + imag * c.imag) / r, (imag * c.real - real * c.imag) / r);
		return res;
	}
	bool operator==(Complex& c)const {
		if (c.real == real && c.imag == imag)return true;
		else return false;
	}
	friend ostream &operator<<(ostream& out,const Complex&c){
		out << "\n>>>  结果是：";
		if (c.imag == 0)out <<c. real;
		else if (c.real == 0)out << c.imag << "i";
		else if (c.imag > 0&&c.real!=0)out <<c.real << "+" << c.imag << "i";
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
	Complex operator^(Complex c) {
		double m = module();
		double a = arg();
		double n = c.real;
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
			return c1.operator^(c2);
		}
		else if (op == 'm') {
			return Complex(c1.module(), 0);
		}
		/*else if (op == 'i') {
			return Complex(0, 1);
		}*/
		else if (op == 'a') {
			return Complex(c1.arg(),0);
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
			case'm':i=4; break;
			default:i = -1; break;
		}
		return i;
	}
	bool isoperator(char c) {
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'a' || c == 'c' || c == 'm' || c == '(' || c == ')')return 1;
		else return 0;
	}
	//逆波兰运算
	Complex calculate(string s) {
		stack<char>op;
		stack<Complex> num;
		for (int i = 0; i <s.size();i++) {
				if (isdigit(s[i])) {
					string str;
					while (isdigit(s[i]) || s[i] == '.') {
						str += s[i];
						i++;
					}
					double d = atof(str.c_str());
					//if(s[0]=='-')d=-d;
					if (i < s.size()) {
						if (s[i] != 'i')num.push(Complex(d, 0));
						else if (s[i] == 'i')num.push(Complex(0, d));
					}
					else num.push(Complex(d, 0));//末尾进去

				}
				if (i < s.size() && i>0) {
					if (s[i] == 'i' && !isdigit(s[i - 1])) {
						num.push(Complex(0, 1));
					}
				}
				if (i == 0 && s[i] == 'i')num.push(Complex(0, 1)), i++;
				if (isoperator(s[i])) {//应该不要边读取边处理，有待修改
					if (num.size() >= 2) {
						if (priority(s[i])<=priority(op.top())) {
							if (op.top() != '(' && op.top() != ')') {
								Complex c1 = num.top();
								//cout << c1;
								num.pop();
								Complex c2 = num.empty()?Complex(0,0):num.top();
								//cout << c2;
								num.pop();
								Complex c3 = calcu(c2, c1, op.top());
								num.push(c3);
								op.pop();
							}
							else if (op.top() == ')') {
								
								while (op.top() != '(') {
									if(op.top()==')')op.pop();
									Complex c1 = num.top();
									//cout << c1;
									num.pop();
									Complex c2 = num.empty() ? Complex(0, 0) : num.top();
									//cout << c2;
									num.pop();
									Complex c3 = calcu(c2, c1, op.top());
									num.push(c3);
									op.pop();
								}
								if(op.top() == '(')op.pop();
							}
						}
					}
					op.push(s[i]);
				}
		}

	//最后的处理
			while(!op.empty()) {
				//if (priority(op.top()) == 1 || priority(op.top()) == 2 || priority(op.top()) == 3) {
				if (op.top() != '(' && op.top() != ')') {
					Complex c1 = num.top();
					//cout << c1;
					num.pop();
					Complex c2 = num.top();
					//cout << c2;
					num.pop();
					Complex c3 = calcu(c2, c1, op.top());
					num.push(c3);
					op.pop();
					//}
				}
				else if (op.top() == ')') {
					op.pop();
					while (op.top() != '(') {
						Complex c1 = num.top();
						//cout << c1;
						num.pop();
						Complex c2 = num.top();
						//cout << c2;
						num.pop();
						Complex c3 = calcu(c2, c1, op.top());
						num.push(c3);
						op.pop();
					}
					if (op.top() == '(')op.pop();
				}
				else if(op.top()=='(') op.pop();
			}
		
	return num.top();
	}

	//可能无用
	void display() const {
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
