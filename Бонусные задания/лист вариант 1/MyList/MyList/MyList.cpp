#include <iostream>
#include "list.h"
#include <numeric>


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
    cout << "--------------------" << endl;
    list.Show();
    cout << list.Size() << endl;
    for (List<int>::Iterator iterator = list.begin();
        iterator != list.end(); iterator++)
    {
        cout << *iterator << " ";
    }
    cout << endl;
    list.Clear();
    cout << "----------------------------" << endl;
    List <int > l = { 3 , 5 , 2 , 7 };
    for (auto i : l) i += 2;
    auto lambda = [&l](int a, int b) { return a + b * 10; };
    cout << accumulate(l.begin(), l.end(), 0, lambda) << "\n";
}