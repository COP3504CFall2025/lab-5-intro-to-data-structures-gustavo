#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	Node *next;
	Node *prev;
	T data;
	Node(T nodeData, Node *nextNode = nullptr, Node *prevNode = nullptr) : next(nextNode), prev(prevNode), data(nodeData) {};
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
		std::cout << current->data << std::endl;
		while (current->next)
		{
			current = current->next;
			std::cout << current->data << std::endl;
		}
	}
	void printReverse() const
	{

		Node<T> *current = this->tail;
		if (!current)
			return;
		std::cout << current->data << std::endl;
		while (current->prev)
		{
			current = current->prev;
			std::cout << current->data << std::endl;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const
	{
		return this->count;
	}
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
			this->count++;
			return;
		}
		this->head->prev = new Node<T>(data, this->head);
		this->head = this->head->prev;
		this->count++;
	}
	void addTail(const T &data)
	{
		if (!this->tail)
		{
			this->tail = new Node<T>(data);
			this->head = this->tail;
			this->count++;
			return;
		}
		this->tail->next = new Node<T>(data, nullptr, this->tail);
		this->tail = this->tail->next;
		this->count++;
	}

	// Removal
	bool removeHead()
	{
		if (!this->head)
			return false;
		if (!this->head->next)
		{
			delete this->head;
			this->count--;
			return true;
		}
		Node<T> *newHead = this->head->next;
		newHead->prev = nullptr;
		delete this->head;
		this->head = newHead;
		this->count--;
		return true;
	}
	bool removeTail()
	{
		if (!this->tail)
		{
			return false;
		}
		if (!this->tail->prev)
		{
			delete this->tail;
			this->count--;
			return true;
		}
		Node<T> *oldTail = this->tail;
		this->tail = this->tail->prev;
		this->tail->next = nullptr;
		delete oldTail;
		this->count--;
		return true;
	}
	void clear()
	{
		Node<T> *current = this->head;
		if (!current)
			return;
		while (current->next != nullptr)
		{
			Node<T> *next = current->next;
			delete current;
			this->count--;
			current = next;
		}
		delete current;
		this->count--;
		this->head = nullptr;
		this->tail = nullptr;
	}

	// Operators
	LinkedList<T> &operator=(LinkedList<T> &&other) noexcept
	{

		this->head = other.getHead();
		other.head = nullptr;
		this->tail = other.getTail();
		other.tail = nullptr;
		return *this;
	}
	LinkedList<T> &operator=(const LinkedList<T> &rhs)
	{
		Node<T> *externalIter = rhs.head;
		if (!externalIter)
		{
			this->head = nullptr;
			this->tail = nullptr;
			return *this;
		}
		this->head = new Node<T>(externalIter->data);
		Node<T> *internalIter = this->head;
		while (externalIter->next)
		{
			internalIter->next = new Node<T>(externalIter->data);
			internalIter = internalIter->next;
			externalIter = externalIter->next;
		}
		return *this;
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
		Node<T> *externalIter = list.head;
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
		this->head = other.head;
		other.head = nullptr;
		this->tail = other.tail;
		other.tail = nullptr;
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
			Node<T> *prevNode = internalIter;
			internalIter = internalIter->next;
			delete prevNode;
		}
		delete internalIter;
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T> *head;
	Node<T> *tail;
	unsigned int count;
};
