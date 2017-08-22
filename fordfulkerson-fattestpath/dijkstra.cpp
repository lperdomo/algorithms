#include "dijkstra.h"

using namespace std;
using namespace boost;

Dijkstra::Dijkstra(Graph graph)
{
	this->graph = graph;
	edges = num_edges(graph);
	vertexes = num_vertices(graph);
	previous.resize(this->vertexes+1);
	visited.resize(this->vertexes+1);
	capacities.resize(this->vertexes+1);
	idMap = get(vertex_index, graph);

}

Dijkstra::~Dijkstra()
{
}

long Dijkstra::getEdges()
{
	return edges;
}

long Dijkstra::getVertexes()
{
	return vertexes;
}

void Dijkstra::setGraph(Graph graph)
{
	this->graph = graph;
}

long Dijkstra::getMin(long value1, long value2)
{
	if (value1 < value2 && value1 > 0) {
		return value1;
	}
	return value2;
}

void Dijkstra::reset()
{

}

void Dijkstra::buildFlow()
{
	stack<long> flowAux;
	long previousId = sink;
	while (previousId != source) {
		flowAux.push(previousId);
		previousId = previous[previousId];
	}

	flowAux.push(source);

	while (!flowAux.empty()) {
		this->flow.push_back(flowAux.top());
		flowAux.pop();
	}
}

vector<long> Dijkstra::findFlow(long source, long sink)
{
	bool found;
	this->source = source;
	this->sink = sink;
	capacities[source] = 0;
	pair<graph_traits<Graph>::adjacency_iterator, graph_traits<Graph>::adjacency_iterator> neighbours;
	HeapN q(2);

	flow.clear();
	for (long i = 0; i <= this->vertexes; i++) {
		previous[i] = 0;
		visited[i] = false;
		capacities[i] = -1;
		q.map.push_back(0);
	}

	Node current = q.makeNode(source, 0);
	q.insert(current);
	while (q.size() > 0) {
		found = false;
		current = q.deleteMax();
		visited[current.first] = true;
		if (current.first == this->sink) {
			found = true;
			break;
		}
		neighbours = adjacent_vertices(vertex(current.first, graph), graph);
		while (neighbours.first != neighbours.second) {
			long key = idMap[*neighbours.first];
			Edge e = edge(current.first, key, graph).first;
			if (graph[e].capacity > 0 && !visited[key]) {
				found = true;
				if (capacities[key] < 0) {
					capacities[key] = getMin(current.second, graph[e].capacity);
					q.insert(q.makeNode(key, capacities[key]));
					previous[key] = current.first;
				} else if (getMin(current.second, graph[e].capacity) > capacities[key]) {
					capacities[key] = getMin(current.second, graph[e].capacity);
					q.update(q.makeNode(key, capacities[key]));
					previous[key] = current.first;
				}
			}
			neighbours.first++;
		}
	}

	if (found) {
		this->buildFlow();
	}

	return this->flow;
}
