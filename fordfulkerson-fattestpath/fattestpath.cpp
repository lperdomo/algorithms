#include "fattestpath.h"

FattestPath::FattestPath(Graph graph, long iterationLimit)
{
	this->graph = graph;
	this->iterationLimit = iterationLimit;
	dijkstra = new Dijkstra(graph);
	capacityMax = numeric_limits<long>::max();
	iterations = 0;
	result = 0;
}

FattestPath::~FattestPath()
{

}

long FattestPath::getResult()
{
	return result;
}

long FattestPath::getIterations()
{
	return iterations;
}

long FattestPath::getEdges()
{
	return dijkstra->getEdges();
}

long FattestPath::getVertexes()
{
	return dijkstra->getVertexes();
}

long FattestPath::bottleneck(vector<long> flow, Graph graph)
{
	long capacityMin = capacityMax;
	for (long i = 0; i < flow.size()-1; i++) {
		Edge e = edge(flow[i], flow[i+1], graph).first;
		if (graph[e].capacity < capacityMin) {
			capacityMin = graph[e].capacity;
		}
	}
	return capacityMin;
}

void FattestPath::findFattest(long source, long sink)
{
	iterations = 0;
	result = 0;
	while (iterations < iterationLimit) {
		long capacity = 0;
		dijkstra->setGraph(graph);
		vector<long> flow = dijkstra->findFlow(source, sink);
		if (flow.size() > 0) {
			capacity = bottleneck(flow, graph);
		}
		if (capacity == 0) {
			return;
		}
		for (long i = 0; i < flow.size()-1; i++) {
			Edge e = edge(flow[i], flow[i+1], graph).first;
			graph[e].capacity -= capacity;

			pair<Edge, bool> residual = edge(flow[i+1], flow[i], graph);
			if (!residual.second) {
				residual = add_edge(flow[i+1], flow[i], graph);
				graph[residual.first].capacity = capacity;
			} else {
				graph[residual.first].capacity += capacity;
			}
		}
		result += capacity;
		iterations++;
	}
	result = -1;
}
