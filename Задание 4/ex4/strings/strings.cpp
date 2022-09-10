#include <iostream>
#include "str.h"

using namespace std;
void Test(str s) 
{

}
int main()
{
    str s = "123";
    cout << s << endl;
    int len = strlen(s);
    cout << len << endl;
    Test(s);
    cout << s << endl;
    str t;
    t = s;
    t = s = t;
    cout << s << endl;
    s += "321";
    cout << s << endl;
    str a = t + s;
    cout << a << endl;
}