#include <iostream>
#pragma once

using namespace std;
class Test
{
public:
	int Val = 0;
	Test()
	{
		cout << "Test Start" << endl;
	}
	~Test()
	{
		cout << "Test Finish" << endl;
	}
};

