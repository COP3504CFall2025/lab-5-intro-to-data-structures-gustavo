#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>

template <typename T>
class LLDQ : public DequeInterface<T>
{
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ();

    // Core Insertion Operations
    void pushFront(const T &item) override
    {
        this->list.addHead(item);
    }
    void pushBack(const T &item) override
    {
        this->list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override
    {
        T *pHead = this->list.getHead();
        if (!pHead)
            throw std::out_of_range("no head vro");
        T head = *pHead;
        this->list.removeHead();
        return head;
    }
    T popBack() override
    {
        T *pTail = this->list.getTail();
        if (!pTail)
            throw std::out_of_range("no tail vro");
        T tail = *pTail;
        this->list.removeTail();
        return tail;
    }

    // Element Accessors
    const T &front() const override
    {
        T *pHead = this->list.getHead();
        if (!pHead)
            throw std::out_of_range("no head vro");
        T head = *pHead;
        return head;
    }
    const T &back() const override
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
