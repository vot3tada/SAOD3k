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
    {

    }
    Node(char key, size_t count)
    {
        this->key = key;
        this->count = count;
    }
    ~Node()
    { }
};


std::unordered_map<char, std::string> mapC;
std::unordered_map<std::string, char> mapD;



Node GetTree(std::vector<Node> arrayOfChar)
{
    std::list<Node> queue;
    sort(arrayOfChar.begin(), arrayOfChar.end(), [](Node a, Node b) {return a.count > b.count; });
    for (int k = 0; k < 128; k++) queue.push_front(Node(arrayOfChar[k].key, arrayOfChar[k].count));
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
        //delete l;
        //delete r;
        queue.sort([](Node a, Node b) {return a.count < b.count; });
    }
    return Node(queue.front());
}
void delTree(Node* subTree)
{
    if (subTree->left != nullptr) delTree(subTree->left);
    if (subTree->right != nullptr) delTree(subTree->right);
    delete subTree->left;
    delete subTree->right;
    return;
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
void GorshokC(Node* subTree, std::string code, std::unordered_map<char, std::string>& map)
{
    if (subTree->left != nullptr) GorshokC(subTree->left, code + "0", map);
    if (subTree->right != nullptr) GorshokC(subTree->right, code + "1", map);
    if (subTree->key != -1) map.insert({ subTree->key,code });
    return;
}
void GorshokD(Node* subTree, std::string code, std::unordered_map<std::string, char>& map)
{
    if (subTree->left != nullptr) GorshokD(subTree->left, code + "0", map);
    if (subTree->right != nullptr) GorshokD(subTree->right, code + "1", map);
    if (subTree->key != -1) map.insert({ code,subTree->key });
    return;
}
std::unordered_map<char, std::string> TreeToMapC(Node* tree)
{
    std::unordered_map<char, std::string> map;
    GorshokC(tree,"", map);
    return map;
}
std::unordered_map<std::string, char> TreeToMapD(Node* tree)
{
    std::unordered_map<std::string, char> map;
    GorshokD(tree, "", map);
    return map;
}
std::string Code(char* text, const size_t len)
{
    std::string code = "";
    for (int i = 0; i < len; i++)
    {
        if (mapC.count(text[i]))
            code += mapC[text[i]];
    }
    //delete[] text;
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
void ThreadWriter(std::list<std::future<std::string>>* queue, std::string nameOutFile, bool* stop)
{
    std::ofstream fout(nameOutFile, std::ios_base::out | std::ios_base::binary);
    std::bitset<8> code;
    int j = 0;
    while (!*stop || queue->size() != 0)
    {
        if (queue->size() == 0) continue;
        auto& item = queue->front();
        auto str = item.get();
        for (int i = 0; i < str.size(); i++)
        {
            code[7 - j] = str[i] == '0' ? 0 : 1;
            if (j == 7)
            {
                fout << static_cast<char>(code.to_ulong());
                code.reset();
                j = 0;
            }
            else j++;
        }
        queue->pop_front();
    }
    fout << static_cast<char>(code.to_ulong());
    fout << j;
    fout.close();
}
void Compress(std::string nameInFile, std::string nameOutFile)
{
    using namespace std;
    const size_t len = 50000;
    float filesize = 0;
    ifstream fin(nameInFile, ios::in);
    //Для получения нового массива чаров
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
        for (i = 0; i < arrayOfChar.size(); i++) arrayOfChar[i].count += array[i].count;
        queue1.pop_back();
    }
    Node tree = GetTree(arrayOfChar);
    mapC = TreeToMapC(&tree);
    delTree(&tree);
    string text;
    fin.open(nameInFile, ios::in);
		text.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    float outsize = 0;
    bool stop = false;
    //list<future<void>> status;
    //list<future<string>> queue2;
    //status.push_front(std::async(std::launch::async, StatusBar, &filesize, &outsize));
    //status.push_front(std::async(std::launch::async, ThreadWriter, &queue2, nameOutFile, &stop));
    //while (!fin.fail())
    //{
    //    char* text = new char[len];
    //    fin.read(text, len);
     //   outsize += len;
    //    queue2.push_back(std::async(std::launch::async, Code, text, len));
    //}
    string str = Code((char*)text.c_str(),text.size());
    std::ofstream fout(nameOutFile, std::ios_base::out | std::ios_base::binary);
    for (int i = 0; i < 128; i++)
    {
        fout << arrayOfChar[i].count << " " << endl;
    }
    std::bitset<8> code;
    int j = 0;
		for (int i = 0; i < str.size(); i++)
		{
				code[7 - j] = str[i] == '0' ? 0 : 1;
				if (j == 7)
				{
						fout << static_cast<char>(code.to_ulong());
						code.reset();
						j = 0;
				}
				else j++;
		}
		fout << static_cast<char>(code.to_ulong());
        fout << j;
    fout.close();
    stop = true;
    //status.front().get();
    //status.clear();
    //queue2.clear();
    fin.close();
    
}
void Decompress(std::string nameInFile, std::string nameOutFile)
{
    using namespace std;
    string text;
    const size_t len = 50000;
    float filesize = 0;
    float outsize = 0;
    ifstream fin(nameInFile, ios::in | ios::binary);
    text.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    /*while (!fin.fail())
    {
        char text[len];
        fin.read(text, len);
        filesize += len;
    }*/
    vector<Node> arrayOfChar;
    int start = 0;
    for (int i = 0; i < 128; i++)
    {
        string s = "";
        while (text[start] != ' ') s += text[start++];
        start += 2;
        arrayOfChar.push_back(Node(i, atoi(s.c_str())));
    }
    Node tree = GetTree(arrayOfChar);
    mapD = TreeToMapD(&tree);
    delTree(&tree);
    ofstream fout(nameOutFile, std::ios_base::out);
    string buf = "";
    //list<future<void>> queue3;
    //queue3.push_front(std::async(std::launch::async, StatusBar, &filesize, &outsize));
    //while (!fin.fail())
    //{
        std::bitset<8> byte;
        //char text[len];
        //fin.read(text, len);
        int sizeLastByte = text[text.size() - 1] - '0';
        for (int i = start; i < text.size() - 1; i++)
        {
            byte = text[i];
            if (i == text.size() - 2)
            {
                for (int bite = 0; bite < sizeLastByte; bite++)
                {
                    buf += byte[7 - bite] == 0 ? '0' : '1';
                    if (mapD.count(buf))
                    {
                        //cout << endl << buf << "-" << map[buf] << endl;
                        fout << mapD[buf];
                        buf = "";
                    }
                }
                break;
            }
            for (int bite = 0; bite < 8; bite++)
            {
                buf += byte[7 - bite] == 0 ? '0': '1';
                if (mapD.count(buf))
                {
                    //cout << endl << buf << "-" << map[buf] << endl;
                    fout << mapD[buf];
                    buf = "";
                }
            }
        }
        //outsize += len;
    //}
    //queue3.clear();
}
int main()
{
    Compress("n.txt", "engwiki.compressed");
    Decompress("engwiki.compressed", "out.txt");
}
