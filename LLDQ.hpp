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
    LLDQ() : list() {}
    ~LLDQ() = default;

    LLDQ(const LLDQ<T> &other) : list(std::move(other.list)) {}
    LLDQ(LLDQ<T> &&other)
    {
        this->list = other.list;
        other.list = LinkedList<T>();
    }
    LLDQ<T> &operator=(const LLDQ<T> &other)
    {
        this->list = other.list;
        return *this;
    }
    LLDQ<T> &operator=(LLDQ<T> &&rhs)
    {
        this->list = std::move(rhs.list);
        return *this;
    }

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
        T data = head->data;
        this->list.removeHead();
        return data;
    }
    T popBack() override
    {
        Node<T> *tail = this->list.getTail();
        if (!tail)
            throw std::out_of_range("no tail vro");
        T data = tail->data;
        this->list.removeTail();
        return data;
    }

    // Element Accessors
    const T &front() const override
    {
        const Node<T> *head = this->list.getHead();
        if (!head)
            throw std::out_of_range("no head vro");
        return head->data;
    }
    const T &back() const override
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
