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
    template <typename T, std::size_t Capacity>
    class FixedStack
    {
    private:
        //Fixed-size array
        std::array<T, Capacity> data_;

        //Index of the Top element
        std::size_t top_;

    public:
        //Constructor, initializes the stack with a size of 0
        FixedStack() { top_ = 0; }

        //Push() inserts element at the Top of the stack
        void Push(const T& item)
        {
            //Check if there is room in the stack, return an error if not
            if (top_ == Capacity)
            {
                throw std::overflow_error("Stack full");
            }

            //Insert element at the Top and adjust top_ position
            data_[top_++] = item;
        }

        //Top() returns a reference to the Top element in the stack
        [[nodiscard]] const T& Top() const
        {
            //Check if there is an item in the stack, return an error if not
            if (top_ == 0)
            {
                throw std::underflow_error("Stack empty");
            }

            return data_[top_ - 1];
        }

        //Top() returns a reference to the Top element in the stack
        [[nodiscard]] T& Top()
        {
            //Check if there is an item in the stack, return an error if not
            if (top_ == 0)
            {
                throw std::underflow_error("Stack empty");
            }

            return data_[top_ - 1];
        }

        //Pop() removes the Top element
        void Pop()
        {
            //Check if there is an item in the stack, return an error if not
            if (top_ == 0)
            {
                throw std::underflow_error("Stack empty");
            }

            //Decrement Top to remove the Top element
            --top_;
        }
    };

    template <typename T>
    class Stack
    {
    private:
        //Dynamic array
        std::vector<T> data_;

    public:
        //Constructor, initializes the stack with a size of 0
        Stack() = default;

        //Push() inserts element at the Top of the stack
        void Push(const T& item)
        {
            if (data_.size() == data_.capacity())
            {
                data_.reserve(data_.capacity() == 0 ? 1 : data_.capacity() * 2);
            }
            data_.push_back(item);
        }

        //Top() returns a reference to the Top element in the stack
        [[nodiscard]] const T& Top() const
        {
            //Check if there is an item in the stack, return an error if not
            if (data_.empty())
            {
                throw std::underflow_error("Stack empty");
            }

            return data_.back();
        }

        //Top() returns a reference to the Top element in the stack
        [[nodiscard]] T& Top()
        {
            //Check if there is an item in the stack, return an error if not
            if (data_.empty())
            {
                throw std::underflow_error("Stack empty");
            }

            return data_.back();
        }

        //Pop() removes the Top element
        void Pop()
        {
            //Check if there is an item in the stack, return an error if not
            if (data_.empty())
            {
                throw std::underflow_error("Stack empty");
            }

            //Remove the Top element
            data_.pop_back();
        }
    };
} //namespace core

#endif //CORE_STRUCTURES_STACK_H_
