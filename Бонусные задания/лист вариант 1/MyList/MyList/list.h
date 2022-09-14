#include <iostream>
#pragma once
template <typename T>
class List
{
	private:
		size_t length = 0;
		struct Node
		{
		public:
			T value;
			Node* link = nullptr;
			Node()
			{}
			Node(T value)
			{
				this->value = value;
			}
			Node(T value, Node& link)
			{
				this->value = value;
				this->link = &link;
			}
			~Node()
			{}
		};
		Node start;
	public:
		List()
		{
			
		}
		~List()
		{}
		void PushBack(T value)
		{
			length++;
			Node *node = &start;
			while (node->link != nullptr) node = node->link;
			node->link = new Node(value);
		}
		void PushFront(T value)
		{
			length++;
			start.link = new Node(value, *start.link);
		}
		void PopBack()
		{
			if (start.link == nullptr) return;
			length--;
			Node* nodePrevious = &start;
			Node* node = nodePrevious->link;
			while (node->link != nullptr)
			{
				nodePrevious = node;
				node = node->link;
			}
			nodePrevious->link = nullptr;
			delete node;
		}
		void PopFront()
		{
			if (start.link == nullptr) return;
			length--;
			Node* node = start.link;
			start.link = node->link;
			delete node;
		}
		void Insert(size_t index, T value)
		{
			if (!index)
			{
				start.link = new Node(value, *start.link);
				return;
			}
			if (start.link == nullptr) throw std::invalid_argument("Out of range");
			Node* node = start.link;
			for (int i = 0; i < index - 1; i++)
			{
				if (node->link == nullptr) throw std::invalid_argument("Out of range");
				node = node->link;
			}
			node->link = new Node(value, *node->link);
			length++;
		}
		void RemoveAt(size_t index)
		{
			if (start.link == nullptr) throw std::invalid_argument("Out of range");
			Node* node = start.link;
			for (int i = 0; i < index - 1; i++)
			{
				if (node->link == nullptr) throw std::invalid_argument("Out of range");
				node = node->link;
			}
			Node* nodePrevious = node;
			node = node->link;
			nodePrevious->link = node->link;
			delete node;
			length--;
		}
		T& operator[](const size_t index)
		{
			if (start.link == nullptr) throw std::invalid_argument("Out of range");
			Node* node = start.link;
			for (int i = 0; i < index; i++)
			{
				if (node->link == nullptr) throw std::invalid_argument("Out of range");
				node = node->link;
			}
			return node->value;
		}
		/*T const& operator[](const size_t index)
		{
			if (start.link == nullptr) throw std::invalid_argument("Out of range");
			Node* node = start.link;
			for (int i = 0; i < index; i++)
			{
				if (node->link == nullptr) throw std::invalid_argument("Out of range");
				node = node->link;
			}
			return &node->value;
		}*/
		size_t Size() const
		{
			return length;
		}
		bool Empty()
		{
			return !length;
		}
		void Clear()
		{
			Node* nodePrevious = &start;
			Node* node = nodePrevious->link;
			while (node->link != nullptr)
			{
				nodePrevious = node;
				node = node->link;
				delete nodePrevious;
			}
			start.link = nullptr;
			delete node;
			length = 0;
		}
		T Front() const
		{
			if (start.link == nullptr) throw std::invalid_argument("Out of range");
			return start.link->value;
		}
		T back() const
		{
			if (start.link == nullptr) throw std::invalid_argument("Out of range");
			Node* node = &start;
			while (node->link != nullptr) node = node->link;
			return node->value;
		}
};

