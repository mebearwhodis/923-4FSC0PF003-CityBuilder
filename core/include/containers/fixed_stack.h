#ifndef CORE_CONTAINERS_FIXED_STACK_H_
#define CORE_CONTAINERS_FIXED_STACK_H_

#include <array>
#include <stdexcept>


namespace core
{
    /**
     * \brief Stacks are data structures that follow the principle of 'Last in, first out'
     * FixedStack's size is set when initialized
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

        //Push() inserts an rvalue element at the Top of the stack
        void Push(T&& item)
        {
            //Check if there is room in the stack, return an error if not
            if (top_ == Capacity)
            {
                throw std::overflow_error("Stack full");
            }

            //Insert element at the Top using move semantics and adjust top_ position
            data_[top_++] = std::move(item);
        }

        //Pop() removes the Top element
        void Pop()
        {
            //Check if there is an item in the stack, return an error if not
            if (top_ == 0)
            {
                throw std::out_of_range("Stack empty");
            }

            //Decrement Top to remove the Top element
            --top_;
        }

        //Top() returns a reference to the Top element in the stack
        [[nodiscard]] const T& Top() const
        {
            //Check if there is an item in the stack, return an error if not
            if (top_ == 0)
            {
                throw std::out_of_range("Stack empty");
            }

            return data_[top_ - 1];
        }

        //Top() returns a reference to the Top element in the stack
        [[nodiscard]] T& Top()
        {
            //Check if there is an item in the stack, return an error if not
            if (top_ == 0)
            {
                throw std::out_of_range("Stack empty");
            }

            return data_[top_ - 1];
        }

        [[nodiscard]] size_t size() const
        {
            return top_;
        }
    };
} //namespace core

#endif //CORE_CONTAINERS_FIXED_STACK_H_
