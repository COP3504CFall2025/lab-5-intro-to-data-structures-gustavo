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
		Node *current = this->head;
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
		Node *iter = this->head;
		reversedList.addHead(this->head);
		while (iter->next)
		{
			iter = iter->next;
			reversedList.addHead(iter);
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node *getHead()
	{
		return this->head;
	}
	const Node *getHead() const
	{
		return this->head;
	}
	Node *getTail()
	{
		return this->tail;
	}
	const Node *getTail() const
	{
		return this->tail;
	}

	// Insertion
	void addHead(const T &data) // may throw std::bad_alloc
	{
		if (!this->head)
		{
			this->head = new Node(data);
			this->tail = this->head;
			return;
		}
		Node *newHead = new Node(data, this->head);
		this->head = newHead;
	}
	void addTail(const T &data)
	{
		if (!this->tail)
		{
			this->tail = new Node(data);
			this->head = this->tail;
			return;
		}
		this->tail->next = new Node(data);
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
			this->head == nullptr;
			return true;
		}
		Node *newHead = this->head->next;
		delete this->head;
		this->head = newHead;
		return true
	}
	bool removeTail()
	{
		if (!this->tail)
	}
	void Clear()
	{
		Node *current = this->head;
		while (current->next != nullptr)
		{
			Node *next = current->next;
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
		other.getHead() = nullptr;
		this->tail = other.getTail();
		other.getTail() = nullptr;
		return this;
	}
	LinkedList<T> &operator=(const LinkedList<T> &rhs)
	{
		Node *externalIter = list.getHead();
		if (!externalIter)
		{
			this->head = nullptr;
			this->tail = nullptr;
			return;
		}
		this->head = new Node(externalIter->data_);
		Node *internalIter = this->head;
		while (externalIter->next)
		{
			internalIter->next = new Node(externalIter->data);
			internalIter = internalIter->next;
			externalIter = externalIter->next;
		}
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
		Node *externalIter = list.getHead();
		if (!externalIter)
		{
			this->head = nullptr;
			this->tail = nullptr;
			return;
		}
		this->head = new Node(externalIter->data_);
		Node *internalIter = this->head;
		while (externalIter->next)
		{
			internalIter->next = new Node(externalIter->data);
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
		Node *internalIter = this->head;
		while (internalIter->next)
		{
			Node *prev = internalIter;
			internalIter = internalIter->next;
			delete prev;
		}
		delete internalIter;
	}

private:
	// Stores pointers to first and last nodes and count
	Node *head;
	Node *tail;
	unsigned int count;
};
