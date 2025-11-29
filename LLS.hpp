#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T>
{
private:
    LinkedList<T> list;

public:
    // Constructor
    LLS() : list() {}

    // Insertion
    void push(const T &item) override
    {
        this->list.addHead(item);
    }

    // Deletion
    T pop() override
    {
        Node<T> *head = this->list.getHead();
        if (!head)
            throw std::out_of_range("no head vro");
        this->list.removeHead();
        return head->data;
    }

    // Access
    T peek() const override
    {
        Node<T> *head = this->list.getHead();
        if (!head)
            throw std::out_of_range("no head vro");
        return head->data;
    }

    // Getters
    std::size_t getSize() const noexcept override
    {
        return this->list.getCount();
    }
};