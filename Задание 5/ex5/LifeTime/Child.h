#include <iostream>
#include "Test.h"
#pragma once
class Child: Test
{
	public:
		Child();
		Child(const Child& t);
		~Child();
};

