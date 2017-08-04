#ifndef HIERHOLZER_H
#define HIERHOLZER_H

#include "util.h"

class Hierholzer
{
public:
    Hierholzer();
    void run(Graph &g);
    bool hasEulerTour(Graph &g);
    void sanityTourCheck(Graph &g);
    std::vector<Edge> tour;
private:
    std::vector<unsigned> getCounts(Graph &g);
};

class DFSEulerVisitor : public boost::default_dfs_visitor
{
public:
    DFSEulerVisitor(unsigned* counts) : counts(counts)
    {
    }

    void finish_vertex(Vertex u, const Graph &g) const
    {
        if (counts[0] > 2) {
            return;
        }
        unsigned edges = 0;
        for (std::pair<AdjacencyIterator, AdjacencyIterator> it = boost::adjacent_vertices(u, g); it.first != it.second; ++it.first) edges++;
        if (edges % 2 == 1) counts[0]++;
    }

    void start_vertex(Vertex u, const Graph &g)
    {
        if (counts[1] > 1) {
            return;
        }
        counts[1]++;
    }

private:
    unsigned* counts;
};

#endif // HIERHOLZER_H
