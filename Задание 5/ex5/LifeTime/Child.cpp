#include "Child.h"
Child::Child()
{
	nCount++;
	cout << "Child: I'm " << nCount << " and I'm alive" << endl;
}
Child::Child(const Child& t)
{
	nCount++;
	*this = t;
	cout << "Child: I'm " << nCount << ", I'm alive and I'm copy" << endl;
}
Child::~Child()
{
	nCount--;
	cout << "Child: I'm died. Number of my brothers: " << nCount << endl;
}