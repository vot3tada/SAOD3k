#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>

size_t naive(const std::string& str, const std::string& sub)
{
    size_t n = str.size(), m = sub.size(), j = 0;
    for (size_t i = 0; i < n - m + 1; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (str[i + j] != sub[j])
                break;
        }
        if (j == m)
            return i;
    }
    return std::string::npos;
}

size_t kmp(const std::string& str, const std::string& sub)
{
    std::vector<int> pi(sub.size());
    for (int i = 1; i < sub.size() + 1; i++)
    {
        auto z = sub.substr(0, i);
        int k = 0;
        for (int j = 1; j < z.size(); j++)
        {
            auto p = z.substr(0, j);
            auto s = z.substr(z.size() - j, j);
            if (p == s) k = p.size();
        }
        pi[i - 1] = k;
    }
    for (int i = 0; i < str.size(); i++)
    {
        if (str.size() - i < sub.size()) return std::string::npos;
        bool flag = false;
        for (int j = 0; j < sub.size(); j++)
        {
            if (str[i+j] != sub[j])
            {
                flag = true;
                if (j > 1) i += pi[j - 1];
                break;
            }
        }
        if (!flag) return i;
    }
    return std::string::npos;
}

size_t bm(const std::string& str, const std::string& sub)
{
    // ваша быстрая реализация BM
    std::vector<int> pi(sub.size());
    for (int i = 0; i < sub.size() - 1; i++) pi[i] = sub.size() - i - 2;
    pi.back() = sub.size() - 1;
    for (int i = 0; i < str.size(); i++)
    {
        if (str.size() - i < sub.size()) return std::string::npos;
        bool flag = false;
        for (int j = sub.size() - 1; j >= 0; j--)
        {
            if (str[i + j] != sub[j])
            {
                flag = true;
                auto f = find(sub.rbegin(), sub.rend(), str[i + j]);
                if (f != sub.rend()) i += pi[sub.rend() - f - 1];
                else i += pi.back();
                break;
            }
        }
        if (!flag) return i;
    }
    return std::string::npos;
}

int main()
{
    using namespace std;

    string str, sub = "was born in a small town called Sceptre";
    ifstream fin("engwiki_ascii.txt", ios::binary);
    if (!fin.is_open())
    {
        cout << "not open!" << endl;
        return 0;
    }
    str.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());


    size_t n = 10;
    std::vector<size_t> times(n), indx(n);

    cout << "\nstd::find\n";
    for (size_t i = 0; i < n; i++)
    {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = str.find(sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nnaive\n";
    for (size_t i = 0; i < n; i++)
    {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = naive(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nkmp\n";
    for (size_t i = 0; i < n; i++)
    {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = kmp(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nbm\n";
    for (size_t i = 0; i < n; i++)
    {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = bm(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << indx[i] << '\t' << times[i] << endl;
    }
}
