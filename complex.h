//复数Complex类
//后面加 const表示函数不可以修改class的成员

/*➢支持的数据类型
1、复数：a + bi （a , b均为实数）
2、实数：a
3、纯虚数：bi
支持的操作符  括弧、负号  “+”，“-”，“×”，“÷”, “||”（加，减，乘，除，取模）
共轭(cjg(Z))
辐角主值(arg(Z))
n次幂
cjg(Z)就是求复数Z的共轭
arg(Z)就是求复数Z的辐角主值，范围为（-𝜋 − 𝜋]
Z^n就是求复数Z的n次幂(n为整数)*/

/*• 怎么样算是合法的输入
• 输入表达式开头结尾
• 以实数、“|”(取模)、负号、”i”或者左括弧开头，以实数、“|”(取模)、“i”或者右括弧结尾
• 操作符（加减乘除）
• 后面可以是实数、“i”、“|”、左括弧，不能是右括弧或者操作符（加减乘除）
(1+3i) , i+3 , -3+4i , |3+4i|   正确
• 实数
• 后面可以是右括弧、“i”、操作符（加减乘除）、“^”，不能是左括弧、“|”或者实数
如  1+-4+)+9-0   错
(2i+3)+8(2+3|4i|)错     */


/*• i
• 前面可以加减乘除、实数、右括号(括号内的结果必须是实数)
• 后面可以是右括弧、操作符（加减乘除）不能是左括弧、”i”、“|”或者实数
• 左括弧
• 后面可以是左括弧、实数、“i”，”|”，不可以是右括弧或者加减乘除
• 右括弧
• 后面可以是右括弧，”i”、操作符（加减乘除）、”^”，不可以是左括弧或者实
数
输入（续）
(2+3)i  正确 ， (2+8i)i  错
(2+3i)+i(1+2i)+i|3|+ii    错
(i+3i)+()+(+3)+(|3+4i|)  错
(9+(i+3i))( +(2+3)8+(2+3)i错
*/

/*括弧匹配
◆ 在输入表达式的任意位置 左括弧个数>=右括弧个数
◆ 对于整个输入表达式，左括弧个数=右括弧个数
• 这个符号有点特别 ‘-’
◆ 有时为负号有时为减号
◆ 为负号的情况
1. 位于表达式开头
2. 前面是左括弧
•“i”和“1i”是等同的，都是合法的
• n次幂的求解中，n是整数，可以是正数或负数*/

/*运算符优先级 (高到低）
括弧
负号 ，取模, cjg, arg
N次幂
乘除
加减*/

#ifndef CPX
#define CPX
#include <iostream>
#include<cmath>
#include<stack>
#include<string>
#include<cstdlib>
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
	Complex conj() const {
		return Complex(real, -imag);
	}
	//乘方
	Complex operator^(int n) {
		double m = module();
		double a = arg();
		return Complex(pow(m, n) * cos(a * n), pow(m, n) * sin(a * n));
	}

	Complex calculate(Complex c1, Complex c2,char op) {
		if (op == '+') {
			return c1 + c2;
		}
		else if (op == '-') {
			return c1 - c2;
		}
		else if (op == '*') {
			return c1 * c2;
		}
		else if (op == '/') {
			return c1 / c2;
		}
		/*else if (op == '^') {
			return c1.power(c2.real);
		}*/
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
			return c1.conj();
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
	Complex calcu(string s) {
		stack<Complex>cpxstk;
		stack<char>opstk;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == ' ') {
				continue;
			}
			else if (s[i] == '(') {
				opstk.push(s[i]);
			}
			else if (s[i] == ')') {
				while (opstk.top() != '(') {
					Complex c2 = cpxstk.top();
					cpxstk.pop();
					Complex c1 = cpxstk.top();
					cpxstk.pop();
					char op = opstk.top();
					opstk.pop();
					cpxstk.push(calculate(c1, c2, op));
				}
				opstk.pop();
			}
			else if (s[i] == '+' || s[i] == '-') {
				while (!opstk.empty() && opstk.top() != '(') {
					Complex c2 = cpxstk.top();
					cpxstk.pop();
					Complex c1 = cpxstk.top();
					cpxstk.pop();
					char op = opstk.top();
					opstk.pop();
					cpxstk.push(calculate(c1, c2, op));
				}
				opstk.push(s[i]);
			}
			else if (s[i] == '*' || s[i] == '/') {
				while (!opstk.empty() && (opstk.top() == '*' || opstk.top() == '/')) {
					Complex c2 = cpxstk.top();
					cpxstk.pop();
					Complex c1 = cpxstk.top();
					cpxstk.pop();
					char op = opstk.top();
					opstk.pop();
					cpxstk.push(calculate(c1, c2, op));
				}
				opstk.push(s[i]);
			}
			else if (s[i] == '^') {
				opstk.push(s[i]);
			}
			else {
				string temp;
				while (s[i] >= '0' && s[i] <= '9' || s[i] == '.') {
					temp += s[i];
					i++;
				}
				i--;
				cpxstk.push(Complex(atof(temp.c_str())));
			}

		}
	}

	void display() const {
		if (real == 0 && imag == 0) {
			cout << 0;
		}
		else if (real == 0) {
			cout << imag << "i";
		}
		else if (imag == 0) {
			cout << real;
		}
		else {
			cout << real << "+" << imag << "i";
		}
	}

	//析构
	~Complex() {
		delete this;
	}
	
};

#endif
