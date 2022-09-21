#include <iostream>
#include "list.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


using namespace std;
void print_lst(List <char> &l) 
{
    for (int i = 0; i < l.Size(); i++)
    {
        cout << l[i] << "\t";
    }
    cout << endl;
}
int main()
{
    List<int> list = {1,2,3,4};
    list.PushFront(11);
    //list.PushBack(10);
    //list.Insert(0, 5);
    //list.Insert(0, 6);
    //list.Insert(1, 7);
    //list.Show();
    //list.RemoveAt(1);
    //list.Show();
    //list.PopBack();
    list.Show();
    //list.PopFront();
    //list.Show();
    //cout << list.Front() << endl;
    //cout << list[1] << endl;
    //list.Clear();
    //List <char> lst = { 5,8,10 }; // ваш список
    //cout << std::boolalpha << lst.Empty() << endl;
    //for (int i = 0; i < 5; i++) lst.PushBack(char('a' + i));
    //print_lst(lst);
    _CrtDumpMemoryLeaks();
}