#ifndef TSPPARSE_H
#define TSPPARSE_H

#include <fstream>
#include <string>
#include <iostream>

#include "util.h"

class Instance
{
public:
    Instance();
    ~Instance();

    std::string name, type, comment;
    std::string edge_weight_type, edge_weight_format, edge_data_format;
    std::string node_coord_type;
    std::string display_data_type;
    unsigned dimension, capacity;
    std::vector<std::pair<double,double> > nodes;

    void read(std::istream& f);

private:
    void read_data_part(std::istream& f, std::string keyword);
    std::string read_spec_part(std::istream& f);
    std::string read_keyword(std::istream& f);
    void skip_separator(std::istream& f, const std::string& keyword);
};

#endif // TSPPARSE_H
