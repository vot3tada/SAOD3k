#include <iostream>
#include "list.h"


using namespace std;
int main()
{
    List<int> list = {1,2,3,4};
    list.PushFront(11);
    list.PushBack(10);
    list.Insert(0, 5);
    list.Insert(0, 6);
    list.Insert(1, 7);
    list.Show();
    list.RemoveAt(1);
    list.Show();
    list.PopBack();
    list.Show();
    list.PopFront();
    list.Show();
    list[1] = 0;
    list.Show();
    cout << list.Front() << endl;
    cout << list[1] << endl;
    list.Clear();
}