#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <stdexcept>


template <class T, class C = std::greater<T>>
class IndexPriorityQueue
{
public:
	IndexPriorityQueue();
	IndexPriorityQueue(const IndexPriorityQueue& other);
	IndexPriorityQueue(const IndexPriorityQueue&& other);
	IndexPriorityQueue& operator= (const IndexPriorityQueue& other);
	IndexPriorityQueue& operator= (const IndexPriorityQueue&& other);

	void Insert(const size_t idx, const T& t);
	void Update(const size_t idx, const T& t);
	size_t Pop();
	inline size_t GetSize() const { return size_; }
	inline bool IsEmpty() const { return size_ == 0; }
	inline bool DoesContain(const size_t idx) const;

private:
	inline size_t Parent(const size_t idx) { return idx > 0 ? (idx - 1) / 2 : 0; }
	inline size_t LeftChild(const size_t idx) { return (idx * 2) + 1; }
	inline size_t RightChild(const size_t idx) { return LeftChild(idx) + 1; }
	void Sink(const size_t idx);
	void Swim(const size_t idx);
	void Swap(const size_t idx1, const size_t idx2);

	C comparer_;
	size_t size_;
	std::vector<T> data_;
	std::unordered_map<size_t, size_t> queue_to_idx_;
	std::unordered_map<size_t, size_t> idx_to_queue_;
};


template <class T, class C>
IndexPriorityQueue<T, C>::IndexPriorityQueue()
{
	comparer_ = C();
	size_ = 0;
	data_.resize(10);
}

template <class T, class C>
IndexPriorityQueue<T, C>::IndexPriorityQueue(const IndexPriorityQueue& other) : IndexPriorityQueue<T, C>()
{
	data_ = other.data_;
	queue_to_idx_ = other.queue_to_idx_;
	idx_to_queue_ = other.idx_to_queue_;
	size_ = other.size_;
}

template <class T, class C>
IndexPriorityQueue<T, C>::IndexPriorityQueue(const IndexPriorityQueue&& other) : IndexPriorityQueue<T, C>()
{
	data_ = move(other.data_);
	queue_to_idx_ = move(other.queue_to_idx_);
	idx_to_queue_ = move(other.idx_to_queue_);
	size_ = other.size_;
}

template <class T, class C>
IndexPriorityQueue<T, C>& IndexPriorityQueue<T, C>::operator= (const IndexPriorityQueue& other)
{
	data_ = other.data_;
	queue_to_idx_ = other.queue_to_idx_;
	idx_to_queue_ = other.idx_to_queue_;
	size_ = other.size_;
	return *this;
}

template <class T, class C>
IndexPriorityQueue<T, C>& IndexPriorityQueue<T, C>::operator= (const IndexPriorityQueue&& other)
{
	data_ = move(other.data_);
	queue_to_idx_ = move(other.queue_to_idx_);
	idx_to_queue_ = move(other.idx_to_queue_);
	size_ = other.size_;
	return *this;
}

template <class T, class C>
bool IndexPriorityQueue<T, C>::DoesContain(const size_t idx) const
{
	for (size_t i = 0; i < size_; ++i)
	{
		if (queue_to_idx_.at(i) == idx)
		{
			return true;
		}
	}
	return false;
}

template <class T, class C>
void IndexPriorityQueue<T, C>::Insert(const size_t idx, const T& t)
{
	if (DoesContain(idx))
	{
		throw new std::invalid_argument("Index already inserted");
	}

	data_[size_] = t;
	queue_to_idx_[size_] = idx;
	idx_to_queue_[idx] = size_;
	size_++;
	if (data_.size() * 0.75 < size_)
	{
		data_.resize(data_.size() * 2);
	}
	Swim(size_ - 1);
}

template <class T, class C>
void IndexPriorityQueue<T, C>::Update(const size_t idx, const T& t)
{
	if (!DoesContain(idx))
	{
		throw new std::out_of_range("Invalid index");
	}

	const size_t queue_idx = idx_to_queue_[idx];
	data_[queue_idx] = t;
	Sink(queue_idx);
	Swim(queue_idx);
}

template <class T, class C>
size_t IndexPriorityQueue<T, C>::Pop()
{
	Swap(0, --size_);
	Sink(0);
	if (size_ < data_.size() * 0.20)
	{
		data_.resize(data_.size() / 2);
	}
	return queue_to_idx_[size_];
}

template <class T, class C>
void IndexPriorityQueue<T, C>::Sink(const size_t idx)
{
	const size_t left_idx = LeftChild(idx);
	const size_t right_idx = RightChild(idx);

	size_t candidate_idx;
	if (right_idx < size_)
	{
		candidate_idx = comparer_(data_[left_idx], data_[right_idx]) ? left_idx : right_idx;
	}
	else if (left_idx < size_)
	{
		candidate_idx = left_idx;
	}
	else
	{
		return;
	}

	if (comparer_(data_[idx], data_[candidate_idx]))
	{
		Swap(idx, candidate_idx);
		Sink(candidate_idx);
	}
}

template <class T, class C>
void IndexPriorityQueue<T, C>::Swim(const size_t idx)
{
	if (size_ <= idx)
	{
		throw new std::out_of_range("Invalid index");
	}
	else if (idx == 0)
	{
		return;
	}

	const size_t parent_idx = Parent(idx);
	if (comparer_(data_[idx], data_[parent_idx]))
	{
		Swap(idx, parent_idx);
		Swim(parent_idx);
	}
}

template <class T, class C>
void IndexPriorityQueue<T, C>::Swap(const size_t idx1, const size_t idx2)
{
	std::swap(data_[idx1], data_[idx2]);
	std::swap(queue_to_idx_[idx1], queue_to_idx_[idx2]);
	std::swap(idx_to_queue_[queue_to_idx_[idx1]], idx_to_queue_[queue_to_idx_[idx2]]);
}
