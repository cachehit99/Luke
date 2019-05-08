#pragma once
#include <iostream>
#include "KaryHeap.h"


class Coord
{
public:
	Coord(const double& x = 0.0, const double& y = 0.0)
	{
		x_ = x;
		y_ = y;
	}
	inline double get_x() const { return x_; }
	inline double get_y() const { return y_; }
private:
	double x_;
	double y_;
};

struct CoordComparater
{
	bool operator() (const Coord& c1, const Coord& c2)
	{
		if (c1.get_x() < c2.get_x())
		{
			return true;
		}
		else if (c1.get_x() > c2.get_x())
		{
			return false;
		}
		else
		{
			return c1.get_y() < c2.get_y();
		}
	}
};

std::ostream& operator<< (std::ostream& os, const Coord& coord)
{
	os << "[" << coord.get_x() << ", " << coord.get_y() << "]";
	return os;
}

void TestKaryHeap()
{
	KaryHeap<Coord, CoordComparater> min_heap(3);

	min_heap.Insert({ 3, 8 });
	min_heap.Insert({ 1, 1 });
	min_heap.Insert({ 8, 10 });
	min_heap.Insert({ 1, 2 });
	min_heap.Insert({ 2, 3 });
	min_heap.Insert({ 4, 2 });
	min_heap.Insert({ 10, 4 });
	min_heap.Insert({ 6 ,3 });
	min_heap.Insert({ 7 ,6 });
	min_heap.Insert({ 9, 8 });
	min_heap.Insert({ 3, 5 });
	min_heap.Insert({ 5, 5 });

	const size_t size = min_heap.Size();
	for (int i = 0; i < size; ++i)
	{
		const Coord min_value = min_heap.RemoveTop();
		std::cout << min_value << std::endl;
	}
}
