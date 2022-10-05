#include <iostream>
#include "Tree.h"
#include <string>
#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>
#include <fstream>
//#include <cctype> //isalpha

void umap(const std::string& text, std::string word)
{
	using namespace std;
	unordered_map<std::string, size_t> dict;
	string str = "";
	for (const auto& ch : text) // кроме последнего слова
	{
		//if(isalpha(ch) || ch == '\'')
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\'')
			str += ch;
		else if (str.size() > 0)
		{
			++dict[str];
			str = "";
		}
	}
	cout << "\ndict size: " << dict.size() << endl;
	cout << word << ": " << dict[word] << endl;
}
void triedict(const std::string& text, std::string word) 
{ 
	using namespace std;
	Tree dict;
	string str = "";
	for (const auto& ch : text)
	{
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\'')
			str += ch;
		else if (str.size() > 0)
		{
			dict.Insert(str.c_str());
			str = "";
		}
	}
	cout << "\ndict size: " << dict.Size() << endl;
	cout << word << ": " << dict.Find(word.c_str()) << endl;
}

int main()
{
	using namespace std;
	string text;
	ifstream fin("engwiki_ascii.txt", ios::binary);
	if (!fin.is_open())
	{
		cout << "not open!" << endl;
		return 0;
	}
	text.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
	string word = "wiki"; // слово которое ищем
	for (int z = 0; z < 10; z++)
	{
		auto time_one = chrono::steady_clock::now();
		//umap(text, word);
		triedict(text, word);
		auto time_two = chrono::steady_clock::now();
		cout << "umap\t" << chrono::duration_cast<chrono::microseconds>(time_two - time_one).count() / 1e6 << " sec\n";
	}
}


//int main()
//{
//    Tree tree;
//    char str[] = "are they the most fun and these are a fun ";
//    std::string s = "";
//    for (int i = 0; i < strlen(str); i++)
//    {
//        if (str[i] != ' ') s += str[i];
//        else
//        {
//            tree.Insert(s.c_str());
//            s = "";
//        }
//    }
//	for (int i = 0; i < strlen(str); i++)
//	{
//		if (str[i] != ' ') s += str[i];
//		else
//		{
//			std::cout << tree.Find(s.c_str()) << std::endl;
//			s = "";
//		}
//	}
//    std::cout << "===========================================" << std::endl;
//}
