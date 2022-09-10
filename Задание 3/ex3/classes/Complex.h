#include <iostream>
#pragma once
using namespace std;

class Complex
{
	private: 
		
	public:
		double Re, Im;
		Complex();
		Complex(double, double);
		Complex(double);
		inline friend ostream& operator << (std::ostream& o, const Complex& c)
		{
			return o << '(' << c.Re << ", " << c.Im << ')';
		}
		Complex operator +(const Complex& c)const;
		Complex operator -(const Complex& c)const;
		Complex operator *(const Complex& c)const;
		Complex operator /(const Complex& c)const;
		Complex Conjugate();
		double Mod();
		double Arg();
};

