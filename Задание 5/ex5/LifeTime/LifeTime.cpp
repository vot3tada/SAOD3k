#include <iostream>
#include "Test.h"
#include "Child.h"

using namespace std;
int Test::nCount = 0;
Test test;
void foo(Test t)
{
	cout << "foo is running" << endl;
}
int main()
{
	Test t;
	Child ch;
	Test* p = new Test;
	delete p;
	
	Test* arr = new Test[5];
	
	delete [] arr;
	Test copy = t;

	foo(t);
}
