#include <math.h>
#include "dijkstra.h"

#include <iostream>
using namespace std;

void dijkstra(Digraph &graph, unsigned src, vector<unsigned> &dist)
{
	Arc aux;
	HHEAP_item currentv, item;
	HHEAP_node node;
	hheap heap;
	unsigned adj, i;

	dist.clear();
	for (i = 0; i <= graph->vertexes; i++) {
		dist.push_back(numeric_limits<unsigned>::max());
	}
	dist[src] = 0;
	HHEAP_makeHeap(heap);
	HHEAP_resizeAux(heap, graph->vertexes);
	HHEAP_insert(heap, 0, HHEAP_newItem(src));

	while (heap->size > 0) {
		currentv = HHEAP_deleteMin(heap);
		for (aux = graph->adj[currentv->value]; aux != NULL; aux = aux->next) {
			adj = aux->component;
			if (dist[adj] == numeric_limits<unsigned>::max()) {
				dist[adj] = dist[currentv->value] + aux->weight;
				HHEAP_insert(heap, dist[adj], HHEAP_newItem(adj));
			} else if ((dist[currentv->value] + aux->weight) < dist[adj]) {
				dist[adj] = dist[currentv->value] + aux->weight;
				item = HHEAP_newItem(adj);
				node = HHEAP_newNode(dist[adj], item);
				HHEAP_decreaseKey(heap, node, dist[adj]);
			}
		}
	}

	delete heap;
}



