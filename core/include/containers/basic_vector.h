#ifndef CORE_STRUCTURES_QUEUE_H_
#define CORE_STRUCTURES_QUEUE_H_

#include <array>
#include <stdexcept>
#include <vector>


namespace core
{
	/**
	 * \brief Queues are data structures that follow the principle of 'First in, first out'
	 * FixedQueue's size is set when initialized, Queue's size is dynamic
	 */
	template <typename T, std::size_t Capacity>
	class FixedQueue
	{
	private:
		//Fixed-capacity array
		std::array<T, Capacity> data_;

		//Index of the Front element
		std::size_t front_;
		//Position to insert the next element
		std::size_t back_;
		//Number of elements in the queue
		std::size_t size_;

	public:
		//Constructor, initializes the queue with a size of 0
		FixedQueue() { front_ = 0; back_ = 0; size_ = 0; }

		//Push() inserts element at the end of the queue, after the current last
		void Push(const T& item)
		{
			//Check if there is room in the queue, return an error if not
			if (size_ == Capacity)
			{
				throw std::overflow_error("Queue full");
			}

			//Insert element at the next available spot
			data_[back_] = item;
			//Increment back_ to next available spot (with modulo to wrap-around) & adjust number of elements in the queue
			back_ = (back_ + 1) % Capacity;
			size_++;
		}

		//TODO: void Push(T&& item) std::move

		//Front() returns a reference to the next element in the queue (the 'oldest' one)
		[[nodiscard]] const T& Front() const
		{
			//Check if there is an item in the queue, return an error if not
			if (size_ == 0)
			{
				//TODO: out of range
				throw std::underflow_error("Queue empty");
			}

			return data_[front_];
		}

		//Front() returns a reference to the next element in the queue (the 'oldest' one)
		[[nodiscard]] T& Front() 
		{
			//Check if there is an item in the queue, return an error if not
			if (size_ == 0)
			{
				throw std::underflow_error("Queue empty");
			}

			return data_[front_];
		}

		//Pop() removes the next element
		void Pop()
		{
			//Check if there is an item in the queue, return an error if not
			if (size_ == 0)
			{
				throw std::underflow_error("Queue empty");
			}

			//Reset the element, might not be necessary, it would just get overwritten
			data_[front_] = {};
			//Increment front_ to next spot (with modulo to wrap-around) & adjust number of elements in the queue
			front_ = (front_ + 1) % Capacity;
			size_--;
		}

	};

	template <typename T>
	class Queue
	{
	private:
		//Dynamic array
		std::vector<T> data_;

		//Index of the Front element
		std::size_t front_;
		//Position to insert the next element
		std::size_t back_;

	public:
		//Constructor, initializes the queue with a size of 0
		Queue() { front_ = 0; back_ = 0; }

		//Push() inserts element at the end of the queue, after the current last
		void Push(const T& item)
		{
			//If capacity is reached, double it (or set it to 1 if it was 0)
			if (data_.size() == data_.capacity())
			{
				data_.reserve(data_.capacity() == 0 ? 1 : data_.capacity() * 2);
			}

			data_.push_back(item);

			//Increment back_ to next available spot (with modulo to wrap-around) & adjust number of elements in the queue
			back_ = (back_ + 1) % data_.capacity();
		}

		//Front() returns a reference to the next element in the queue (the 'oldest' one)
		[[nodiscard]] const T& Front() const
		{
			//Check if there is an item in the queue, return an error if not
			if (data_.empty())
			{
				throw std::underflow_error("Queue empty");
			}

			return data_[front_];
		}

		//Front() returns a reference to the next element in the queue (the 'oldest' one)
		[[nodiscard]] T& Front()
		{
			//Check if there is an item in the queue, return an error if not
			if (data_.empty())
			{
				throw std::underflow_error("Queue empty");
			}

			return data_[front_];
		}

		//Pop() removes the next element
		void Pop()
		{
			//Check if there is an item in the queue, return an error if not
			if (data_.empty())
			{
				throw std::underflow_error("Queue empty");
			}

			//Reset the element, might not be necessary, it would just get overwritten
			//data_[front_] = T();

			//Increment front_ to next spot (with modulo to wrap-around) & adjust number of elements in the queue
			front_ = (front_ + 1) % data_.capacity();
		}
	};
} //namespace core
#endif //CORE_STRUCTURES_QUEUE_H_