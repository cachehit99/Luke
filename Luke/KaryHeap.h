#pragma once
#include <vector>

template <class T, class C = greater<T>>
class KaryHeap
{
public:
	KaryHeap(const size_t k);
	KaryHeap(const KaryHeap& other);
	KaryHeap(const KaryHeap&& other);
	KaryHeap& operator= (const KaryHeap& other);
	KaryHeap& operator= (const KaryHeap&& other);

	void Insert(const T& t);
	T RemoveTop();
	inline size_t Size() const { return size_; }
	inline size_t K() const { return k_; }

private:
	inline size_t Parent(const size_t idx) { return idx > 0 ? (idx - 1) / k_ : 0; }
	inline size_t FirstChild(const size_t idx) { return (idx * k_) + 1; }
	void Sink(const size_t idx);
	void Swim(const size_t idx);
	
	C comparer_;
	size_t size_;
	size_t k_;
	std::vector<T> data_;
};


template <class T, class C>
KaryHeap<T, C>::KaryHeap(const size_t k)
{
	comparer_ = C();
	k_ = k;
	size_ = 0;
	data_.resize(10);
}

template <class T, class C>
KaryHeap<T, C>::KaryHeap(const KaryHeap& other) : KaryHeap<T, C>(other.k_)
{
	data_ = other.data_;
	size_ = other.size_;
}

template <class T, class C>
KaryHeap<T, C>::KaryHeap(const KaryHeap&& other) : KaryHeap<T, C>(other.k_)
{
	data_ = move(other.data_);
	size_ = other.size_;
}

template <class T, class C>
KaryHeap<T, C>& KaryHeap<T, C>::operator= (const KaryHeap& other)
{
	k_ = other.k_;
	data_ = other.data_;
	size_ = other.size_;
	return *this;
}

template <class T, class C>
KaryHeap<T, C>& KaryHeap<T, C>::operator= (const KaryHeap&& other)
{
	k_ = other.k_;
	data_ = move(other.data_);
	size_ = other.size_;
	return *this;
}

template <class T, class C>
void KaryHeap<T, C>::Insert(const T& t)
{
	data_[size_++] = t;
	if (data_.size() * 0.75 < size_)
	{
		data_.resize(data_.size() * 2);
	}
	Swim(size_ - 1);
}

template <class T, class C>
T KaryHeap<T, C>::RemoveTop()
{
	std::swap(data_[0], data_[--size_]);
	Sink(0);
	if (size_ < data_.size() * 0.20)
	{
		data_.resize(data_.size() / 2);
	}
	return data_[size_];
}

template <class T, class C>
void KaryHeap<T, C>::Sink(const size_t idx)
{
	const size_t first_child_idx = FirstChild(idx);
	if (size_ <= first_child_idx)
	{
		return;
	}

	size_t cadidate_idx = first_child_idx;
	T candidate_value = data_[first_child_idx];

	for (int i = 1; i < k_; ++i)
	{
		if (size_ <= first_child_idx + i)
		{
			break;
		}
		if (comparer_(data_[first_child_idx + i], candidate_value))
		{
			cadidate_idx = first_child_idx + i;
			candidate_value = data_[first_child_idx + i];
		}
	}

	if (comparer_(candidate_value, data_[idx]))
	{
		std::swap(data_[idx], data_[cadidate_idx]);
		Sink(cadidate_idx);
	}
}

template <class T, class C>
void KaryHeap<T, C>::Swim(const size_t idx)
{
	if (idx == 0)
	{
		return;
	}

	const size_t parent_idx = Parent(idx);
	if (comparer_(data_[idx], data_[parent_idx]))
	{
		std::swap(data_[parent_idx], data_[idx]);
		Swim(parent_idx);
	}
}
