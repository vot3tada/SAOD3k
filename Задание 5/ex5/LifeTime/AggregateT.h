#include <iostream>
#pragma once
using namespace std;

template <typename T>
class AggregateT {
public:
	T my_objTest;
	AggregateT(T obj) : my_objTest(obj)
	{
		cout << "Hi, I'm aggregateT." << endl;
	}
	~AggregateT()
	{ 
		cout << "End of aggregateT" << endl;
	}
};

