#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <stdlib.h>
#include <vector>
#include <limits>
#include "digraph.h"
#include "hollowheap.hpp"

void dijkstra(Digraph &graph, unsigned src, vector<unsigned> &dist);

#endif
