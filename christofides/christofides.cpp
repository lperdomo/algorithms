#include "christofides.h"

Christofides::Christofides()
{
    odd = 0;
    result = 0;
}

void Christofides::load()
{
    i.read(std::cin);
    //std::cout << "gv" << i.nodes.size() << std::endl;
}

Christofides::~Christofides()
{
    delete TuM;
}

void Christofides::extractMST()
{
    TuM = new Graph(i.dimension);
    odd = 0;

    Prim p;
    p.run(i.nodes);
    //std::cout << "mstv" << boost::num_vertices(*TuM) << std::endl;
    for (std::pair<VertexIterator, VertexIterator> it = boost::vertices(*TuM); it.first != it.second; ++it.first) {
        if (*it.first != p.mst[*it.first].first) {
            //EdgeWeightProperty w = boost::get(edge_weight_t(), *i.g, boost::edge(*it.first, pred[id], *i.g).first);
            Edge e = boost::add_edge(*it.first, p.mst[*it.first].first, *TuM).first;
            (*TuM)[e].id = boost::num_edges(*TuM);
            (*TuM)[e].weight = p.mst[*it.first].second;
            //std::cout << "[" << *it.first << "," << p.mst[*it.first].first << "]=" << (*TuM)[e].weight << std::endl;
            if (boost::out_degree(*it.first, *TuM) & 1) odd++;
            else  odd--;
            if (boost::out_degree(p.mst[*it.first].first, *TuM) & 1) odd++;
            else  odd--;
        }
    }
    //std::cout << "mste" << boost::num_edges(*TuM) << std::endl;
    //std::cout << "odd" << odd << std::endl;
}

void Christofides::extractOdds()
{
    odds.resize(odd);
    unsigned id = 0;
    for (std::pair<VertexIterator, VertexIterator> it = boost::vertices(*TuM); it.first != it.second; ++it.first) {
        if (boost::out_degree(*it.first, *TuM) & 1) {
            odds[id] = *it.first;
            id++;
        }
    }
}

void Christofides::doGreedyMatching()
{
    std::vector<Vertex> mate(odd, -1);

    unsigned v;
    long l = std::numeric_limits<long>::max(), w = 0;
    for (unsigned id = 0; id < odds.size(); id++) {
        if (mate[id] == -1) {
            l = std::numeric_limits<long>::max();
            for (unsigned id2 = 0; id2 < odds.size(); id2++) {
                if (id != id2 && mate[id2] == -1) {
                    w = Util::euclideanDistance(i.nodes[odds[id]].first, i.nodes[odds[id]].second, i.nodes[odds[id2]].first, i.nodes[odds[id2]].second);
                    if (w < l) {
                        l = w;
                        v = id2;
                    }
                }
            }
            mate[id] = v;
            mate[v] = id;
        }
    }

    std::vector<unsigned> visited(odds.size(), false);
    for (unsigned id = 0; id < odds.size(); id++) {
        //if (!boost::edge(odds[id], odds[mate[id]], *TuM).second) {
        if (!visited[id]) {
            Edge e = boost::add_edge(odds[id], odds[mate[id]], *TuM).first;
            (*TuM)[e].id = boost::num_edges(*TuM);
            (*TuM)[e].weight = Util::euclideanDistance(i.nodes[odds[id]].first, i.nodes[odds[id]].second, i.nodes[odds[mate[id]]].first, i.nodes[odds[mate[id]]].second);
            //std::cout << "push " << id << " " << mate[id] << std::endl; //" = " << (*TuM)[e].weight;
            visited[id] = true;
            visited[mate[id]] = true;
        }
    }


    //std::cout << "merge" << std::endl;
    //std::cout << "tumv" << boost::num_vertices(*TuM) << std::endl;
    //std::cout << "tumee" << boost::num_edges(*TuM) << std::endl;

    //std::cout << "odds tum" << std::endl;
    //for (std::pair<VertexIterator, VertexIterator> it = boost::vertices(*TuM); it.first != it.second; ++it.first) {
    //    if (boost::out_degree(*it.first, *TuM) & 1) {
    //       std::cout << *it.first << std::endl;
    //    }
    //}
}

