#include <iostream>
#include "BinaryHeap.h"
#include "BinaryHeapOpt.h"
#include <Windows.h>

int main()
{
	const int M = 5, N = 30;
	int arr[N];
	for (int i = 0; i < N; arr[i++] = rand()%N);
	int k = 0;
	LARGE_INTEGER li1, li2, lif;
	::QueryPerformanceFrequency(&lif);
	::QueryPerformanceCounter(&li1);
	for (int i = 0; i < M; i++)
	{
		BinaryHeap heap(arr, N);
		k += heap[0];
	}
	::QueryPerformanceCounter(&li2);
	int mcSec = (int)((double)((li2.QuadPart - li1.QuadPart) * 1000000) / (double)lif.QuadPart);
	std::cout << "time: " << mcSec << std::endl;
	std::cout << "k: " << k << std::endl;
	k = 0;
	::QueryPerformanceFrequency(&lif);
	::QueryPerformanceCounter(&li1);
	for (int i = 0; i < M; i++)
	{
		BinaryHeapOpt heap(arr, N);
		k += heap[0];
	}
	::QueryPerformanceCounter(&li2);
	mcSec = (int)((double)((li2.QuadPart - li1.QuadPart) * 1000000) / (double)lif.QuadPart);
	std::cout << "time: " << mcSec << std::endl;
	std::cout << "k: " << k << std::endl;
}

