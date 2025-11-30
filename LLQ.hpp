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

    LLQ(LLQ<T> &&other)
    {
        this->list = other.list;
        other.list = LinkedList<T>();
    }
    LLQ() : list() {}
    ~LLQ() noexcept override = default;

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
            throw std::runtime_error("Gerb");
        T data = tail->data;
        this->list.removeTail();
        return data;
    }

    // Access
    T peek() const override
    {
        const Node<T> *tail = this->list.getTail();
        if (!tail)
            throw std::runtime_error("gerb");
        return tail->data;
    }

    // Getter
    std::size_t getSize() const noexcept override
    {
        return this->list.getCount();
    }
};