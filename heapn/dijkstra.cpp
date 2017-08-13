#include "dijkstra.h"

using namespace std;

void dijkstra(Digraph &graph, unsigned src, vector<unsigned> &dist)
{
	Arc aux;
	Node currentv;
	vector<Node> heapn;
	vector<unsigned> map;
	unsigned adj, i;

	dist.clear();
	for (i = 0; i <= graph->vertexes; i++) {
		dist.push_back(numeric_limits<unsigned>::max());
		map.push_back(0);
	}
	dist[src] = 0;
	HEAPN_insert(heapn, map, HEAPN_node(src, 0));
	while (!heapn.empty()) {
		currentv = HEAPN_deleteMin(heapn, map);
		for (aux = graph->adj[currentv->component]; aux != NULL; aux = aux->next) {
			adj = aux->component;
			if (dist[adj] == numeric_limits<unsigned>::max()) {
				dist[adj] = dist[currentv->component] + aux->weight;
				HEAPN_insert(heapn, map, HEAPN_node(adj, dist[adj]));
			} else if ((dist[currentv->component] + aux->weight) < dist[adj]) {
				dist[adj] = dist[currentv->component] + aux->weight;
                HEAPN_update(heapn, map, HEAPN_node(adj, dist[adj]));
			}
		}
	}
}



