
#include <cassert>
#include <stdlib.h>
#include <string>
//#include <chrono>
#include <iostream>

#include "fattestpath.h"

using namespace std;

void read_dimacs(long &source, long &sink, long &highestFlow, long &flowSum, Graph& graph) {
	source = 0;
	sink = 0;
	string lineType, line = "", dummy;
	while (cin) {
		getline(cin,line);
		lineType = line.substr(0,2);
		stringstream lineStream(line);
		if (lineType == "a ") {
			long u,v,w;
			char ac;
			lineStream >> ac >> u >> v >> w;
			Edge e = add_edge(u, v, graph).first;
		    graph[e].capacity = w;
		    flowSum += w;
		    if (highestFlow < graph[e].capacity) {
		    	highestFlow = graph[e].capacity;
		    }
		} else if (lineType == "n ") {
			if (source == 0) {
				lineStream >> dummy >> source >> dummy;
			} else {
				lineStream >> dummy >> sink >> dummy;
			}
		}
	}
}

int main (int argc, char *argv[])
{
	assert(argc == 1);
	long source = 0;
	long sink = 0;
	long highestFlow = 0;
	long flowSum = 0;

	Graph graph;
	read_dimacs(source, sink, highestFlow, flowSum, graph);

	FattestPath *fattestPath = new FattestPath(graph, 2*num_edges(graph)*log(flowSum)+1);
	//chrono::system_clock::time_point t = chrono::system_clock::now();
	fattestPath->findFattest(source, sink);
	if (fattestPath->getResult() > -1) {
		cout << fattestPath->getResult() << endl;
	} else {
		cout << "INF" << endl;
	}
	/*cerr << highestFlow
   		 << " " << fattestPath->getVertexes()
		 << " " << fattestPath->getEdges()
		 << " " << fattestPath->getIterations()
		 << " " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() << endl;*/
}
