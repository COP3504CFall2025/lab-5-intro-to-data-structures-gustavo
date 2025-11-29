#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T>
{
private:
    LinkedList<T> list;

public:
    // Constructor
    LLQ() : list() {}

    // Insertion
    void enqueue(const T &item) override
    {
        this->list.addHead(item);
    }

    // Deletion
    T dequeue() override
    {
        T *pTail = this->list.getTail();
        if (!pTail)
            throw std::out_of_range("no tail vro");
        T tail = *pTail;
        this->list.removeTail();
        return tail;
    }

    // Access
    T peek() const override
    {
        T *pTail = this->list.getTail();
        if (!pTail)
            throw std::out_of_range("no tail vro");
        T tail = *pTail;
        return tail;
    }

    // Getter
    std::size_t getSize() const noexcept override
    {
        return this->list.getCount();
    }
};