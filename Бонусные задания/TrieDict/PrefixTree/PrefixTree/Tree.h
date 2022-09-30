#pragma once
#include <list>
#include <memory>

class Tree
{
	class Node
	{
	public:
		std::list<Node> nodes;
		char key;
		int count = 0;
		Node()
		{}
		Node(char key)
		{
			this->key = key;
		}
		~Node()
		{ }
		Node* AddNode(const char key)
		{
			nodes.push_front(Node(key));
			return &nodes.front();
		}
		Node* FindNode(const char key)
		{
			for (auto& item : nodes) if (item.key == key) return &item;
			return nullptr;
		}
		void Raise() { count++; }
	};
	Node root;
	int size = 0;
public:
	Tree()
	{ }
	~Tree()
	{ }
	void Insert(const char* word)
	{
		Node* node(&root);
		for (int i = 0; i < strlen(word); i++)
		{
			Node* addNode = node->FindNode(word[i]);
			if (addNode == nullptr) node = node->AddNode(word[i]);
			else node = addNode;
		}
		if (node->count == 0) size++;
		node->Raise();
	}
	int Find(const char* word)
	{
		Node* node = &root;
		for (int i = 0; i < strlen(word); i++)
		{
			Node* addNode = node->FindNode(word[i]);
			if (addNode == nullptr) return 0;
			else node = addNode;
		}
		return node->count;
	}
	int Size() const { return size; }
};

