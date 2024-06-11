#ifndef CORE_CONTAINERS_QUEUE_H_
#define CORE_CONTAINERS_QUEUE_H_

#include <stdexcept>
#include <vector>

namespace core
{
    template <typename T>
    class Queue
    {
    private:
        std::vector<T> data_;
        std::size_t front_;
        std::size_t back_;
        std::size_t size_;

    public:
        Queue() : front_(0), back_(0), size_(0) {}

        void Push(const T& item)
        {
            if (size_ == data_.capacity())
            {
                data_.reserve(data_.capacity() == 0 ? 1 : data_.capacity() * 2);
            }
            if (size_ < data_.size())
            {
                data_[back_] = item;
            }
            else
            {
                data_.push_back(item);
            }
            back_ = (back_ + 1) % data_.capacity();
            size_++;
        }

        void Pop()
        {
            if (size_ == 0)
            {
                throw std::out_of_range("Queue empty");
            }
            front_ = (front_ + 1) % data_.capacity();
            size_--;
        }

        const T& Front() const
        {
            if (size_ == 0)
            {
                throw std::out_of_range("Queue empty");
            }
            return data_[front_];
        }

        T& Front()
        {
            if (size_ == 0)
            {
                throw std::out_of_range("Queue empty");
            }
            return data_[front_];
        }

        std::size_t Size() const
        {
            return size_;
        }

        std::size_t Capacity() const
        {
            return data_.capacity();
        }

        void Empty()
        {
            data_.clear();
            front_ = 0;
            back_ = 0;
            size_ = 0;
        }
    };
} // namespace core

#endif // CORE_CONTAINERS_QUEUE_H_
