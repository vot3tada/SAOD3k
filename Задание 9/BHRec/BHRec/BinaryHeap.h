#pragma once
#include <vector>
#include <exception>

class BinaryHeap
{
private:
	std::vector<int> heap;
	void Swap(int &a, int &b)
	{
		int c = a;
		a = b;
		b = c;
	}
	void FixHeap(int index, int length)
	{
		int left = 2 * index, right = left + 1, largest;
		if (left < length && heap[left] > heap[index])
			largest = left;
		else
			largest = index;
		if (right <= length && heap[right] > heap[largest])
			largest = right;
		if (largest != index)
		{
			Swap(heap[index], heap[largest]);
			FixHeap(largest, length);
		}
	}
	void BuildHeap()
	{
		int len = heap.size();
		for (int i = len / 2; i >= 0; i--)
			FixHeap(i, len);
	}
public:
	BinaryHeap(const int arr[], int n) : heap(n)
	{
		heap = std::vector<int>(n);
		for (int i = 0; i < n; heap[i] = arr[i++]);
		BuildHeap();
	}
	~BinaryHeap()
	{}
	operator int() const
	{
		return heap.size();
	}
	int operator [] (int i)
	{
		if (i < 0 || i >= heap.size()) throw std::out_of_range("Index out of range");
		return heap[i];
	}
};

