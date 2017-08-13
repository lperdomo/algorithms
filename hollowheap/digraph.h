#ifndef DIGRAPH_H_
#define DIGRAPH_H_

#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

typedef struct arc *Arc;
struct arc {
	unsigned component;
	unsigned weight;
	Arc next;
};

typedef struct digraph *Digraph;
struct digraph {
	unsigned vertexes;
	unsigned arcs;
    Arc *adj;
};

Digraph DIGRAPH_init(unsigned vertexes);

Arc DIGRAPH_arc(unsigned component, unsigned weight, Arc next);

void DIGRAPH_insertArc(Digraph &graph, unsigned index, unsigned component, unsigned weight);

void DIGRAPH_printstats(Digraph &graph);

#endif
