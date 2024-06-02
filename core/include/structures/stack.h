#ifndef CORE_STRUCTURES_STACK_H_
#define CORE_STRUCTURES_STACK_H_

#include <array>
#include <stdexcept>
#include <vector>


namespace core
{
    /**
     * \brief Stacks are data structures that follow the principle of 'Last in, first out'
     * FixedStack's size is set when initialized, Stack's size is dynamic
     */
    template <typename T, std::size_t Size>
    class FixedStack
    {
    private:
        //Fixed-size array
        std::array<T, Size> data_;

        //Index of the top element
        std::size_t top_;

    public:
        // Constructor, initializes the stack with a size of 0
        FixedStack() { top_ = 0; }

        // push() inserts element at the top of the stack
        void push(const T& item)
        {
            // Check if there is room in the stack, return an error if not
            if (top_ == Size)
            {
                throw std::overflow_error("Stack full");
            }

            // Insert element at the top
            data_[top_++] = item;
        }

        // top() returns a reference to the top element in the stack
        const T& top() const
        {
            // Check if there is an item in the stack, return an error if not
            if (top_ == 0)
            {
                throw std::underflow_error("Stack empty");
            }

            return data_[top_ - 1];
        }

        // pop() removes the top element
        void pop()
        {
            // Check if there is an item in the stack, return an error if not
            if (top_ == 0)
            {
                throw std::underflow_error("Stack empty");
            }

            // Decrement top to remove the top element
            --top_;
        }
    };

    template <typename T>
    class Stack
    {
    private:
        // Dynamic array
        std::vector<T> data_;

    public:
        // Constructor, initializes the stack with a size of 0
        Stack() = default;

        // push() inserts element at the top of the stack
        void push(const T& item)
        {
            if (data_.size() == data_.capacity())
            {
                data_.reserve(data_.capacity() == 0 ? 1 : data_.capacity() * 2);
            }
            data_.push_back(item);
        }

        // top() returns a reference to the top element in the stack
        const T& top() const
        {
            // Check if there is an item in the stack, return an error if not
            if (data_.empty())
            {
                throw std::underflow_error("Stack empty");
            }

            return data_.back();
        }

        // pop() removes the top element
        void pop()
        {
            // Check if there is an item in the stack, return an error if not
            if (data_.empty())
            {
                throw std::underflow_error("Stack empty");
            }

            // Remove the top element
            data_.pop_back();
        }
    };
} // namespace core

#endif // CORE_STRUCTURES_STACK_H_
