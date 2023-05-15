//复数Complex类
//后面加 const表示函数不可以修改class的成员


#ifndef CPX
#define CPX
//#define debug//断点
#include <iostream>
#include<cmath>
#include<stack>
#include<vector>
#include<string>
#include<cstdlib>
#include<cctype>
#include <stdexcept>
#include<iomanip>
using namespace std;
class Complex{
private:
	double real;
	double imag; 
	
	static int num_of_inte(double r) {
		int cnt = 0;
		while (r > 1) {
			r /= 10;
			cnt++;
		}
		return cnt;
	}

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
			printf("\033[1;4;5;31m%s\033[0m", err.what());
			cout << endl;
			return Complex(NAN,NAN);
		}
		Complex res = Complex((real * c.real + imag * c.imag) / r, (imag * c.real - real * c.imag) / r);
		return res;
	}
	bool operator==(Complex& c)const {
		if (c.real == real && c.imag == imag)return true;
		else return false;
	}

	
	friend ostream &operator<<(ostream& out,const Complex &c){
		if (!isnan(c.real) && !isnan(c.imag)) {
			out << "\n>>>  结果是：";

			if (abs(c.imag) <= 2e-14)out << setprecision(num_of_inte(c.real) + 6) << c.real;
			else if (c.real>2e-14) {
				if (c.imag != 1 && c.imag != -1)out << setprecision(6 + num_of_inte(c.imag)) << c.imag << "i";
				else if (c.imag == 1) out << setprecision(6) << "i";
				else if (c.imag == -1)out << setprecision(6) << "-i";
			}
			else if (c.imag > 2e-14 && c.real> 2e-14) {
				if (c.imag != 1)out << setprecision(6 + num_of_inte(c.real)) << c.real << "+" << setprecision(6 + num_of_inte(c.imag)) << c.imag << "i";
				else out << setprecision(6 + num_of_inte(c.real)) << c.real << "+i";
			}

			else if(c.imag<-2e-14){
				if (c.imag != -1)out << setprecision(6 + num_of_inte(c.real)) << c.real << setprecision(6 + num_of_inte(c.imag)) << c.imag << "i";
				else out << setprecision(6 + num_of_inte(c.real)) << c.real << "-i";
			}
			return out;
		}
		else {
			out << "\n>>>  结果是：";
			out << "NAN";
			return out;
		}
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
		for (int i = 0; i < s.size(); i++) {
			if (isdigit(s[i])) {
				string str;
				while (isdigit(s[i]) || s[i] == '.') {
					str += s[i];
					i++;
				}
				double d = atof(str.c_str());
				if (i < s.size()) {
					if (s[i] != 'i') { num.push(Complex(d, 0)); i--; continue; }
					else if (s[i] == 'i') {
						if (i < s.size() - 1) {
							if (s[i + 1] == '^') {
								num.push(Complex(d, 0)); i--; continue;
							}
							else {
								num.push(Complex(0, d)); continue;
							}
						}
						
					}
				}
				else {
					num.push(Complex(d, 0)); i--; continue;
				}//末尾进去

			}
			if (i < s.size() && i>0) {
				if (s[i] == 'i' && !isdigit(s[i - 1])) {
					num.push(Complex(0, 1));
					continue;
				}
				else if (i<s.size()&&s[i] == 'i' && isdigit(s[i - 1])&&s[i+1]=='^') {
					num.push(Complex(0, 1));
					continue;
				}
				
			}
			if (i == 0 && s[i] == 'i')num.push(Complex(0, 1));
			
			if (isoperator(s[i])) {
				if (op.empty()&&s[i]!='(') { op.push(s[i]); continue; }

				if (priority(s[i]) == 4) { op.push(s[i]); continue; }

				if (s[i] == '(') {
					op.push(s[i]); continue;
				}
				else if (!op.empty() && s[i] != ')' && priority(s[i]) > priority(op.top())) {
					op.push(s[i]); 
					continue;
				}
				else if (!op.empty() && priority(s[i]) <= priority(op.top()) && s[i + 1] != '(' && op.top() != '(') {
					while (!op.empty() && priority(s[i]) <= priority(op.top()) && op.top() != '(') {
						Complex c1 = num.top();
#ifdef debug
						cout << c1;//t
#endif
						num.pop();
						Complex c2 = num.top();
#ifdef debug
						cout << c2;//t
#endif
						num.pop();
						Complex c3 = calcu(c2, c1, op.top());
#ifdef debug
						cout << c3;//t
#endif
						num.push(c3);
						op.pop();
					}
					if (op.empty()) {
						op.push(s[i]);
						continue;
					}
					if (!op.empty() && op.top() == '(')op.push(s[i]);
				}

				else if (!op.empty() && priority(s[i]) <= priority(op.top()) && s[i + 1] != '(' && op.top() == '('&&s[i]!=')') {
					if(s[i]!=')')op.push(s[i]);
					continue;
				}

				else if (i < s.size() - 1 && s[i] != '(' && s[i] != ')' && s[i + 1] == '(')op.push(s[i]);

				//  warning: 此处堆积 ,  (阿门……)

				else if (s[i] == ')') {
					if (!op.empty() && op.top() == '(') {
						op.pop();

						if(!op.empty() && priority(op.top()) == 4) {
							Complex c1 = num.top();
#ifdef debug
							cout << c1;//t
#endif
							num.pop();
							Complex c3 = calcu(c1,c1, op.top());
#ifdef debug
							cout << c3;//t
#endif
							num.push(c3);
							op.pop();
							if (!op.empty() && op.top() == '(') {
								op.pop();
								if (!op.empty() && priority(op.top()) == 4) {
									op.push('(');
									continue;
								}
								else if(((op.empty()))||(!op.empty() && priority(op.top()) != 4)){
									op.push('(');
									continue;
								}
							}
						}
						
					}
					
					else if (!op.empty() && priority(op.top()) < 4) {
					if(!op.empty() && op.top() != '(') {
						Complex c1 = num.top();
#ifdef debug
						cout << c1;//t
#endif
						num.pop();
						Complex c2 = num.top();
#ifdef debug
						cout << c2;//t
#endif
						num.pop();
						Complex c3 = calcu(c2, c1, op.top());
#ifdef debug
						cout << c3;//t
#endif
						num.push(c3);
						op.pop();
					}
				}
					 if (!op.empty() && op.top() == '(') {
						op.pop();
						if (!op.empty() && priority(op.top()) != 4) {
							op.push('(');
							continue;
						}
						if(!op.empty() && priority(op.top()) == 4) {
							Complex c1 = num.top();
#ifdef debug
							cout << c1;//t
#endif
							num.pop();
							Complex c3 = calcu(c1, Complex(0, 1), op.top());
#ifdef debug
							cout << c3;//t
#endif
							num.push(c3);
							op.pop();
							if (!op.empty() && op.top() == '(') {
								op.pop();
								if (!op.empty() && priority(op.top()) == 4) {
									op.push('(');
									continue;
								}
								else if (((op.empty())) || (!op.empty() && priority(op.top()) != 4)){
									op.push('(');
									continue;
								}
							}
						}
					}
				}

				//end-----

			}

		}

	//最后的处理
			while(!op.empty()&&num.size()>=2) {
				if (priority(op.top()) == 1 || priority(op.top()) == 2 || priority(op.top()) == 3) {
					Complex c1 = num.top();
#ifdef debug
cout << c1;
#endif
					num.pop();
					Complex c2 = num.top();
#ifdef debug
cout << c2;
#endif
					num.pop();
					Complex c3 = calcu(c2, c1, op.top());
#ifdef debug
					cout << c3;//t
#endif
					num.push(c3);
					op.pop();

				}
				else if(!op.empty() &&priority(op.top())==4){
					Complex c1 = num.top();
#ifdef debug
cout << c1;
#endif
					num.pop();
					Complex c3 = calcu(c1, c1, op.top());
#ifdef debug
					cout << c3;//t
#endif
					num.push(c3);
					op.pop();
				}
				if(!op.empty()&&op.top()=='(') op.pop();
			}
		
	return num.top();
	}

	bool inf(Complex c) {
		if (c.real == NAN|| c.imag ==NAN)return 1;
		else return 0;
	}

	//析构
	~Complex() {};
	
};

#endif
