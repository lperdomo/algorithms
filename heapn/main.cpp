#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "dijkstra.h"

int main(int argc, char *argv[])
{
	unsigned source = atoi(argv[1])-1;
	double destination = atof(argv[2])-1;

	Dijkstra dijkstra;
	dijkstra.readDimacsFile(cin);
	dijkstra.run(source);
	if (dijkstra.distance[destination] == numeric_limits<long>::max()) {
		std::cout << "INF" << std::endl;
	} else {
		std::cout << dijkstra.distance[destination] << std::endl;
	}

	return 0;
}
