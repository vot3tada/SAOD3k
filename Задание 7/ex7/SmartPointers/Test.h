#include <iostream>
#pragma once

using namespace std;
class Test
{
public:
	int Val;
	Test()
	{
		Val = 0;
		cout << "Test Start" << endl;
	}
	~Test()
	{
		cout << "Test Finish" << endl;
	}
};

