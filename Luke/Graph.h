#pragma once
#include <vector>
#include <list>
#include <iterator>


class Edge
{
public:
	Edge(const size_t from, const size_t to, const double weight)
		: from_(from), to_(to), weight_(weight) {}
	Edge operator= (const Edge& other)
	{
		return Edge(other.from_, other.to_, other.weight_);
	}

	inline size_t GetFrom() const { return from_; }
	inline size_t GetTo() const { return to_; }
	inline double GetWeight() const { return weight_; }
	size_t GetOther(const size_t v) const
	{
		if (v == from_)
		{
			return to_;
		}
		else if (v == to_)
		{
			return from_;
		}
		else
		{
			throw new std::invalid_argument("Invalid vertex");
		}
	}

private:
	const size_t from_;
	const size_t to_;
	const double weight_;
};


class IGraph
{
public:
	IGraph(const size_t num_vertex)
	{
		adjacents_.resize(num_vertex);
	}
	inline size_t GetNumVertex() const { return adjacents_.size(); }
	inline bool IsValidVertex(const size_t v) const { return 0 <= v && v < GetNumVertex(); }
	virtual void AddEdge(const Edge& edge) = 0;
	std::list<Edge> GetAdjacents(const size_t vertex) const
	{
		if (adjacents_.size() <= vertex)
		{
			throw new std::out_of_range("Invalid vertex");
		}
		return adjacents_[vertex];
	}

protected:
	std::vector<std::list<Edge>> adjacents_;
};


class DirectedGraph : public IGraph
{
public:
	using IGraph::IGraph;
	virtual void AddEdge(const Edge& edge) override
	{
		const size_t from = edge.GetFrom();
		if (adjacents_.size() <= from)
		{
			throw new std::out_of_range("Invalid edge");
		}
		adjacents_[from].push_back(edge);
	}
};
