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
        ACII[text[i]].count++;
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
void StatusBar(float* filesize, float* outsize)
{
    using namespace std;
    int out = 0;
    int nout = 0;
    while (out != 100)
    {
        nout = ((*outsize / *filesize) * 100);
        if (out != nout)
        {
            out = nout;
            cout << out << '%' << endl;
        }
    }
}
void Compress(std::string nameInFile, std::string nameOutFile)
{
    using namespace std;
    const size_t len = 50000;
    float filesize = 0;
    ifstream fin(nameInFile, ios::in);
    list<future<std::vector<Node>>> queue1;
    int i = 0;
    while (!fin.fail())
    {
        char* text = new char[len];
        fin.read(text, len);
        queue1.push_front(std::async(std::launch::async, GetArrayOfChar, text, len));
        filesize += len;
    }
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
    float outsize = 0;
    list<future<void>> queue3;
    queue3.push_front(std::async(std::launch::async, StatusBar, &filesize, &outsize));
    int out = 0;
    int nout = 0;
    while (!fin.fail())
    {
        char* text = new char[len];
        fin.read(text, len);
        outsize += len;
        auto str = Code(text, map, len);
        bitset<8> code;
        for (int i = 0; i < str.size(); i++)
        {
            code[7 - (i % 8)] = str[i] == '0' ? 0 : 1;
            if (i % 8 == 7)
            {
                fout << static_cast<char>(code.to_ulong());
                code.reset();
            }
        }
    }
    queue3.clear();
    fin.close();
    fout.close();
}
int main()
{
    /*std::string text;
    std::ifstream fin("engwiki_ascii.txt", std::ios::binary);
    text.append((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();
    auto arr = GetArrayOfChar((char*)text.c_str(), text.size());
    auto tree = GetTree(arr);
    auto map = TreeToMap(&tree);
    auto str = Code((char*)text.c_str(), map, text.size());
    std::bitset<8> code;
    std::ofstream fout("out.compressed", std::ios_base::out | std::ios_base::binary);
    for (int i = 0; i < str.size(); i++)
    {
        code[7 - (i % 8)] = str[i] == '0' ? 0 : 1;
        if (i % 8 == 7)
        {
            fout << static_cast<char>(code.to_ulong());
            code.reset();
        }
    }
    fout.close();*/
    Compress("engwiki_ascii.txt", "out.compressed");
}
