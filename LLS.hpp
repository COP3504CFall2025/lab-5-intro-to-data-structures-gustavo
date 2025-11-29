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
        T *pHead = this->list.getHead();
        if (!pHead)
            throw std::out_of_range("no head vro");
        T head = *pHead;
        this->list.removeHead();
        return head;
    }

    // Access
    T peek() const override
    {
        T *pHead = this->list.getHead();
        if (!pHead)
            throw std::out_of_range("no head vro");
        T head = *pHead;
        return head;
    }

    // Getters
    std::size_t getSize() const noexcept override
    {
        return this->list.getCount();
    }
};