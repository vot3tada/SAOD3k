#include <iostream>
#include "PF.h"
using namespace std;

int main()
{
	//https://neerc.ifmo.ru/wiki/index.php?title=%D0%9F%D1%80%D0%B5%D1%84%D0%B8%D0%BA%D1%81-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F - о префикс функции...
	/*const char* s = "rakaratrakarakarakatakarakara";
	PF pf = s;*/


	for (int i = 0; i < 5; i++)
	{
		const int N = 25;
		char str[N]{ 0 };
		for (int i = 0; i < N - 1; i++)
			str[i] = rand() % ('e' - 'a') + 'a';
		for (char* p = str; *p; cout << *(++p));
		cout << " " << strlen(str) << endl;
		PF pf = str;
		cout << pf.CmpCount() << endl;
	}
	
}