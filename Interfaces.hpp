#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class StackInterface
{
    virtual void push(const T &item);
    virtual T pop(const T &item);
    virtual T peek() const;
};

template <typename T>
class QueueInterface
{
    virtual void enqueue(const T &item);
    virtual T dequeue(const T &item);
    virtual T peek() const;
};

template <typename T>
class DequeInterface
{
    virtual void pushFront(const T &item);
    virtual void pushBack(const T &item);
    virtual T popFront();
    virtual T popBack();
    virtual const T &front() const;
    virtual const T &back() const;
};
