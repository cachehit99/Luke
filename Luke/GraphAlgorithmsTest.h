#pragma once
#include "GraphAlgorithms.h"

void TestShortestPath()
{
	DirectedGraph graph(8);
	graph.AddEdge({ 0, 1, 5.0 });
	graph.AddEdge({ 0, 4, 9.0 });
	graph.AddEdge({ 0, 7, 8.0 });
	graph.AddEdge({ 1, 2, 12.0});
	graph.AddEdge({ 1, 3, 15.0 });
	graph.AddEdge({ 1, 7, 4.0 });
	graph.AddEdge({ 2, 3, 3.0 });
	graph.AddEdge({ 2, 6, 11.0 });
	graph.AddEdge({ 3, 6, 9.0 });
	graph.AddEdge({ 4, 5, 4.0 });
	graph.AddEdge({ 4, 6, 20.0 });
	graph.AddEdge({ 4, 7, 5.0 });
	graph.AddEdge({ 5, 2, 1.0 });
	graph.AddEdge({ 5, 6, 13.0 });
	graph.AddEdge({ 7, 5, 6.0 });
	graph.AddEdge({ 7, 2, 7.0 });

	auto shortest = GraphAlgorithms::ShortestPath(graph, 0);
	cout << "";
}