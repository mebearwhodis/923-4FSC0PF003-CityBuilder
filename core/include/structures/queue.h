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
	template <typename T, std::size_t Size>
	class FixedQueue
	{
	private:
		//Fixed-size array
		std::array<T, Size> data_;

		//Index of the front element
		std::size_t front_;
		//Position to insert the next element
		std::size_t back_;
		//Number of elements in the queue
		std::size_t nbElements_;

	public:
		//Constructor, initializes the queue with a size of 0
		FixedQueue() { front_ = 0; back_ = 0; nbElements_ = 0; }

		//push() inserts element at the end of the queue, after the current last
		void push(const T& item)
		{
			//Check if there is room in the queue, return an error if not
			if (nbElements_ == Size)
			{
				throw std::overflow_error("Queue full");
			}

			//Insert element at the next available spot
			data_[back_] = item;
			//Increment back_ to next available spot (with modulo to wrap-around) & adjust number of elements in the queue
			back_ = (back_ + 1) % Size;
			nbElements_++;
		}

		//front() returns a reference to the next element in the queue (the 'oldest' one)
		const T& front() const
		{
			//Check if there is an item in the queue, return an error if not
			if (nbElements_ == 0)
			{
				throw std::underflow_error("Queue empty");
			}

			return data_[front_];
		}

		//pop() removes the next element
		void pop()
		{
			//Check if there is an item in the queue, return an error if not
			if (nbElements_ == 0)
			{
				throw std::underflow_error("Queue empty");
			}

			//Reset the element, might not be necessary, it would just get overwritten
			data_[front_] = T();
			//Increment front_ to next spot (with modulo to wrap-around) & adjust number of elements in the queue
			front_ = (front_ + 1) % Size;
			nbElements_--;
		}

	};

	template <typename T>
	class Queue
	{
	private:
		//Dynamic array
		std::vector<T> data_;

		//Index of the front element
		std::size_t front_;
		//Position to insert the next element
		std::size_t back_;

	public:
		//Constructor, initializes the queue with a size of 0
		Queue() { front_ = 0; back_ = 0; }

		//push() inserts element at the end of the queue, after the current last
		void push(const T& item)
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

		//front() returns a reference to the next element in the queue (the 'oldest' one)
		const T& front() const
		{
			//Check if there is an item in the queue, return an error if not
			if (data_.empty())
			{
				throw std::underflow_error("Queue empty");
			}

			return data_[front_];
		}

		//pop() removes the next element
		void pop()
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