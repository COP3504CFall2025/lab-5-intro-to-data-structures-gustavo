#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T>
class ABS : public StackInterface<T>
{
public:
    // Big 5 + Parameterized Constructor
    ABS()
    {
        this->array_ = new T[1];
        this->capacity_ = 1;
        this->curr_size_ = 0;
    }
    explicit ABS(const size_t capacity)
    {
        this->array_ = new T[capacity];
        this->capacity_ = capacity;
        this->curr_size_ = 0;
    }
    ABS(const ABS &other)
    {
        this->array_ = nullptr;
        this->capacity_ = 0;
        this->curr_size = 0;

        T *newArray = new T[other.capacity_];
        for (size_t i = 0; i < other.curr_size_; i++)
        {
            newArray[i] = other.array_[i];
        }

        this->array_ = newArray;
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
    }
    ABS &operator=(const ABS &rhs)
    {
        T *newArray = new T[rhs.capacity_];
        for (size_t i = 0; i < rhs.curr_size_; i++)
        {
            newArray[i] = rhs.array_[i];
        }

        delete[] this->array;

        this->array_ = newArray;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;

        return *this;
    }
    ABS(ABS &&other) noexcept
    {
        this->array_ = other.array_;
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;

        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }
    ABS &operator=(ABS &&rhs) noexcept
    {
        delete[] this->array_;
        this->array_ = rhs.array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;

        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;

        return *this;
    }
    ~ABS() noexcept override
    {
        delete this->array_;
        this->array_ = nullptr;
        this->capacity_ = 0;
        this->curr_size_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override
    {
        return this->curr_size_;
    };

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept
    {
        return this->capacity_;
    };

    // Return underlying data for the stack
    [[nodiscard]] T *getData() const noexcept
    {
        return this->array_;
    };

    // Push item onto the stack
    void push(const T &data) override
    {
        if (this->curr_size_ == capacity_)
        {
            reserve(capacity_ * scale_factor_);
        }
        this->array_[curr_size_] = data;
    };

    T peek() const override
    {
        if (curr_size_ == 0)
            throw std::runtime_error("Gerb");
        return this->array_[curr_size_ - 1];
    };

    T pop() override
    {
        if (curr_size_ == 0)
            throw std::runtime_error("Gerb");
        this->curr_size_--;
        return this->array_[curr_size_ - 1];
    };

private:
    size_t capacity_;
    size_t curr_size_;
    T *array_;
    static constexpr size_t scale_factor_ = 2;

    void reserve(size_t newCapacity)
    {
        T *newArray = new T[newCapacity];
        size_t newSize = this->curr_size_ > newCapacity ? newCapacity : this->curr_size_;
        for (size_t i = 0; i < newSize; i++)
        {
            newArray[i] = this->array_[i];
        }

        delete[] this->array_;
        this->array_ = newArray;
        this->curr_size_ = newSize;
        this->capacity = newCapacity;
    }
};
