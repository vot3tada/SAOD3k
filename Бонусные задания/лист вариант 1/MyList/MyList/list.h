#include <iostream>
#include <cassert>      // assert
#include <cstddef>      // ptrdiff_t
#include <iterator>     // iterator
#include <type_traits>  // remove_cv
#include <utility>      // swap


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
			{
				//std::cout << "Node dead " << value << std::endl;
			}
		};		
		Node* start = nullptr;
		Node* iterator = start;
	public:
		List()
		{

		}
		template<typename... Args>
		List(Args... args)
		{
			PushBack(args...);
		}
		~List()
		{
			Clear();
		}

		class Iterator;
		Iterator begin()
		{
			return Iterator(start);
		}
		Iterator end()
		{
			return Iterator(nullptr);
		}
		class Iterator
		{
		public:
			Iterator() noexcept :
				m_pCurrentNode(start) { }

			Iterator(const Node* pNode) noexcept :
				m_pCurrentNode(pNode) { }

			Iterator& operator=(Node* pNode)
			{
				this->m_pCurrentNode = pNode;
				return *this;
			}

			// Prefix ++ overload
			Iterator& operator++()
			{
				if (m_pCurrentNode)
					m_pCurrentNode = m_pCurrentNode->link;
				return *this;
			}

			// Postfix ++ overload
			Iterator operator++(int)
			{
				Iterator iterator = *this;
				++* this;
				return iterator;
			}

			bool operator!=(const Iterator& iterator)
			{
				return m_pCurrentNode != iterator.m_pCurrentNode;
			}

			T operator*()
			{
				return m_pCurrentNode->value;
			}
		private:
			const Node* m_pCurrentNode;
		};

		void PushBack(T value)
		{
			length++;
			if (start == nullptr) {
				start = new Node(value); return;
			}
			Node *node = start;
			while (node->link != nullptr) node = node->link;
			node->link = new Node(value);
			iterator = start;
		}
		template<typename... Args>
		void PushBack(T value, Args... args)
		{
			if constexpr (sizeof...(Args) > 0)
			{
				length++;
				if (start == nullptr) {
					start = new Node(value); return PushBack(args...);
				}
				Node* node = start;
				while (node->link != nullptr) node = node->link;
				node->link = new Node(value);
				return PushBack(args...);
			}
		}
		void PushFront(T value)
		{
			length++;
			if (start == nullptr) {
				start = new Node(value); return;
			}
			start = new Node(value, *start);
			iterator = start;
		}
		void PopBack()
		{
			if (start == nullptr) return;
			length--;
			Node* nodePrevious = start;
			Node* node = nodePrevious->link;
			while (node->link != nullptr)
			{
				nodePrevious = node;
				node = node->link;
			}
			nodePrevious->link = nullptr;
			delete node;
			iterator = start;
		}
		void PopFront()
		{
			if (start == nullptr) return;
			length--;
			Node* node = start;
			start = node->link;
			delete node;
			iterator = start;
		}
		void Insert(size_t index, T value)
		{
			if (start == nullptr) throw std::out_of_range("Out of range");
			
			if (!index)
			{
				start = new Node(value, *start);
				length++;
				return;
			}
			Node* node = start;
			for (int i = 0; i < index - 1; i++)
			{
				if (node->link == nullptr) throw std::out_of_range("Out of range");
				node = node->link;
			}
			node->link = new Node(value, *node->link);
			length++;
		}
		void RemoveAt(size_t index)
		{
			if (start == nullptr) throw std::out_of_range("Out of range");
			Node* node = start;
			for (int i = 0; i < index - 1; i++)
			{
				if (node->link == nullptr) throw std::out_of_range("Out of range");
				node = node->link;
			}
			Node* nodePrevious = node;
			node = node->link;
			nodePrevious->link = node->link;
			delete node;
			length--;
			iterator = start;
		}
		T& operator[](const size_t index)
		{
			if (start == nullptr) throw std::out_of_range("Out of range");
			Node* node = start;
			for (int i = 0; i < index; i++)
			{
				if (node->link == nullptr) throw std::out_of_range("Out of range");
				node = node->link;
			}
			return node->value;
		}
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
			if (start == nullptr) return;
			Node* nodePrevious = start;
			Node* node = nodePrevious->link;
			while (node != nullptr)
			{
				nodePrevious = node;
				node = node->link;
				delete nodePrevious;
			}
			delete start;
			start = nullptr;
			length = 0;
		}
		T Front() const
		{
			if (start == nullptr) throw std::out_of_range("Out of range");
			return start->value;
		}
		T Back() const
		{
			if (start == nullptr) throw std::out_of_range("Out of range");
			Node* node = start;
			while (node->link != nullptr) node = node->link;
			return node->value;
		}
		void Show()
		{
			if (start == nullptr) return;
			Node* node = start;
			while (node != nullptr) {
				std::cout << node->value << "\t";
				node = node->link;
			}
			std::cout << std::endl;
		}
};


