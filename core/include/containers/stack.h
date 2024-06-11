#ifndef CORE_CONTAINERS_STACK_H_
#define CORE_CONTAINERS_STACK_H_

#include <stdexcept>
#include <vector>

namespace core
{
    /**
     * \brief Stacks are data structures that follow the principle of 'Last in, first out'
     * Stack's size is dynamic
     */
    template <typename T>
    class Stack
    {
    private:
        // Dynamic array
        std::vector<T> data_;

    public:
        // Constructor, initializes the stack with a size of 0
        Stack() = default;

        // Push() inserts element at the Top of the stack
        void Push(const T& item)
        {
            if (data_.size() == data_.capacity())
            {
                data_.reserve(data_.capacity() == 0 ? 1 : data_.capacity() * 2);
            }
            data_.push_back(item);
        }

        // Push() inserts an rvalue element at the Top of the stack
        void Push(T&& item)
        {
            if (data_.size() == data_.capacity())
            {
                data_.reserve(data_.capacity() == 0 ? 1 : data_.capacity() * 2);
            }
            data_.push_back(std::move(item));
        }

        // Pop() removes the Top element
        void Pop()
        {
            // Check if there is an item in the stack, return an error if not
            if (data_.empty())
            {
                throw std::out_of_range("Stack empty");
            }

            // Remove the Top element
            data_.pop_back();
        }

        // Top() returns a reference to the Top element in the stack
        [[nodiscard]] const T& Top() const
        {
            // Check if there is an item in the stack, return an error if not
            if (data_.empty())
            {
                throw std::out_of_range("Stack empty");
            }

            return data_.back();
        }

        // Top() returns a reference to the Top element in the stack
        [[nodiscard]] T& Top()
        {
            // Check if there is an item in the stack, return an error if not
            if (data_.empty())
            {
                throw std::out_of_range("Stack empty");
            }

            return data_.back();
        }

        // Size() to get the current size of the stack
        [[nodiscard]] std::size_t Size() const
        {
            return data_.size();
        }

        // Capacity() to get the current capacity of the stack
        [[nodiscard]] std::size_t Capacity() const
        {
            return data_.capacity();
        }

        // Empty() to check if the stack is empty
        [[nodiscard]] bool Empty() const
        {
            return data_.empty();
        }

        // Clear() to empty the stack
        void Clear()
        {
            data_.clear();
        }
    };
} // namespace core

#endif // CORE_CONTAINERS_STACK_H_
