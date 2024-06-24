#ifndef CORE_CONTAINERS_BASIC_VECTOR_H_
#define CORE_CONTAINERS_BASIC_VECTOR_H_

#include <array>
#include <vector>
#include <variant>
#include <stdexcept>
#include <initializer_list>
#include <iterator>

namespace core
{
	/**
	 * \brief A vector class that uses stack storage up to a specified size,
	 *        and switches to heap storage when the size exceeds the stack capacity.
	 *
	 * \tparam T Type of elements stored in the vector
	 * \tparam StackSize Number of elements that can be stored on the stack
	 */
	template <typename T, std::size_t StackSize>
	class BasicVector
	{
	private:
		using StackArray = std::array<T, StackSize>;
		using HeapVector = std::vector<T>;

		std::variant<StackArray, HeapVector> data_;
		std::size_t size_;

		bool usingHeap() const
		{
			return std::holds_alternative<HeapVector>(data_);
		}

		void switchToHeap()
		{
			if (!usingHeap())
			{
				HeapVector heapData(std::get<StackArray>(data_).begin(), std::get<StackArray>(data_).begin() + size_);
				data_ = std::move(heapData);
			}
		}

	public:
		// Constructor
		BasicVector() : data_(StackArray{}), size_(0) {}

		// Initializer list constructor
		BasicVector(std::initializer_list<T> init) : BasicVector()
		{
			if (init.size() > StackSize)
			{
				switchToHeap();
				std::get<HeapVector>(data_) = init;
			}
			else
			{
				std::copy(init.begin(), init.end(), std::get<StackArray>(data_).begin());
			}
			size_ = init.size();
		}

		// Reserve method
		void Reserve(std::size_t newCapacity)
		{
			if (newCapacity > StackSize)
			{
				switchToHeap();
				std::get<HeapVector>(data_).reserve(newCapacity);
			}
		}

		// Push_Back method
		void PushBack(const T& item)
		{
			if (size_ >= Capacity())
			{
				switchToHeap();
				std::get<HeapVector>(data_).push_back(item);
			}
			else
			{
				if (usingHeap())
				{
					std::get<HeapVector>(data_).push_back(item);
				}
				else
				{
					std::get<StackArray>(data_)[size_] = item;
				}
			}
			++size_;
		}

		// Pop_Back method
		void PopBack()
		{
			if (size_ == 0)
			{
				throw std::out_of_range("Vector empty");
			}
			--size_;
			if (usingHeap())
			{
				std::get<HeapVector>(data_).pop_back();
			}
		}

		// Begin method
		T* Begin()
		{
			if (usingHeap())
			{
				return std::get<HeapVector>(data_).data();
			}
			return std::get<StackArray>(data_).data();
		}

		// End method
		T* End()
		{
			return Begin() + size_;
		}

		// Size method
		[[nodiscard]] std::size_t Size() const
		{
			return size_;
		}

		[[nodiscard]] std::size_t Capacity() const
		{
			if(usingHeap())
			{
				return std::get<HeapVector>(data_).capacity();
			}
			return StackSize;
		}

		// Overloaded operator[]
		T& operator[](std::size_t pos)
		{
			if (pos >= size_)
			{
				throw std::out_of_range("Index out of range");
			}
			if (usingHeap())
			{
				return std::get<HeapVector>(data_)[pos];
			}
			return std::get<StackArray>(data_)[pos];
		}

		const T& operator[](std::size_t pos) const
		{
			if (pos >= size_)
			{
				throw std::out_of_range("Index out of range");
			}
			if (usingHeap())
			{
				return std::get<HeapVector>(data_)[pos];
			}
			return std::get<StackArray>(data_)[pos];
		}

		// Insert method
		void Insert(std::size_t position, const T& value)
		{
			if (position > size_)
			{
				throw std::out_of_range("Position out of range");
			}
			if (size_ >= Capacity())
			{
				switchToHeap();
			}
			if (usingHeap())
			{
				auto& vec = std::get<HeapVector>(data_);
				vec.insert(vec.begin() + position, value);
			}
			else
			{
				auto& arr = std::get<StackArray>(data_);
				for (std::size_t i = size_; i > position; --i)
				{
					arr[i] = arr[i - 1];
				}
				arr[position] = value;
			}
			++size_;
		}

		// Erase method
		void Erase(std::size_t position)
		{
			if (position >= size_)
			{
				throw std::out_of_range("Position out of range");
			}
			if (usingHeap())
			{
				auto& vec = std::get<HeapVector>(data_);
				vec.erase(vec.begin() + position);
			}
			else
			{
				auto& arr = std::get<StackArray>(data_);
				for (std::size_t i = position; i < size_ - 1; ++i)
				{
					arr[i] = arr[i + 1];
				}
			}
			--size_;
		}

		// Method to check if using heap storage
		bool UsingHeap() const
		{
			return usingHeap();
		}
	};

} // namespace core

#endif // CORE_CONTAINERS_BASIC_VECTOR_H_
