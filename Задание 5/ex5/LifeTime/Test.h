#include <iostream>
#pragma once
using namespace std;
class Test
{
	
public:
	static int nCount;
	Test();
	Test(const Test& t);
	~Test();
};

