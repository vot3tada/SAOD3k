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
    for (int i = 1; i < sub.size(); i++) {
        int j = pi[i - 1];
        while (j > 0 && sub[i] != sub[j])
            j = pi[j - 1];
        if (sub[i] == sub[j])
            j++;
        pi[i] = j;
    }
    for (int k = 0, i = 0; i < str.size(); ++i)
    {
        while (k > 0 && sub[k] != str[i]) k = pi[k - 1];
        if (sub[k] == str[i]) k++;
        if (k == sub.size()) return i - sub.size() + 1;
    }
    return std::string::npos;
}
using namespace std;
vector<size_t> prefix(const string& s)
{

    size_t n = s.length();
    vector<size_t> len(n);

    for (size_t i = 1; i < n; i++)
    {

        size_t j = len[i - 1];

        while (j > 0 && s[i] != s[j])
            j = len[j - 1];

        if (s[i] == s[j])
            j++;

        len[i] = j;
    }
    return len;
}

size_t KMP2(const string& T, const string& t)
{
    size_t index = string::npos;
    size_t Tn = T.length();
    size_t tn = t.length();
    vector<size_t> f = prefix(t);
    size_t j = 0;
    for (size_t i = 0; i < Tn; i++)
    {
        while (j > 0 && T[i] != t[j])
            j = f[j - 1];
        if (T[i] == t[j])
            ++j;
        if (j == tn)
        {
            index = i - tn + 1;
            break;
        }
    }
    return index;
}

size_t bm(const std::string& str, const std::string& sub)
{
    int badchar[256];

    for (int i = 0; i < 256; i++)
        badchar[i] = -1;
    for (int i = 0; i < sub.size(); i++)
        badchar[(int)sub[i]] = i;
    int s = 0;
    while (s <= (str.size() - sub.size()))
    {
        int j = sub.size() - 1;
        while (j >= 0 && sub[j] == str[s + j])
            j--;
        if (j < 0)
        {
            return s;
            //s += (s + sub.size() < str.size()) ? sub.size() - badchar[str[s + sub.size()]] : 1;
        }
        else
            s += max(1, j - badchar[str[s + j]]);
    }
    return s;
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
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
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
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
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
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nkmp2\n";
    for (size_t i = 0; i < n; i++)
    {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = KMP2(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
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
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << indx[i] << '\t' << times[i] << endl;
    }
}
