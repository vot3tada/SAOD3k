#include <iostream>
#include <list>
#include <vector>
#include <Windows.h>
using namespace std;

int main()
{
    /*int N = 200, M = 200;
    list<int> numbers(N);
    int i = 1;
    for (auto iter = numbers.begin(); iter != numbers.end(); *iter++ = i++);
    for (int n : numbers)
        cout << n << " ";
    cout << endl;
    int k = 0;
    LARGE_INTEGER li1, li2, lif;
    ::QueryPerformanceFrequency(&lif);
    ::QueryPerformanceCounter(&li1);
    for (int i = 0; i < M; i++)
    {
        numbers.emplace_front(i);
        k++;
        numbers.pop_front();
        k++;
    }
    ::QueryPerformanceCounter(&li2);
    int mcSec = (int)((double)((li2.QuadPart - li1.QuadPart) * 1000000) / (double)lif.QuadPart);
    cout << k << endl;
    cout << mcSec << endl;*/
    int M = 200;
    for (int N = 0; N <= 1200; N += 200)
    {
        list<int> numbers(N);
        int i = 1;
        for (auto iter = numbers.begin(); iter != numbers.end(); *iter++ = i++);
        int k = 0;
        LARGE_INTEGER li1, li2, lif;
        ::QueryPerformanceFrequency(&lif);
        ::QueryPerformanceCounter(&li1);
        for (int i = 0; i < M; i++)
        {
            numbers.insert(numbers.cbegin(), i);
            k++;
            numbers.erase(numbers.cbegin());
            k++;
        }
        ::QueryPerformanceCounter(&li2);
        int mcSec = (int)((double)((li2.QuadPart - li1.QuadPart) * 1000000) / (double)lif.QuadPart);
        cout << N / 200 + 1 << "\t";
        //cout << k << "\t";
        cout << mcSec << endl;
    }
    cout << "---------------------" << endl;
    for (int N = 0; N <= 1200; N += 200)
    {
        vector<int> numbers(N);
        int i = 1;
        for (auto iter = numbers.begin(); iter != numbers.end(); *iter++ = i++);
        int k = 0;
        LARGE_INTEGER li1, li2, lif;
        ::QueryPerformanceFrequency(&lif);
        ::QueryPerformanceCounter(&li1);
        for (int i = 0; i < M; i++)
        {
            numbers.insert(numbers.cbegin(), i);
            k++;
            numbers.erase(numbers.cbegin());
            k++;
        }
        ::QueryPerformanceCounter(&li2);
        int mcSec = (int)((double)((li2.QuadPart - li1.QuadPart) * 1000000) / (double)lif.QuadPart);
        cout << N / 200 + 1 << "\t";
        //cout << k << "\t";
        cout << mcSec << endl;
    }
}