void Christofides::doBlossomPerfectMatching()
{
    GeomPerfectMatching pm(odd, 2);
    //resultados mudam levemente para pr2392, rl5934, rl5915
    //pm.gpm_options.init_Delaunay = false;//processa mais rapido que KNN
    //pm.gpm_options.init_KNN = true;//consegue processar a d18512
    for (unsigned id = 0; id < odds.size(); id++) {
        GeomPerfectMatching::REAL t[2];
        t[0] = i.nodes[odds[id]].first;
        t[1] = i.nodes[odds[id]].second;
        pm.AddPoint(t);
    }

    pm.options.verbose = false;
    pm.Solve();
    //pm.SolveComplete();//usa13509, brd14501, d18512
    std::vector<unsigned> visited(odds.size(), false);

    for (unsigned id = 0; id < odds.size(); id++) {
        if (!visited[id]) {
            Edge e = boost::add_edge(odds[id], odds[pm.GetMatch(id)], *TuM).first;
            (*TuM)[e].id = boost::num_edges(*TuM);
            (*TuM)[e].weight = Util::euclideanDistance(i.nodes[odds[id]].first, i.nodes[odds[id]].second, i.nodes[odds[pm.GetMatch(id)]].first, i.nodes[odds[pm.GetMatch(id)]].second);
            //std::cout << "push " << odds[id] << " " << odds[pm.GetMatch(id)] << std::endl; //" = " << (*TuM)[e].weight;
            visited[id] = true;
            visited[pm.GetMatch(id)] = true;
        }
    }

    //std::cout << "merge" << std::endl;
    //std::cout << "tumv" << boost::num_vertices(*TuM) << std::endl;
    //std::cout << "tume" << boost::num_edges(*TuM) << std::endl;
    //for (std::pair<EdgeIterator, EdgeIterator> it = boost::edges(mst); it.first != it.second; ++it.first) {
    //    std::cout << "[" << source(*it.first, *TuM) << "," << target(*it.first, *TuM) << "]" << std::endl;
    //}
    //std::cout << "odds tum" << std::endl;
    //for (std::pair<VertexIterator, VertexIterator> it = boost::vertices(*TuM); it.first != it.second; ++it.first) {
    //    if (boost::out_degree(*it.first, *TuM) & 1) {
    //        std::cout << *it.first << " " << boost::out_degree(*it.first, *TuM) << std::endl;
    //    }
    //}
}

void Christofides::doEulerTour()
{
    //if (hierholzer.hasEulerTour(*TuM)) {
    //    std::cout << "closed circuit" << std::endl;
    //}

    hierholzer.run(*TuM);

    //hierholzer.sanityTourCheck(*TuM);
}

void Christofides::doHamiltonTour()
{
    std::vector<bool> visited(boost::num_vertices(*TuM), false);
    std::vector<Edge>::iterator ei = hierholzer.tour.begin();
    Vertex first = boost::source(*ei, *TuM), last = first;
    visited[last] = true;
    result = 0;
    while (ei != hierholzer.tour.end()) {
        if (!visited[boost::target(*ei, *TuM)]) {
            //std::cout << "(" << last << ", " << boost::target(*ei, *TuM) << ")" << std::endl;
            result += Util::euclideanDistance(i.nodes[last].first, i.nodes[last].second, i.nodes[boost::target(*ei, *TuM)].first, i.nodes[boost::target(*ei, *TuM)].second);
            last = boost::target(*ei, *TuM);
            visited[last] = true;
        }
        ei++;
    }
    result += Util::euclideanDistance(i.nodes[last].first, i.nodes[last].second, i.nodes[first].first, i.nodes[first].second);
}

void Christofides::printResult()
{
    std::cout << result << std::endl;
}

void Christofides::run()
{
    this->extractMST();
    this->extractOdds();
    this->doBlossomPerfectMatching();
    //this->doGreedyMatching();
    this->doEulerTour();
    this->doHamiltonTour();
    this->printResult();
}
