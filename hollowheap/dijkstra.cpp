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
	HHItem *current, item;
    pair<boost::graph_traits<Graph>::adjacency_iterator, boost::graph_traits<Graph>::adjacency_iterator> neighbours;
	distance.clear();
	HollowHeap q;
	for (long i = 0; i <= boost::num_vertices(graph); i++) {
		distance.push_back(numeric_limits<long>::max());
		q.aux.push_back(NULL);
	}
	distance[source] = 0;
	q.insert(new HHNode(0, new HHItem(source)));

	while (q.size > 0) {
		current = q.deleteMin();
		neighbours = boost::adjacent_vertices(boost::vertex(current->value, graph), graph);
		while (neighbours.first != neighbours.second) {
			Edge e = boost::edge(current->value, *neighbours.first, graph).first;
			if (distance[*neighbours.first] == numeric_limits<long>::max()) {
				distance[*neighbours.first] = distance[current->value] + graph[e].weight;
				q.insert(new HHNode(distance[*neighbours.first], new HHItem(*neighbours.first)));
			} else if ((distance[current->value] + graph[e].weight) < distance[*neighbours.first]) {
				distance[*neighbours.first] = distance[current->value] + graph[e].weight;
				q.decreaseKey(new HHNode(distance[*neighbours.first], new HHItem(*neighbours.first)), distance[*neighbours.first]);
			}
			neighbours.first++;
		}
	}
}
