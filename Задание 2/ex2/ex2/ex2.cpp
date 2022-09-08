﻿#include <iostream>
using namespace std;

void Swap(int &a, int &b)
{
    //По-человечески
   /*
   int c = b;
   int b = a;
   a = c;
   */

   //Сташно не по-человечески
    int* pa = &a, * pb = &b;
    int c = *pb;
    *pb = *pa;
    *pa = c;
}

//void Swap(int* pa, int* pb)
//{
//    int c = *pb;
//    *pb = *pa;
//    *pa = c;
//}

int main()
{
    //int x = 3;
    //int* p = &x;
    //cout << x << ' ' << *p << ' ' << p << endl;
    //p++; 
    //cout << p << endl;
    //cout << p - &x << endl;

    //typedef unsigned char byte; 	// Нет встроенного byte
    //byte* pb = (byte*)--p;		// вернули указатель на x и преобразовали
    //for (byte* pt = pb; pt - pb < sizeof(int); pt++)
    //    cout << (int)*pt << ' ';	// выводим как int
    //cout << endl;
    
    int a = 3, b = 5;
    Swap(a, b);
    cout << a << " " << b << endl;
}
