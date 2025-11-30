#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T>
class ABQ : public QueueInterface<T>
{

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
    }

public:
    // Constructors + Big 5
    ABQ()
    {
        this->array_ = new T[1];
        this->capacity_ = 1;
        this->curr_size_ = 0;
    }
    explicit ABQ(const size_t capacity)
    {
        this->array_ = new T[capacity];
        this->capacity_ = capacity;
        this->curr_size_ = 0;
    }
    ABQ(const ABQ &other)
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
    ABQ &operator=(const ABQ &rhs)
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
    ABQ(ABQ &&other) noexcept
    {
        this->array_ = other.array_;
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;

        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }
    ABQ &operator=(ABQ &&rhs) noexcept
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
    ~ABQ() noexcept override
    {
        delete[] this->array_;
        this->array_ = nullptr;
        this->capacity_ = 0;
        this->curr_size_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override
    {
        return this->curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept
    {
        return this->capacity_;
    }
    [[nodiscard]] T *getData() const noexcept
    {
        return this->array_;
    }

    // Insertion
    void enqueue(const T &data) override
    {
        if (this->curr_size_ >= this->capacity_) // not enough space. Create a new array with each item shifted to the right
        {
            size_t newCapacity = this->capacity_ * scale_factor_;

            T *newArray = new T[newCapacity];
            size_t newSize = this->curr_size_ + 1;
            for (size_t i = 1; i < newSize; i++)
            {
                newArray[i] = this->array_[i - 1];
            }

            delete[] this->array_;
            this->array_ = newArray;
            this->curr_size_ = newSize;
            // note that array_[0] is junk value
        }
        else // enough space. shift all to the right in current array
        {
            size_t newSize = this->curr_size_ + 1;
            for (size_t i = 1; i < newSize; i++)
            {
                this->array_[i] = this->array_[i - 1];
            }
        }
        this->array_[0] = data;
    }
    // Access
    T peek() const override
    {
        return this->array_[this->curr_size_];
    }

    // Deletion
    T dequeue() override
    {
        if (this->curr_size_ < this->capacity_ / 2 && this->capacity_ > 1)
            reserve(curr_size_ / scale_factor_);
        this->curr_size_--;
        return this->array_[this->curr_size_];
    };
};
