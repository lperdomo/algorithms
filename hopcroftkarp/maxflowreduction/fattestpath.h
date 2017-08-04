#ifndef FATTESTPATH_H_
#define FATTESTPATH_H_

#include "dijkstra.h"

class FattestPath {
public:
	FattestPath(Graph graph, long iterationLimit);
	~FattestPath();
	void findFattest(long source, long sink);
	long bottleneck(vector<long> flow, Graph graph);
	long getResult();
	long getIterations();
	long getEdges();
	long getVertexes();

private:
	long result;
	long iterations;
	long iterationLimit;
	long capacityMax;
	Graph graph;
	Dijkstra *dijkstra;
};

#endif
