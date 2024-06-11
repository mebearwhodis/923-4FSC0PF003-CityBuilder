#ifndef CORE_CONTAINERS_VECTOR_H_
#define CORE_CONTAINERS_VECTOR_H_

#include <array>
#include <stdexcept>
#include <vector>

namespace core
{
    /**
     * \brief A dynamic vector implementation.
     *
     * This class provides a vector-like interface with dynamic resizing capabilities.
     * It uses a std::vector internally for storage and management of elements.
     *
     * \tparam T Type of elements stored in the vector
     * \tparam Allocator Allocator type for managing memory
     * \tparam GrowthDividend Factor by which to grow the capacity of the vector
     * \tparam GrowthDivisor Factor by which to divide the capacity when resizing
     */
    template <typename T, class Allocator = std::allocator<T>, std::size_t GrowthDividend = 3, std::size_t GrowthDivisor = 2>
    class Vector
    {
    private:
        std::vector<T, Allocator> data_;
        std::size_t begin_;
        std::size_t end_;
        std::size_t size_;

    public:
        // Static assert that GrowthDividend > GrowthDivisor
        static_assert(GrowthDividend > GrowthDivisor, "GrowthDividend must be greater than GrowthDivisor");

        Vector() : begin_(0), end_(0), size_(0) {}

        // Initializer list constructor
        Vector(std::initializer_list<T> init) : begin_(0), end_(0), size_(0)
        {
            Reserve(init.size());
            for (const T& item : init)
            {
                PushBack(item);
            }
        }

        void Reserve(std::size_t newCapacity)
        {
            data_.reserve(newCapacity);
        }

        void PushBack(const T& item)
        {
            if (size_ >= data_.capacity())
            {
                Reserve((data_.capacity() * GrowthDividend) / GrowthDivisor);
            }
            try
            {
                data_.push_back(item);
                ++size_;
            }
            catch (const std::bad_alloc& e)
            {
                throw std::overflow_error("Vector capacity exceeded");
            }
        }

        void EmplaceBack(T&& item)
        {
            if (size_ >= data_.capacity())
            {
                Reserve((data_.capacity() * GrowthDividend) / GrowthDivisor);
            }
            try
            {
                data_.emplace_back(std::move(item));
                ++size_;
            }
            catch (const std::bad_alloc& e)
            {
                throw std::overflow_error("Vector capacity exceeded");
            }
        }

        void PopBack()
        {
            if (size_ > 0)
            {
                try
                {
                    data_.pop_back();
                    --size_;
                }
                catch (const std::bad_alloc& e)
                {
                    throw std::out_of_range("Vector is empty");
                }
            }
            else
            {
                throw std::out_of_range("Vector is empty");
            }
        }

        auto Begin() { return data_.begin(); }

        auto End() { return data_.end(); }

        [[nodiscard]] std::size_t Size() const { return size_; }

        T& operator[](std::size_t pos) { return data_[pos]; }

        const T& operator[](std::size_t pos) const { return data_[pos]; }

        void Insert(std::size_t position, const T& value)
        {
            try
            {
                data_.insert(data_.begin() + position, value);
                ++size_;
            }
            catch (const std::bad_alloc& e)
            {
                throw std::overflow_error("Vector capacity exceeded");
            }
        }

        void Erase(std::size_t position)
        {
            if (size_ > 0)
            {
                try
                {
                    data_.erase(data_.begin() + position);
                    --size_;
                }
                catch (const std::bad_alloc& e)
                {
                    throw std::out_of_range("Vector is empty");
                }
            }
            else
            {
                throw std::out_of_range("Vector is empty");
            }
        }
    };

} // namespace core

#endif // CORE_CONTAINERS_VECTOR_H_
