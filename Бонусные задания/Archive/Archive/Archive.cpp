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
    sort(ACII.begin(), ACII.end(), [](Node a, Node b) {return a.count > b.count; });
    return ACII;
}
void Gorshok(Node* subTree, std::string code, std::unordered_map<char, std::string>& map)
{
    if (subTree->left != nullptr) Gorshok(subTree->left, code + "0", map);
    if (subTree->right != nullptr) Gorshok(subTree->right, code + "1", map);
    if (subTree->key != -1) map.insert({ subTree->key,code });
    return;
}
std::unordered_map<char, std::string> TreeToCode(Node* tree)
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
    //delete[] text;
    return code;
    //return text;
}
std::string ThreadTask(unsigned aTaskID, char* text,const size_t len)
{
    auto arr = GetArrayOfChar(text, len);
    auto tree = GetTree(arr);
    std::unordered_map<char, std::string> map = TreeToCode(&tree);
    return Code(text, map, len);
}
void Compress(std::string nameInFile, std::string nameOutFile)
{
    using namespace std;
    const size_t len = 50;
    ifstream fin(nameInFile, ios::in);
    ofstream fout(nameOutFile, ios::binary);
    list<future<string>> queue;
    int i = 0;
    while (!fin.fail())
    {
        char* text = new char[len];
        fin.read(text, len);
        queue.push_front(std::async(std::launch::async, ThreadTask,i++, text, len));
    }
    fin.close();
    while (!queue.empty())
    {
        auto& task = queue.back();
        cout << task.get();
        queue.pop_back();
    }
    fout.close();
}
int main()
{
    using namespace std;
    const size_t len = 1000;
    char text[len];
    ifstream f("engwiki_ascii.txt", ios::in);
    while (!f.fail())
    {
        f.read(text, sizeof(text));
    }
    auto arr = GetArrayOfChar(text, len);
    auto tree = GetTree(arr);
    std::unordered_map<char, std::string> map = TreeToCode(&tree);
    cout << Code(text, map, len);
    f.close();
    cout << endl;
    //Compress("engwiki_ascii.txt", "out.compressed");
}
