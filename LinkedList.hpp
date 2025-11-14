#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	Node *next;
	T data;
	Node(T nodeData, Node *nextNode = nullptr) : data(nodeData), next(nextNode) {};
};

template <typename T>
class LinkedList
{
public:
	// Behaviors
	void printForward() const
	{
		Node<T> *current = this->head;
		if (!current)
			return;
		while (current->next)
		{
			current = current->next;
			std::cout << current->data;
		}
	}
	void printReverse() const
	{
		LinkedList reversedList = LinkedList();
		Node<T> *iter = this->head;
		reversedList.addHead(this->head->data);
		while (iter->next)
		{
			iter = iter->next;
			reversedList.addHead(iter->data);
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node<T> *getHead()
	{
		return this->head;
	}
	const Node<T> *getHead() const
	{
		return this->head;
	}
	Node<T> *getTail()
	{
		return this->tail;
	}
	const Node<T> *getTail() const
	{
		return this->tail;
	}

	// Insertion
	void addHead(const T &data) // may throw std::bad_alloc
	{
		if (!this->head)
		{
			this->head = new Node<T>(data);
			this->tail = this->head;
			return;
		}
		Node<T> *newHead = new Node<T>(data, this->head);
		this->head = newHead;
	}
	void addTail(const T &data)
	{
		if (!this->tail)
		{
			this->tail = new Node<T>(data);
			this->head = this->tail;
			return;
		}
		this->tail->next = new Node<T>(data);
		this->tail = this->tail->next;
	}

	// Removal
	bool removeHead()
	{
		if (!this->head)
			return false;
		if (!this->head->next)
		{
			delete this->head;
			return true;
		}
		Node<T> *newHead = this->head->next;
		delete this->head;
		this->head = newHead;
		return true;
	}
	bool removeTail()
	{
		Node<T> *iter = this->head;
		if (!iter)
		{
			return false;
		}
		while (iter->next)
		{
			iter = iter->next;
		}
		delete iter;
		return true;
	}
	void clear()
	{
		Node<T> *current = this->head;
		while (current->next != nullptr)
		{
			Node<T> *next = current->next;
			delete current;
			count--;
			current = next;
		}
		delete current;
		count--;
	}

	// Operators
	LinkedList<T> &operator=(LinkedList<T> &&other) noexcept
	{

		this->head = other.getHead();
		other.head = nullptr;
		this->tail = other.getTail();
		other.tail = nullptr;
		return this;
	}
	LinkedList<T> &operator=(const LinkedList<T> &rhs)
	{
		Node<T> *externalIter = rhs.getHead();
		if (!externalIter)
		{
			this->head = nullptr;
			this->tail = nullptr;
			return this;
		}
		this->head = new Node<T>(externalIter->data);
		Node<T> *internalIter = this->head;
		while (externalIter->next)
		{
			internalIter->next = new Node<T>(externalIter->data);
			internalIter = internalIter->next;
			externalIter = externalIter->next;
		}
		return this;
	}

	// Construction/Destruction
	LinkedList()
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
	LinkedList(const LinkedList<T> &list)
	{
		Node<T> *externalIter = list.getHead();
		if (!externalIter)
		{
			this->head = nullptr;
			this->tail = nullptr;
			return;
		}
		this->head = new Node<T>(externalIter->data);
		Node<T> *internalIter = this->head;
		while (externalIter->next)
		{
			internalIter->next = new Node<T>(externalIter->data);
			internalIter = internalIter->next;
			externalIter = externalIter->next;
		}
	}
	LinkedList(LinkedList<T> &&other) noexcept
	{
		this->head = other.getHead();
		other.getHead() = nullptr;
		this->tail = other.getTail();
		other.getTail() = nullptr;
	}
	~LinkedList()
	{
		if (!this->head)
		{
			return;
		}
		Node<T> *internalIter = this->head;
		while (internalIter->next)
		{
			Node<T> *prev = internalIter;
			internalIter = internalIter->next;
			delete prev;
		}
		delete internalIter;
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T> *head;
	Node<T> *tail;
	unsigned int count;
};
