#include <iostream>
#include <cmath>
#include "Complex.h" 
using namespace std;

Complex::Complex()
{
	this->Re = 0;
	this->Im = 0;
}
Complex::Complex(double Re, double Im)
{
	this->Re = Re;
	this->Im = Im;
}
Complex::Complex(double Re)
{
	this->Re = Re;
	this->Im = 0;
}
Complex Complex::operator +(const Complex& c)const
{
	return Complex(Re + c.Re, Im + c.Im);
}
Complex Complex::operator -(const Complex& c)const
{
	return Complex(Re - c.Re, Im - c.Im);
}
Complex Complex::operator *(const Complex& c)const
{
	return Complex(Re * c.Re - Im * c.Im, Re * c.Im + c.Re * Im);
}
Complex Complex::operator /(const Complex & c)const
{
	return Complex((Re * c.Re + Im * c.Im) / (c.Re * c.Re + c.Im * c.Im), (-Re * c.Im + c.Re * Im) / (c.Re * c.Re + c.Im * c.Im));
}
Complex Complex::Conjugate()
{
	Complex c(Re,-Im);
	return c;
}
double Complex::Mod()
{
	return sqrt(Re*Re+Im*Im);
}
double Complex::Arg()
{
	if (!Mod()) return 0;
	if (Re > 0) return atan(Im / Re);
	if (Re < 0) if (Im >= 0) return acos(-1) + atan(Im / Re); else return -acos(-1) - atan(Im / Re);
	if (Im > 0) return acos(0);
	return -acos(0);
}





