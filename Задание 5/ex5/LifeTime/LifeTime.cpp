#include <iostream>
#include "Test.h"
#include "Child.h"
#include "Aggregate.h"
#include "AggregateT.h"





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

	Aggregate agr;

	foo(t);
	AggregateT<Test> agrT1 = Test();
	AggregateT<Child> agrT2 = Child();
}
