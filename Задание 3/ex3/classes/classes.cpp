#include <iostream>
#include "Complex.h"

using namespace std;

int main()
{
    /*Complex c(1, 2), b = 3;
    cout << c << " " << b << endl;*/
    

    /*Complex a(1, 1);
    Complex b(2, 2);
    a = a + b;
    cout << a << endl;
    a = a - b;
    cout << a << endl;
    a = a * b;
    cout << a << endl;
    a = a / b;
    cout << a << endl;*/


    Complex arr[4] = { Complex (1,1),Complex (2,2) ,Complex (3,3) ,Complex (4,4) };
    for (Complex c : arr)
    {
        cout << c << ' ';
    }
    cout << endl;
    Complex v[4]{ 1,2, Complex(2,3) };
    for (Complex c : v)
    {
        cout << c << ' ';
    }
    cout << endl;
    

    /*Complex* pc = new Complex(1,2);
    cout << *pc << endl;
    cout << pc->Re << endl;
    cout << pc->Im << endl;
    delete pc;*/
    

    Complex* pc = new Complex[3];
    cout << pc[1].Re << endl;
    delete [] pc;
}
