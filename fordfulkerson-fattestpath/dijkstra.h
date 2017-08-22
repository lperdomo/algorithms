#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <cassert>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <iterator>
#include <sstream>
#include <limits>
#include <math.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <iostream>

#include "heapn.h"

using namespace std;
using namespace boost;

struct VertexInformation {
  unsigned component;
};

struct EdgeInformation {
  unsigned capacity;
};

typedef adjacency_list<vecS, vecS, directedS,VertexInformation,EdgeInformation> Graph;
typedef graph_traits <Graph>::edge_descriptor Edge;

class Dijkstra {
	public:
		Dijkstra(Graph graph);
		~Dijkstra();
		void setGraph(Graph graph);
		vector<long> findFlow(long source, long sink);
		long getEdges();
		long getVertexes();
	private:
		long source;
		long sink;
		long edges;
		long vertexes;
		Graph graph;
		property_map<Graph, vertex_index_t>::type idMap;
		vector<long> flow;
		vector<long> previous;
		vector<bool> visited;
		vector<long> capacities;
		long getMin(long value1, long value2);
		void reset();
		void buildFlow();
};

#endif
