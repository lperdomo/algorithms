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
	flow.clear();
	for (long i = 0; i <= this->vertexes; i++) {
		previous[i] = 0;
		visited[i] = false;
		capacities[i] = -1;
	}
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
	this->reset();
	this->source = source;
	this->sink = sink;
	capacities[source] = 0;
	pair<graph_traits<Graph>::adjacency_iterator, graph_traits<Graph>::adjacency_iterator> neighbours;
	HeapB *priorityQueue = new HeapB();
	Node current = priorityQueue->makeNode(source, 0);
	priorityQueue->insert(current);
	while (priorityQueue->size() > 0) {
		found = false;
		current = priorityQueue->deleteMax();
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
					priorityQueue->insert(key, capacities[key]);
					previous[key] = current.first;
				} else if (getMin(current.second, graph[e].capacity) > capacities[key]) {
					capacities[key] = getMin(current.second, graph[e].capacity);
					priorityQueue->update(key, capacities[key]);
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
