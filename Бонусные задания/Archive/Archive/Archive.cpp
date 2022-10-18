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

std::vector<Node> arrayOfChar = { Node(0,0),
                                    Node(1,0),
                                    Node(2,0),
                                    Node(3,0),
                                    Node(4,0),
                                    Node(5,0),
                                    Node(6,0),
                                    Node(7,0),
                                    Node(8,0),
                                    Node(9,0),
                                    Node(10,431876),
                                    Node(11,0),
                                    Node(12,0),
                                    Node(13,0),
                                    Node(14,0),
                                    Node(15,0),
                                    Node(16,0),
                                    Node(17,0),
                                    Node(18,0),
                                    Node(19,0),
                                    Node(20,0),
                                    Node(21,0),
                                    Node(22,0),
                                    Node(23,0),
                                    Node(24,0),
                                    Node(25,0),
                                    Node(26,0),
                                    Node(27,0),
                                    Node(28,0),
                                    Node(29,0),
                                    Node(30,0),
                                    Node(31,0),
                                    Node(32,46513630),
                                    Node(33,285161),
                                    Node(34,1569687),
                                    Node(35,208839),
                                    Node(36,10620),
                                    Node(37,70553),
                                    Node(38,35055),
                                    Node(39,297776),
                                    Node(40,784147),
                                    Node(41,784326),
                                    Node(42,971939),
                                    Node(43,24708),
                                    Node(44,2500845),
                                    Node(45,1985767),
                                    Node(46,2664077),
                                    Node(47,148982),
                                    Node(48,2290060),
                                    Node(49,2651441),
                                    Node(50,1910173),
                                    Node(51,827228),
                                    Node(52,713335),
                                    Node(53,746264),
                                    Node(54,685466),
                                    Node(55,702983),
                                    Node(56,805408),
                                    Node(57,1548901),
                                    Node(58,1243622),
                                    Node(59,255452),
                                    Node(60,3104),
                                    Node(61,2893320),
                                    Node(62,9974),
                                    Node(63,453600),
                                    Node(64,697),
                                    Node(65,1370361),
                                    Node(66,875223),
                                    Node(67,1948312),
                                    Node(68,685965),
                                    Node(69,553503),
                                    Node(70,713226),
                                    Node(71,565744),
                                    Node(72,704223),
                                    Node(73,800363),
                                    Node(74,490317),
                                    Node(75,337680),
                                    Node(76,658156),
                                    Node(77,1014806),
                                    Node(78,571688),
                                    Node(79,454998),
                                    Node(80,845636),
                                    Node(81,45330),
                                    Node(82,795552),
                                    Node(83,1443561),
                                    Node(84,1193800),
                                    Node(85,309242),
                                    Node(86,262426),
                                    Node(87,483386),
                                    Node(88,31793),
                                    Node(89,137128),
                                    Node(90,59183),
                                    Node(91,9971),
                                    Node(92,24471),
                                    Node(93,10077),
                                    Node(94,3669),
                                    Node(95,195380),
                                    Node(96,6148),
                                    Node(97,18778626),
                                    Node(98,3072188),
                                    Node(99,6297430),
                                    Node(100,6718406),
                                    Node(101,24731371),
                                    Node(102,3922083),
                                    Node(103,4675727),
                                    Node(104,8003149),
                                    Node(105,15360907),
                                    Node(106,225706),
                                    Node(107,1524676),
                                    Node(108,8977289),
                                    Node(109,5017290),
                                    Node(110,15048400),
                                    Node(111,15190030),
                                    Node(112,3893272),
                                    Node(113,135533),
                                    Node(114,14454592),
                                    Node(115,12926655),
                                    Node(116,16101232),
                                    Node(117,5221917),
                                    Node(118,1913467),
                                    Node(119,2777450),
                                    Node(120,537312),
                                    Node(121,3959774),
                                    Node(122,372429),
                                    Node(123,48684),
                                    Node(124,5807639),
                                    Node(125,55784),
                                    Node(126,2445),
                                    Node(127,0) };

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
    fout.close();
}
void Compress(std::string nameInFile, std::string nameOutFile)
{
    using namespace std;
    const size_t len = 50000;
    float filesize = 0;
    ifstream fin(nameInFile, ios::in);
    //Для получения нового массива чаров
    //list<future<std::vector<Node>>> queue1;
    int i = 0;
    while (!fin.fail())
    {
        char* text = new char[len];
        fin.read(text, len);
        //queue1.push_front(std::async(std::launch::async, GetArrayOfChar, text, len));
        filesize += len;
    }
    fin.close();
    /*if (queue1.empty()) return;
    auto arrayOfChar = queue1.back().get();
    queue1.pop_back();
    while (!queue1.empty())
    {
        auto array = queue1.back().get();
        for (i = 0; i < arrayOfChar.size(); i++) arrayOfChar[i].count += array[i].count;
        queue1.pop_back();
    }
    for (int i = 0; i < 128; i++) cout <<"Node(" << i << ',' << arrayOfChar[i].count <<")," << endl;*/
    auto tree = GetTree(arrayOfChar);
    std::unordered_map<char, std::string> map = TreeToMapC(&tree);
    fin.open(nameInFile, ios::in);
    float outsize = 0;
    bool stop = false;
    list<future<void>> status;
    list<future<string>> queue2;
    //status.push_front(std::async(std::launch::async, StatusBar, &filesize, &outsize));
    status.push_front(std::async(std::launch::async, ThreadWriter, &queue2, nameOutFile, &stop));
    while (!fin.fail())
    {
        char* text = new char[len];
        fin.read(text, len);
        outsize += len;
        queue2.push_back(std::async(std::launch::async, Code, text, len));
    }
    stop = true;
    status.front().get();
    status.clear();
    queue2.clear();
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
    fin.open(nameInFile, ios::in | ios::binary);
    ofstream fout(nameOutFile, std::ios_base::out);
    string buf = "";
    //list<future<void>> queue3;
    //queue3.push_front(std::async(std::launch::async, StatusBar, &filesize, &outsize));
    //while (!fin.fail())
    //{
        std::bitset<8> byte;
        //char text[len];
        //fin.read(text, len);
        for (int i = 0; i < text.size(); i++)
        {
            byte = text[i];
            //if (text[i] == -52) continue;
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
    auto tree = GetTree(arrayOfChar);
    mapC = TreeToMapC(&tree);
    mapD = TreeToMapD(&tree);
    Compress("engwiki_ascii.txt", "engwiki.compressed");
    Decompress("engwiki.compressed", "out.txt");
}
