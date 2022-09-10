#include <iostream>
#include "Test.h"
using namespace std;

Test::Test()
{
	nCount++;
	cout << "Parent: I'm " << nCount << " and I'm alive" << endl;
}
Test::Test(const Test& t)
{
	nCount++;
	*this = t;
	cout << "Parent: I'm " << nCount << ", I'm alive and I'm copy" << endl;
}
Test::~Test()
{
	nCount--;
	cout << "Parent: I'm died. Number of my brothers: "<< nCount << endl;
}