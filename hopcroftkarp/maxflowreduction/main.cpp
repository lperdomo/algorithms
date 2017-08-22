
#include <cassert>
#include <stdlib.h>
#include <string>
//#include <chrono>
#include <iostream>

#include "fattestpath.h"

using namespace std;

void read_dimacs(long &source, long &sink, long &highestFlow, long &flowSum, Graph& graph) {
    long highest = 0;
	string lineType, line = "", dummy;
	set<long> s, t;
	while (cin) {
		getline(cin,line);
		lineType = line.substr(0,2);
		stringstream lineStream(line);
		if (lineType == "e ") {
			long u,v;
			char ac;
			lineStream >> ac >> u >> v;
			if (u != v) {
                Edge e = add_edge(u, v, graph).first;
                s.insert(u);
                t.insert(v);
                graph[e].capacity = 1;
                flowSum += 1;
                if (u > highest) highest = u;
                if (v > highest) highest = v;
            }
		}
	}
	source = highest+1;
	sink = highest+2;
	set<long>::iterator it;
	for (it = s.begin(); it != s.end(); ++it) {
        Edge e = add_edge(source, *it, graph).first;
        graph[e].capacity = 1;
	}
	for (it = t.begin(); it != t.end(); ++it) {
        Edge e = add_edge(*it, sink, graph).first;
        graph[e].capacity = 1;
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
	FattestPath *fattestPath = new FattestPath(graph, 2*num_edges(graph)*flowSum+1);
	//chrono::system_clock::time_point t = chrono::system_clock::now();
	fattestPath->findFattest(source, sink);
	if (fattestPath->getResult() > -1) {
		cout << fattestPath->getResult() << endl;
	} else {
		cout << "INF" << endl;
	}
	//cerr << highestFlow
   	//	 << " " << fattestPath->getVertexes()
	//	 << " " << fattestPath->getEdges()
	//	 << " " << fattestPath->getIterations()
	//	 << " " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() << endl;
}
