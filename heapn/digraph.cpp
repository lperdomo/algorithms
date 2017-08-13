#include "digraph.h"

using namespace std;

Digraph DIGRAPH_init(unsigned vertexes)
{
   Digraph graph = (Digraph)malloc(sizeof(Digraph));
   graph->vertexes = vertexes;
   graph->arcs = 0;
   graph->adj = (Arc*)malloc((vertexes+1) * sizeof(Arc));
   for (unsigned i = 0; i <= vertexes; i++) {
	   graph->adj[i] = NULL;
   }
   return graph;
}

Arc DIGRAPH_arc(unsigned component, unsigned weight, Arc next)
{
    Arc current = (Arc)malloc(sizeof(struct arc));
    current->component = component;
    current->weight = weight;
    current->next = next;
    return current;
}

void DIGRAPH_insertArc(Digraph &graph, unsigned index, unsigned component, unsigned weight)
{
	Arc current = graph->adj[index];
	for (current = graph->adj[index]; current != NULL; current = current->next) {
		if (current->component == component) return;
	}
	graph->adj[index] = DIGRAPH_arc(component, weight, graph->adj[index]);

	graph->arcs++;
}
