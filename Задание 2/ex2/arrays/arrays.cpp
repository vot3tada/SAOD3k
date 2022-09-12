#include <iostream>
using namespace std;

//void rotate(int a[], int n) {
//    int x = a[0];
//    for (int i = 1; i < n; i++)
//        a[i - 1] = a[i];
//    a[n - 1] = x;
//}

void rotate(int a[], int n, bool clockwise=false) 
{
    if (!clockwise)
    {
        int x = *a;
        for (int* p = a; p - a < n; *p++ = *(p + 1));
        *(a + 4) = x;
    }
    else {
        int x = *(a + 4);
        for (int* p = a + n - 1; p >= a; *p-- = *(p - 1));
        *a = x;
    }
}


int main()
{
    int a[5]{ 1,2,3,4,5 };
    for (int i = 0; i < 5; i++)
        cout << a[i] << ' ';
    cout << endl;

    rotate(a, 5, 0);

    for (int* p = a; p - a< 5; p++)
        cout << *p << ' ';
    cout << endl;
    return 0;
}
