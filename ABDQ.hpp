#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T>
{
private:
    T *data_;              // underlying dynamic array
    std::size_t capacity_; // total allocated capacity
    std::size_t size_;     // number of stored elements
    long front_;           // index of front element
    long back_;            // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

    void reserve(size_t newCapacity)
    {
        T *newArray = new T[newCapacity];
        if (this->size_ > newCapacity)
            throw std::runtime_error("New capacity cannot store all items. You would clip the stuff cuh");
        size_t newSize = this->size_;
        for (size_t i = 0; i < newSize; i++)
        {
            newArray[i] = this->data_[(this->front_ + i) % capacity_];
        }

        delete[] this->data_;
        this->data_ = newArray;
        this->size_ = newSize;
        this->capacity_ = newCapacity;
        this->front_ = 0;
        this->back_ = this->size_ - 1;
    }

public:
    // Big 5
    ABDQ()
    {
        this->data_ = new T[1];
        this->capacity_ = 1;
        this->size_ = 0;
        this->front_ = this->back_ = -1;
    }
    explicit ABDQ(std::size_t capacity)
    {
        if (capacity < 4)
        {
            throw std::runtime_error("Capacity too small");
        }
        this->data_ = new T[capacity];
        this->capacity_ = capacity;
        this->size_ = 0;
        this->front_ = this->back_ = -1;
    }
    ABDQ(const ABDQ &other)
    {
        this->data_ = nullptr;
        this->capacity_ = 0;
        this->size_ = 0;

        T *newArray = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++)
        {
            newArray[i] = other.data_[(other.front_ + i) % other.capacity_];
        }

        this->data_ = newArray;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
    }
    ABDQ(ABDQ &&other) noexcept
    {
        this->data_ = other.data_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.back_ = other.front_ = -1;
    }
    ABDQ &operator=(const ABDQ &other)
    {
        T *newArray = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++)
        {
            newArray[i] = other.data_[(other.front_ + i) % other.capacity_];
        }

        delete[] this->data_;

        this->data_ = newArray;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        return *this;
    }
    ABDQ &operator=(ABDQ &&other) noexcept
    {
        delete[] this->data_;
        this->data_ = other.data_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;

        other.data_ = nullptr;
        other.front_ = other.back_ = -1;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }
    ~ABDQ() override
    {
        delete[] this->data_;
        this->data_ = nullptr;
        this->capacity_ = 0;
        this->size_ = 0;
        this->front_ = this->back_ = -1;
    }

    // Insertion
    void pushFront(const T &item) override
    {
        if (this->size_ == this->capacity_)
        {
            reserve(this->capacity_ * SCALE_FACTOR);
        }
        if (this->front_ == -1)
        {
            this->front_++;
            this->back_++;
            this->data_[front_] = item;
            return;
        }
        std::size_t index = (this->front_ == 0 ? this->capacity_ - 1 : this->front_ - 1);
        this->data_[index] = item;
        this->front_ = index;
        this->size_++;
    }
    void pushBack(const T &item) override
    {
        if (this->size_ == this->capacity_)
        {
            reserve(this->capacity_ * SCALE_FACTOR);
        }
        if (this->front_ == -1)
        {
            this->front_++;
        }
        std::size_t index = (this->back_ + 1) % this->capacity_;
        this->data_[index] = item;
        this->back_ = index;
        this->size_++;
    }

    // Deletion
    T popFront() override
    {
        if (this->front_ == -1)
        {
            throw std::runtime_error("Cannot call popFront(): Deque is empty");
        }
        T item = this->data_[this->front_];
        this->size_--;
        if (this->back_ == this->front_)
        {
            this->back_ = this->front_ = -1;
            return item;
        }

        this->front_ = (this->front_ + 1) % this->capacity_;
        if (this->size_ == this->capacity_ / SCALE_FACTOR)
        {
            reserve(this->capacity_ / SCALE_FACTOR);
        }

        return item;
    }
    T popBack() override
    {
        if (this->front_ == -1)
        {
            throw std::runtime_error("Cannot call popBack(): Deque is empty");
        }
        T item = this->data_[this->back_];
        this->size_--;
        if (this->back_ == this->front_)
        {
            this->back_ = this->front_ = -1;
        }
        this->back_ = this->back_ == 0 ? this->capacity_ : this->back_ - 1;
        if (this->size_ == this->capacity_ / SCALE_FACTOR)
        {
            reserve(this->capacity_ / SCALE_FACTOR);
        }
        return item;
    }

    // Access
    const T &front() const override
    {
        return this->data_[this->front_];
    }
    const T &back() const override
    {
        return this->data_[this->back_];
    }

    // Getters
    std::size_t getSize() const noexcept override
    {
        return this->size_;
    }
};
