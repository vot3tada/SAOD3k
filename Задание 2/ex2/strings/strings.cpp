#include <iostream>
#include "utils.h"
using namespace std;


int main()
{
    char str[] = "Hello!";
    cout << str << endl;
    cout << strlen(str) << ' ' << sizeof(str) << endl;
    
    char t[32];
    Copy(t, str);
    cout << t << endl;
    
    char tt[32];
    
    char* pd = tt, * ps = str;
    for (char* pd = tt, *ps = str; *(pd);)
    {
        *pd++ = *ps++;
    }
    cout << tt << endl;
    cout << Len(str) << endl;
    cout << Compare(tt,str) << endl;

}
