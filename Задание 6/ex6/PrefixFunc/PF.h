#include <iostream>
#pragma once

using namespace std;

class PF
{
	private:
		void Init(const char* s)
		{
			n = strlen(s);
			pv = new int[n];
			*pv = 0;
			for (int i = 1; i < n; i++)
			{
				int k = pv[i - 1];
				while (k > 0 && s[i] != s[k]) { k = pv[k - 1]; cmpCount++;}
				if (s[i] == s[k]) k++;
				pv[i] = k;
			}
		}
	public:
		int* pv;
		int n;
		int cmpCount;
		PF(const char* s)
		{
			cmpCount = 0;
			Init(s);
		}
		~PF()
		{
			delete[] pv;
		}
		
		operator int() const
		{
			return n;
		}
		int operator [] (int i) const
		{
			if (i >= n || i < 0) throw out_of_range("Index out of range");
			return *(pv + i);
		}
		int CmpCount()
		{
			return cmpCount;
		}
};

