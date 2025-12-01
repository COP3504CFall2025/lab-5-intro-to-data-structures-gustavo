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
    ~LLS() = default;

    LLS(LLS<T> &&other)
    {
        this->list = other.list;
        other.list = LinkedList<T>();
    }
    LLS<T> &operator=(LLS<T> &&rhs)
    {
        if (rhs == *this)
            return *this;
        this->list = rhs.list;
        rhs.list = LinkedList<T>();
        return *this;
    }

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
            throw std::runtime_error("no head vro");
        T data = head->data;
        this->list.removeHead();
        return data;
    }

    // Access
    T peek() const override
    {
        const Node<T> *head = this->list.getHead();
        if (!head)
            throw std::runtime_error("no head vro");
        return head->data;
    }

    // Getters
    std::size_t getSize() const noexcept override
    {
        return this->list.getCount();
    }
};