#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <vector>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>

#include "hollowheap.hpp"

struct VertexInformation {
  unsigned component;
};

struct EdgeInformation {
  unsigned weight;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexInformation, EdgeInformation> Graph;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

class Dijkstra
{
    public:
        Dijkstra();
        Dijkstra(Graph graph);
        ~Dijkstra();
        void run(long source);
        void readDimacsFile(istream &in);
        vector<long> distance;
    private:
        Graph graph;
        long vertices;
};


#endif
