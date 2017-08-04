#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H

#include "util.h"
#include "prim.h"
#include "hierholzer.h"
#include "tspparse.h"

#include "blossom5/PerfectMatching.h"
#include "blossom5/GEOM/GeomPerfectMatching.h"

#include <iostream>

class Christofides
{
public:
    Christofides();
    ~Christofides();
    void load();
    void run();
    void printResult();
    Instance i;
    Graph *TuM;
    std::vector<Vertex> odds;
    Hierholzer hierholzer;
    long odd;
    long result;
private:
    void extractMST();
    void extractOdds();
    void doBlossomPerfectMatching();
    void doGreedyMatching();
    void doEulerTour();
    void doHamiltonTour();
};

#endif
