#include "hierholzer.h"

#include <iostream>

Hierholzer::Hierholzer()
{
}

std::vector<unsigned> Hierholzer::getCounts(Graph &g)
{
    std::vector<unsigned> counts(2);
    DFSEulerVisitor vis(&counts[0]);
    boost::depth_first_search(g, visitor(vis));
    return counts;
}

void Hierholzer::run(Graph &g)
{
    Vertex first;
    std::pair<VertexIterator, VertexIterator> vit = boost::vertices(g);
    unsigned adjacent;
    first = *vit.first;
    while (vit.first != vit.second) {
        adjacent = 0;
        for (std::pair<OutEdgeIterator, OutEdgeIterator> it2 = boost::out_edges(*vit.first, g); it2.first != it2.second; ++it2.first) adjacent++;
        //std::cout << "candidato" << *vit.first << " = " << adjacent << std::endl;
        if (adjacent & 1) first = *vit.first;
        ++vit.first;
    }
    //std::cout << "comeco tour" << first << std::endl;
    //std::vector<std::vector<bool> > visited(boost::num_vertices(g), std::vector<bool>(boost::num_vertices(g), false));
    std::vector<bool> visited(boost::num_edges(g), false);
    std::vector<Vertex> tmp, order;
    tmp.push_back(first);
    bool available;
    while (!tmp.empty()) {
        Vertex v = tmp.back();
        available = false;
        for (std::pair<OutEdgeIterator, OutEdgeIterator> it = boost::out_edges(v, g); it.first != it.second; ++it.first) {
            if (!visited[g[*it.first].id]) {
            //if (!visited[boost::target(*it.first, g)][boost::source(*it.first, g)]) {
                available = true;
                //std::cout << "seguiu " << boost::source(*it.first, g) << ", " << boost::target(*it.first, g) << std::endl;
                //visited[boost::target(*it.first, g)][boost::source(*it.first, g)] = true;
                //visited[boost::source(*it.first, g)][boost::target(*it.first, g)] = true;
                visited[g[*it.first].id] = true;
                //tour.push_back(boost::edge(boost::target(*it.first, g), v, g).first);
                tmp.push_back(boost::target(*it.first, g));
                break;
            }
        }
        if (!available) {
            if (!order.empty()) {
                tour.push_back(boost::edge(order.back(), v, g).first);
                order.pop_back();
            }
            order.push_back(v);
            tmp.pop_back();
        }
    }
}

void Hierholzer::sanityTourCheck(Graph &g)
{
    bool check = tour.size() == boost::num_edges(g);
    for (std::vector<Edge>::iterator ei = tour.begin(); ei != tour.end(); ei++) {
        //std::cout << "(" << boost::source(*ei, g) << "," << boost::target(*ei, g) << ")" << std::endl;
        if ((ei + 1) == tour.end()) {
            check &= (boost::target(*ei, g) == boost::source(*tour.begin(), g));
        } else {
            check &= (boost::target(*ei, g) == boost::source(*(ei + 1), g));
        }
    }
    std::cout << (check ? "tour succeded" : "tour failed") << std::endl;
}

bool Hierholzer::hasEulerTour(Graph &g)
{
    std::vector<unsigned> counts = this->getCounts(g);
    return (counts[1] == 1 && counts[0] == 0);
}
