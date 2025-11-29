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
        Node<T> *tail = this->list.getTail();
        if (!tail)
            throw std::out_of_range("no tail vro");
        this->list.removeTail();
        return tail->data;
    }

    // Access
    T peek() const override
    {
        const Node<T> *tail = this->list.getTail();
        if (!tail)
            throw std::out_of_range("no tail vro");
        return tail->data;
    }

    // Getter
    std::size_t getSize() const noexcept override
    {
        return this->list.getCount();
    }
};