#include "dijkstra.h"

Dijkstra::Dijkstra()
{
}

Dijkstra::Dijkstra(Graph graph)
{
    this->graph = graph;
    this->vertices = boost::num_vertices(graph);
}

Dijkstra::~Dijkstra()
{
}

void Dijkstra::readDimacsFile(istream& in) {
	string line="", dummy;
	while (line.substr(0,4) != "p sp")
		getline(in,line);
	stringstream linestr;
	linestr.str(line);
	unsigned i = 0, n, m;
	linestr >> dummy >> dummy >> n >> m;
	while (i < m) {
		getline(in,line);
		if (line.substr(0,2) == "a ") {
			stringstream arc(line);
			unsigned u,v,w;
			char ac;
			arc >> ac >> u >> v >> w;
			Edge e = add_edge(u, v, graph).first;
		    graph[e].weight = w;
			i++;
		}
	}
	this->vertices = boost::num_vertices(graph);
}

void Dijkstra::run(long source)
{
	Node current;
	pair<boost::graph_traits<Graph>::adjacency_iterator, boost::graph_traits<Graph>::adjacency_iterator> neighbours;

	HeapN q(4);
	distance.clear();
	for (long i = 0; i <= this->vertices; i++) {
		distance.push_back(numeric_limits<long>::max());
		q.map.push_back(0);
	}

	distance[source] = 0;
	q.insert(q.makeNode(source, 0));
	while (!q.empty()) {
		current = q.deleteMin();

		neighbours = boost::adjacent_vertices(boost::vertex(current.first, graph), graph);
		while (neighbours.first != neighbours.second) {
			Edge e = boost::edge(current.first, *neighbours.first, graph).first;
			if (distance[*neighbours.first] == numeric_limits<long>::max()) {
                distance[*neighbours.first] = distance[current.first] + graph[e].weight;
				q.insert(q.makeNode(*neighbours.first, distance[*neighbours.first]));
			} else if ((distance[current.first] + graph[e].weight) < distance[*neighbours.first]) {
				distance[*neighbours.first] = distance[current.first] + graph[e].weight;
                q.update(q.makeNode(*neighbours.first, distance[*neighbours.first]));
			}
			neighbours.first++;
		}
	}
}



