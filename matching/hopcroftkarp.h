#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
//#include <chrono>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>

using namespace std;
using namespace boost;


struct VertexInformation {
  unsigned component;
};

struct EdgeInformation {
  unsigned capacity;
};

typedef adjacency_list<vecS, vecS, undirectedS,VertexInformation,EdgeInformation> Graph;
typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::adjacency_iterator adjacency_it;

class HopcroftKarp {
 public:
    HopcroftKarp();
    void findMaxMatching();

 private:
    Graph g;
    long vertices;
    long edges;
    map<long, long> matchingLeft;
    map<long, long> matchingRight;
    map<long, long> distanceLeft;
    map<long, long> distanceRight;
    //chrono::system_clock::time_point timeInit;
    long expectedResult;
    long matchings;
    long phases;
    long maximalExtraction;
    void inputDIMACSfile();
    void init();
    void reset();
    void result();
    bool breadthFirstSearch();
    bool depthFirstSearch(long left);

};
