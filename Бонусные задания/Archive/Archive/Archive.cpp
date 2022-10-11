#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <fstream>
#include <future>
#include <array>
#include <iterator>
#include <string.h>
#include <bitset>

struct Node
{
    size_t count = 0;
    char key = -1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node()
    { }
    Node(char key, size_t count)
    {
        this->key = key;
        this->count = count;
        left = nullptr;
        right = nullptr;
    }
    ~Node()
    { }
};

Node GetTree(std::vector<Node> arrayOfChar)
{
    std::list<Node> queue;
    sort(arrayOfChar.begin(), arrayOfChar.end(), [](Node a, Node b) {return a.count > b.count; });
    for (int k = 0; arrayOfChar[k].count != 0 && k < 128; k++) queue.push_front(Node(arrayOfChar[k].key, arrayOfChar[k].count));
    while (queue.size() > 1)
    {
        Node* l = new Node(queue.front());
        queue.pop_front();
        Node* r = new Node(queue.front());
        queue.pop_front();
        Node root;
        root.count = l->count + r->count;
        root.left = l;
        root.right = r;
        queue.push_front(root);
        queue.sort([](Node a, Node b) {return a.count < b.count; });
    }
    return Node(queue.front());
}
std::vector<Node> GetArrayOfChar(char* text, const size_t len)
{
    std::vector<Node> ACII(128);
    for (int i = 0; i < 128; ACII[i++].key = i);
    for (int i = 0; i < len; i++)
    {
        if (text[i] - 1 < 0) break;
        ACII[text[i] - 1].count++;
    }
    return ACII;
}
void Gorshok(Node* subTree, std::string code, std::unordered_map<char, std::string>& map)
{
    if (subTree->left != nullptr) Gorshok(subTree->left, code + "0", map);
    if (subTree->right != nullptr) Gorshok(subTree->right, code + "1", map);
    if (subTree->key != -1) map.insert({ subTree->key,code });
    return;
}
std::unordered_map<char, std::string> TreeToMap(Node* tree)
{
    std::unordered_map<char, std::string> map;
    Gorshok(tree,"", map);
    return map;
}
std::string Code(char* text, std::unordered_map<char, std::string>& map, const size_t len)
{
    std::string code = "";
    for (int i = 0; i < len; i++)
    {
        if (text[i] < 0) break;
        code += map[text[i]];
    }
    delete[] text;
    return code;
}
std::string MakeCode(unsigned aTaskID, std::unordered_map<char, std::string> map)
{
    return " ";
}
//auto tree = GetTree(arr);
    //std::unordered_map<char, std::string> map = TreeToCode(&tree);
    //return Code(text, map, len);
std::vector<Node> MakeArray(unsigned aTaskID, char* text, const size_t len)
{
    return GetArrayOfChar(text, len);
}
void Compress(std::string nameInFile, std::string nameOutFile)
{
    using namespace std;
    const size_t len = 50000;
    int size = 0;
    ifstream fin(nameInFile, ios::in);
    list<future<std::vector<Node>>> queue1;
    int i = 0;
    while (!fin.fail())
    {
        char* text = new char[len];
        fin.read(text, len);
        queue1.push_front(std::async(std::launch::async, MakeArray,i++, text, len));
        size += len;
    }
    cout << size;
    i = 0;
    fin.close();
    if (queue1.empty()) return;
    auto arrayOfChar = queue1.back().get();
    queue1.pop_back();
    while (!queue1.empty())
    {
        auto array = queue1.back().get();
        for (i = 0; i < arrayOfChar.size(); i++)
        {
            arrayOfChar[i].count += array[i].count;
        }
        queue1.pop_back();
    }
    auto tree = GetTree(arrayOfChar);
    list<future<std::string>> queue2;
    std::unordered_map<char, std::string> map = TreeToMap(&tree);
    fin.open(nameInFile, ios::in);
    ofstream fout(nameOutFile, std::ios_base::out | std::ios_base::binary);
    while (!fin.fail())
    {
        char* text = new char[len];
        fin.read(text, len);
        auto str = Code(text, map, len);
        for (int i = 0; i < str.size(); i+=8)
        {
            char s[] = "00000000";
            int bite = 0;
            if (str.size() - i < 8) bite = 8 - (str.size() - i);
            if (bite != 0) for (bite; bite < 8; bite++) s[bite] = str[i];
            else for (bite; bite < 8; bite++) s[bite] = str[i + bite];
            std::bitset<8> code {s};
            fout << code;
        }
    }
    fin.close();
    fout.close();
}
int main()
{
    Compress("engwiki_ascii.txt", "out.compressed");
}
