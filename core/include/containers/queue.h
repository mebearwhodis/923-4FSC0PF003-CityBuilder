#ifndef CORE_CONTAINERS_QUEUE_H_
#define CORE_CONTAINERS_QUEUE_H_

#include <stdexcept>
#include <vector>

namespace core
{
	/**
	 * \brief Queues are data structures that follow the principle of 'First in, first out'
	 * Queue's size is dynamic
	 */
	template <typename T>
	class Queue
	{
	private:
		// Dynamic array
		std::vector<T> data_;
		std::size_t front_;
		std::size_t back_;
		std::size_t size_;

	public:
		// Constructor, initializes the queue with a size of 0
		Queue() : front_(0), back_(0), size_(0) {}

		// Push() inserts element at the back of the queue
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

		void Push(T&& item)
		{
			if (size_ == data_.capacity())
			{
				data_.reserve(data_.capacity() == 0 ? 1 : data_.capacity() * 2);
			}
			if (size_ < data_.size())
			{
				data_[back_] = std::move(item);
			}
			else
			{
				data_.push_back(std::move(item));
			}
			back_ = (back_ + 1) % data_.capacity();
			size_++;
		}

		// Pop() removes the front element
		void Pop()
		{
			if (size_ == 0)
			{
				throw std::out_of_range("Queue empty");
			}
			front_ = (front_ + 1) % data_.capacity();
			size_--;
		}

		// Front() returns a reference to the front element in the queue
		[[nodiscard]] const T& Front() const
		{
			if (size_ == 0)
			{
				throw std::out_of_range("Queue empty");
			}
			return data_[front_];
		}

		// Front() returns a reference to the front element in the queue
		[[nodiscard]] T& Front()
		{
			if (size_ == 0)
			{
				throw std::out_of_range("Queue empty");
			}
			return data_[front_];
		}

		// Size() returns the current size of the queue
		[[nodiscard]] std::size_t Size() const
		{
			return size_;
		}

		// Capacity() returns the current capacity of the queue
		[[nodiscard]] std::size_t Capacity() const
		{
			return data_.capacity();
		}

		// Empty() clears the queue
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