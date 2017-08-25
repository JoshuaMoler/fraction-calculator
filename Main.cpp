
#include <iostream>
class Fraction {
private:
	int m_num;
	int m_den;
	int gcd(int a, int b) {
		return (b == 0) ? (a > 0 ? a : -a) : gcd(b, a % b);
	}
public:

	Fraction() {}

	Fraction(int num, int den) :m_num{ num }, m_den{ den } {
		reduce();
	}
	void reduce() {
		int devisor = gcd(m_num, m_den);
		m_num = m_num / devisor;
		m_den = m_den / devisor;
	}
	void print() {
		std::cout << m_num << "/" << m_den << '\n';
	}

	friend  Fraction operator*(Fraction &f1, Fraction &f2);
	friend  Fraction operator*(Fraction &f1, int x);
	friend  Fraction operator*(int x, Fraction &f1);
	friend  Fraction operator+(Fraction &f1, Fraction &f2);
	friend  Fraction operator+(Fraction &f1, int x);
	friend  Fraction operator+(int x, Fraction &f1);
	friend  Fraction operator-(Fraction &f1, Fraction &f2);
	friend  Fraction operator-(Fraction &f1, int x);
	friend  Fraction operator-(int x, Fraction &f1);
	friend  Fraction operator/(Fraction &f1, Fraction &f2);
	friend  Fraction operator/(Fraction &f1, int x);
	friend  Fraction operator/(int x, Fraction &f1);
	friend std::ostream& operator<< (std::ostream &out, Fraction &f);
	friend std::istream& operator>> (std::istream&in, Fraction &f);
};
class Calc {
private:
	Fraction f1;
	Fraction f2;
	char op;
public:
	friend std::ostream& operator << (std::ostream &out, Calc &c);
	friend std::istream& operator >> (std::istream &in, Calc &c);

};
std::istream& operator >> (std::istream& in, Calc &c) {
	while (true) {
		in >> c.f1;
		in >> c.op;
		in >> c.f2;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Invalid input: input extraction failed.\nPlease enter a valid fractional equation.\n";
		}
		else if (c.op == '+' || c.op == '-' || c.op == '*' || c.op == '/')
			break;
		else
			std::cout << "Invalid input: please enter a valid operator.\n";
	}
	return in;
}
std::ostream& operator << (std::ostream &out, Calc &c) {
	switch (c.op) {
	case '+':
		out << c.f1 << ' ' << c.op << ' ' << c.f2 << " = " << c.f1 + c.f2;
		break;
	case '-':
		out << c.f1 << ' ' << c.op << ' ' << c.f2 << " = " << c.f1 - c.f2;
		break;
	case '/':
		out << c.f1 << ' ' << c.op << ' ' << c.f2 << " = " << c.f1 / c.f2;
		break;
	case '*':
		out << c.f1 << ' ' << c.op << ' ' << c.f2 << " = " << c.f1 * c.f2;
		break;
	}
	return out;
}
std::istream& operator>> (std::istream &in, Fraction &f) {
	char c;
	in >> f.m_num;
	in >> c;
	in >> f.m_den;
	f.reduce();
	return in;
}
std::ostream& operator<< (std::ostream &out, Fraction &f) {
	if (f.m_den == 1)
		out << f.m_num;
	else
		out << f.m_num << "/" << f.m_den;
	return out;
}
Fraction operator/(Fraction &f1, Fraction &f2) {
	return Fraction((f1.m_num*f2.m_den), (f1.m_den*f2.m_num));
}
Fraction operator/(Fraction &f1, int x) {
	return Fraction((f1.m_num), f1.m_den*x);

}
Fraction operator/(int x, Fraction &f1) {
	return Fraction((f1.m_num), f1.m_den*x);

}
Fraction operator-(Fraction &f1, Fraction &f2) {
	return Fraction(((f1.m_num*f2.m_den) - (f2.m_num*f1.m_den)), (f1.m_den * f2.m_den));
}
Fraction operator-(Fraction &f1, int x) {
	return Fraction((f1.m_num - (x * f1.m_den)), f1.m_den);
}
Fraction operator-(int x, Fraction &f1) {
	return Fraction((f1.m_num - (x * f1.m_den)), f1.m_den);
}
Fraction operator+(Fraction &f1, Fraction &f2) {

	return Fraction(((f1.m_num*f2.m_den) + (f2.m_num*f1.m_den)), (f1.m_den * f2.m_den));
}
Fraction operator+(Fraction &f1, int x) {
	return Fraction((f1.m_num + (x * f1.m_den)), f1.m_den);
}
Fraction operator+(int x, Fraction &f1) {
	return Fraction((f1.m_num + (x * f1.m_den)), f1.m_den);
}
Fraction operator*(Fraction &f1, Fraction &f2) {

	return Fraction((f1.m_num*f2.m_num), (f1.m_den*f2.m_den));
}
Fraction operator*(Fraction &f1, int x) {
	return Fraction((f1.m_num*x), f1.m_den);
}
Fraction operator*(int x, Fraction &f1) {
	return Fraction((f1.m_num*x), f1.m_den);
}
int main()
{

	Calc calc;
	Fraction fraction;
	std::cout << "Welcome to the fraction calculator!\nTo reduce, enter \'r\';\nTo preform arithematic, enter \'a\';\nTo exit, enter \'e\'.\n\n";
	char command;
	while (true) {
		std::cin >> command;
		switch (command) {
		case 'r':
		case 'R':
			std::cin >> fraction;
			std::cout << fraction << "\n\n";
			break;
		case 'a':
		case 'A':
			std::cin >> calc;
			std::cout << calc << "\n\n";
			break;
		case 'e':
		case 'E':
			return 0;
			break;
		default:
			std::cout << "Invalid input. Please enter \'r\' or \'a\', followed my an expression, or  \'e\' to exit.\n\n";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			break;
		}
	}



	return 0;
}