#pragma once
#include <forward_list>
#include <memory>

class Tree
{
	class Node
	{
	public:
		std::forward_list<std::unique_ptr<Node>> nodes;
		char key;
		int count = 0;
		Node()
		{ }
		Node(char key)
		{
			this->key = key;
		}
		~Node()
		{ }
		Node* AddNode(const char key)
		{
			nodes.push_front(std::unique_ptr<Node>(new Node(key)));
			return nodes.front().get();
		}
		Node* FindNode(const char key)
		{
			for (auto& item : nodes) if (item.get()->key == key) return item.get();
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
		int n = strlen(word);
		for (int i = 0; i < n; i++)
		{
			Node* addNode = node->FindNode(word[i]);
			if (addNode == nullptr)
				node = node->AddNode(word[i]);
			else node = addNode;
		}
		if (node->count == 0) size++;
		node->Raise();
	}
	int Find(const char* word)
	{
		Node* node = &root;
		int n = strlen(word);
		for (int i = 0; i < n; i++)
		{
			Node* addNode = node->FindNode(word[i]);
			if (addNode == nullptr) return 0;
			else node = addNode;
		}
		return node->count;
		return 0;
	}
	int Size() const { return size; }
};

