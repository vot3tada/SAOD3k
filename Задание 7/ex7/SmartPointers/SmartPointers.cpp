#include <iostream>
#include <memory>
#include "Test.h"

using namespace std;

int main()
{
	//shared_ptr<Test[]> sp(new Test[3]);
	/*shared_ptr<Test> sp(new Test[3], default_delete<Test[]>());
	for (int i = 0; i < 3; i++)
	{
		(sp.get() + i)->Val = i;
		cout << (sp.get() + i)->Val << endl;
	}*/
	unique_ptr<Test[]> p = make_unique<Test[]>(3);
	for (int i = 0; i < 3; i++)
	{
		p[i].Val = i;
		cout << p[i].Val << endl;
	}
	cout << "---------------------" << endl;
	p.reset(new Test[2]);
	cout << "---------------------" << endl;
}