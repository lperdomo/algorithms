#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "dijkstra.h"

using namespace std;

void read_dimacs(istream& in, unsigned & n, unsigned & m, Digraph& a) {
	string line="", dummy;
	while (line.substr(0,4) != "p sp")
		getline(in,line);
	stringstream linestr;
	linestr.str(line);
	linestr >> dummy >> dummy >> n >> m;
	a = DIGRAPH_init(n);
	unsigned i = 0;
	while (i < m) {
		getline(in,line);
		if (line.substr(0,2) == "a ") {
			stringstream arc(line);
			unsigned u,v,w;
			char ac;
			arc >> ac >> u >> v >> w;
			DIGRAPH_insertArc(a, u, v, w);
			i++;
		}
	}
}

int main(int argc, char *argv[])
{
	unsigned src = atoi(argv[1]);
	double dst = atof(argv[2]);

	unsigned n, m;

	Digraph graph;
	read_dimacs(cin, n, m, graph);
	//cout << "DIMACS file loaded!" << endl;
	//srand(time(NULL));
	//src = rand()%n;
	//dst = rand()%n;

	vector<unsigned> dist;
	dijkstra(graph, src, dist);
	//cout << "Source: " << src+1 << " Destination: " << dst+1 << " Distance: ";
	if (dist[dst] == numeric_limits<unsigned>::max()) {
		cout << "INF" << endl;
	} else {
		cout << dist[dst] << endl;
	}

	return 0;
}
