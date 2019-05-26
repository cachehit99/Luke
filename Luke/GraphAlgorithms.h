#pragma once
#include "Graph.h"
#include "IndexPriorityQueue.h"


class GraphAlgorithms
{
public:
	static std::vector<size_t> ShortestPath(const IGraph& graph, const int s)
	{
		const size_t num_vertex = graph.GetNumVertex();
		if (!graph.IsValidVertex(s))
		{
			throw new std::invalid_argument("Inavlid source vertex");
		}

		std::vector<size_t> vertex_to(num_vertex);
		std::vector<double> weight_to(num_vertex, std::numeric_limits<double>::infinity());
		weight_to[s] = 0.0;

		IndexPriorityQueue<double> queue;
		queue.Insert(s, 0.0);

		while (!queue.IsEmpty())
		{
			const size_t from = queue.Pop();

			for (auto& e : graph.GetAdjacents(from))
			{
				const size_t to = e.GetTo();
				if (weight_to[to] > weight_to[from] + e.GetWeight())
				{
					weight_to[to] = weight_to[from] + e.GetWeight();
					vertex_to[to] = from;
					if (queue.DoesContain(to))
					{
						queue.Update(to, weight_to[to]);
					}
					else
					{
						queue.Insert(to, weight_to[to]);
					}
				}
			}
		}

		return vertex_to;
	}
};
