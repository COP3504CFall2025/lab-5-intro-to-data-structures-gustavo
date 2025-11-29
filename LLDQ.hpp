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
        Node<T> *head = this->list.getHead();
        if (!head)
            throw std::out_of_range("no head vro");
        this->list.removeHead();
        return head->data;
    }
    T popBack() override
    {
        Node<T> *tail = this->list.getTail();
        if (!tail)
            throw std::out_of_range("no tail vro");
        this->list.removeTail();
        return tail->data;
    }

    // Element Accessors
    const T &front() const override
    {
        Node<T> *head = this->list.getHead();
        if (!head)
            throw std::out_of_range("no head vro");
        return head->data;
    }
    const T &back() const override
    {
        Node<T> *tail = this->list.getTail();
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
