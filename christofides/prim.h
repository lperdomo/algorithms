#ifndef PRIM_H
#define PRIM_H

#include "util.h"

class Prim
{
public:
    Prim();
    void run(std::vector<std::pair<double, double> > &nodes);
    std::vector<std::pair<unsigned, long> > mst;
private:
};

#endif
