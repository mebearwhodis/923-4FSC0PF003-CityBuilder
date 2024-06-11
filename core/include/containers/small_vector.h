#ifndef CORE_CONTAINERS_SMALL_VECTOR_H_
#define CORE_CONTAINERS_SMALL_VECTOR_H_

#include <array>
#include <stdexcept>
#include <initializer_list>

namespace core
{

	/**
	* \brief A fixed-capacity vector implementation.
	*
	* This class provides a vector-like interface with a fixed maximum capacity.
	* It stores elements in a pre-allocated array and does not support dynamic resizing.
	*
	* \tparam T Type of elements stored in the vector
	* \tparam Capacity Maximum number of elements the vector can hold
	*/
	template <typename T, std::size_t Capacity>
	class SmallVector
	{
	private:
		std::array<T, Capacity> data_;
		std::size_t begin_;
		std::size_t end_;
		std::size_t size_;

	public:
		// Constructor, initializes the queue with a size of 0
		SmallVector() : begin_(0), end_(0), size_(0) {}

		// Initializer list constructor
		SmallVector(std::initializer_list<T> init) : SmallVector()
		{
			if (init.size() > Capacity)
			{
				throw std::overflow_error("Initializer list exceeds vector capacity");
			}
			for (const T& item : init)
			{
				PushBack(item);
			}
		}

		// Push_Back() to add an element at the end
		void PushBack(const T& item)
		{
			if (size_ < Capacity)
			{
				data_[end_] = item;
				end_ = (end_ + 1) % Capacity;
				size_++;
			}
			else
			{
				throw std::overflow_error("Vector full");
			}
		}

		// Pop_Back() to delete the last element
		void PopBack()
		{
			if (size_ > 0)
			{
				end_ = (end_ - 1 + Capacity) % Capacity;
				size_--;
			}
			else
			{
				throw std::out_of_range("Vector empty");
			}
		}

		// Begin() returns iterator to beginning
		T* Begin()
		{
			return &data_[begin_];
		}

		// End() returns iterator to end
		T* End()
		{
			return &data_[end_];
		}

		// Size() returns the size that is calculated by subtracting Begin() from End()
		[[nodiscard]] std::size_t Size() const
		{
			return size_;
		}

		// Overloaded operator[]
		T& operator[](std::size_t pos)
		{
			if (pos >= size_)
			{
				throw std::out_of_range("Index out of range");
			}
			return data_[(begin_ + pos) % Capacity];
		}

		const T& operator[](std::size_t pos) const
		{
			if (pos >= size_)
			{
				throw std::out_of_range("Index out of range");
			}
			return data_[(begin_ + pos) % Capacity];
		}

		// Insert an element at the specified position
		void Insert(std::size_t position, const T& value)
		{
			if (size_ >= Capacity)
			{
				throw std::overflow_error("Vector full");
			}
			if (position > size_)
			{
				throw std::out_of_range("Position out of range");
			}
			for (std::size_t i = size_; i > position; --i)
			{
				data_[(begin_ + i) % Capacity] = data_[(begin_ + i - 1) % Capacity];
			}
			data_[(begin_ + position) % Capacity] = value;
			end_ = (end_ + 1) % Capacity;
			size_++;
		}

		// Erase the element at the specified position
		void Erase(std::size_t position)
		{
			if (size_ == 0)
			{
				throw std::out_of_range("Vector empty");
			}
			if (position >= size_)
			{
				throw std::out_of_range("Position out of range");
			}
			for (std::size_t i = position; i < size_ - 1; ++i)
			{
				data_[(begin_ + i) % Capacity] = data_[(begin_ + i + 1) % Capacity];
			}
			end_ = (end_ - 1 + Capacity) % Capacity;
			size_--;
		}
	};

} // namespace core

#endif // CORE_CONTAINERS_SMALL_VECTOR_H_
