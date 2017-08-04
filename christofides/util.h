#ifndef GRAPH_H
#define GRAPH_H

#include <cmath>

#include <boost/array.hpp>
#include <boost/heap/fibonacci_heap.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/undirected_dfs.hpp>

struct VertexInformation { };
//struct VertexInformation { double x; double y; };
struct EdgeInformation { long id; long weight; };
//typedef boost::adjacency_matrix<boost::undirectedS, VertexInformation, EdgeInformation> Graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexInformation, EdgeInformation> Graph;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;

struct compareWeight
{
	bool operator() (const std::pair<Vertex, long>& a, const std::pair<Vertex, long>& b) const
	{
		return a.second > b.second;
	}
};

typedef boost::heap::fibonacci_heap< std::pair<Vertex,long>, boost::heap::compare<compareWeight>, boost::heap::mutable_<true> > FibonnaciHeap;
typedef boost::heap::fibonacci_heap< std::pair<Vertex,long>, boost::heap::compare<compareWeight>, boost::heap::mutable_<true> >::handle_type FibonnaciHeapHandle;

class Util
{
public:
    Util() { }
    static double euclideanDistance(double x1, double y1, double x2, double y2)
    {
        return lrint(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
    }
};

#endif // GRAPH_H
