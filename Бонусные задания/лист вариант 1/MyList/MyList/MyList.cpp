﻿#include <iostream>
#include <iterator>
#include "list.h"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    List<int> list;
    /*list.PushFront(11);
    list.PushBack(10);*/
    list.Insert(0, 5);
    list.Insert(0, 6);
    list.Insert(1, 7);
    list.RemoveAt(1);
    //list.Show();
    //list.PopBack();
    //list.PopFront();
    cout << list.Front() << endl;
    cout << list[1] << endl;
    //list.Clear();
}