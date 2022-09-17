#pragma once
class RWF
{
private:
	int M;
	int N;
	int* pm;
	std::string s, t;
	void Init(const char* sc, const char* tc)
	{
		s = std::string(sc);
		t = std::string(tc);
		pm = new int[N * M];		
		for (int i = 0; i < N; pm[N*M-1-i] = i++);
		for (int i = 0; i < M; pm[N * (M - i) - 1] = i++);
		for (int i = M - 2; i >= 0; i--)
		{
			for (int j = N - 2; j >= 0; j--)
			{
				int p = s[M - i - 2] == t[N - j - 2] ? 0 : 1;
				pm[N * i + j] = std::min(std::min(pm[N * (i + 1) + j] + 1, pm[N * i + j + 1] + 1), pm[N * (i + 1) + j + 1] + p);
			}
		}
	}
public:
	RWF(int N, int M, const char* sc, const char* tc)
	{
		this->N = N;
		this->M = M;
		Init(sc, tc);
	}
	RWF(const WF&) = delete;
	~RWF()
	{}
	int Rows() const { return N; }
	int Columns() const { return M; }
	int Get(int i, int j) const
	{
		if (i > N || j > M) throw std::out_of_range("Index out of range");
		return pm[N * i + j];
	}
	void Set(int i, int j, int value)
	{
		if (i > N || j > M) throw std::out_of_range("Index out of range");
		pm[N * i + j] = value;
	}
	void Show()
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				std::cout << pm[N * i + j] << "\t";
			}
			std::cout << std::endl;
		}
	}
};

