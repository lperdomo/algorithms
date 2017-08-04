#include "tspparse.h"

Instance::Instance()
{
}

Instance::~Instance()
{
}

std::string Instance::read_keyword(std::istream& f)
{
    std::string keyword;
    if (f >> keyword) return keyword;
    else return "EOF";
}

void Instance::skip_separator(std::istream& f, const std::string& keyword)
{
    std::string sep;
    f >> sep;
    if (sep != ":") throw "Expected separator : but found \'"+sep+"\'";
}

std::string Instance::read_spec_part(std::istream& f)
{
    std::string keyword;
    this->node_coord_type="TWOD_COORDS";
    do {
        keyword = read_keyword(f);
        if (keyword[keyword.length()-1] == ':') {
            keyword = keyword.substr(0,keyword.length()-1);
            f.putback(':');
        }
        if (keyword == "NAME") {
            skip_separator(f,keyword);
            f >> this->name;
        } else if (keyword == "TYPE") {
            skip_separator(f,keyword);
            f >> this->type;
            assert(this->type == "TSP" || this->type == "ATSP" || this->type == "SOP" || this->type == "HCP" || this->type == "CVRP" || this->type == "TOUR");
        } else if (keyword == "COMMENT") {
            skip_separator(f,keyword);
            char cline[1024];
            f.getline(cline,1024);
            this->comment = cline;
        } else if (keyword == "DIMENSION") {
            skip_separator(f,keyword);
            f >> this->dimension;
        } else if (keyword == "CAPACITY") {
            skip_separator(f,keyword);
            f >> this->capacity;
        } else if (keyword == "EDGE_WEIGHT_TYPE") {
            skip_separator(f,keyword);
            f >> this->edge_weight_type;
        } else if (keyword == "EDGE_WEIGHT_FORMAT") {
            skip_separator(f,keyword);
            f >> this->edge_weight_format;
        } else if (keyword == "EDGE_DATA_FORMAT") {
            skip_separator(f,keyword);
            f >> this->edge_data_format;
        } else if (keyword == "NODE_COORD_TYPE") {
            skip_separator(f,keyword);
            f >> this->node_coord_type;
        } else if (keyword == "DISPLAY_DATA_TYPE") {
            skip_separator(f,keyword);
            f >> this->display_data_type;
        } else if (keyword == "EOF") {
            skip_separator(f,keyword);
        } else {
            return keyword;
        }
    } while (true);
}

void Instance::read_data_part(std::istream& f, std::string keyword)
{
    try {
        do {
            if (keyword == "NODE_COORD_SECTION") {
                if (node_coord_type == "TWOD_COORDS") {
                    nodes.resize(dimension);
                    for (unsigned i = 0; i < nodes.size(); i++) {
                        unsigned j;
                        double x,y;
                        f >> j >> x >> y;
                        nodes[j-1] = std::make_pair(x, y);
                    }
                }
            } else if (keyword == "EOF") {
                return;
            } else if (keyword == "" && f.eof()) {
                return;
            }
            keyword = read_keyword(f);
        } while (true);
    } catch (const std::string& s) {
        std::cout << s << std::endl;
        return;
    } catch (...) {
        std::cout << "Warning: Unexpected end of file while scanning for keyword." << std::endl;
        return;
    }
}

void Instance::read(std::istream& f)
{
    std::string token;
    try {
        token = read_spec_part(f);
    } catch (const std::string& s) {
        std::cout << "Could not read specification part, reason: " << s << std::endl;
        exit(1);
    } catch (...) {
        std::cout << "Could not read specification part, unknown reason." << std::endl;
        exit(1);
    }
    try {
        read_data_part(f, token);
    } catch (const std::string& s) {
        std::cout << "Could not read data part, reason: " << s << std::endl;
        exit(1);
    } catch (...) {
        std::cout << "Could not read data part, unknown reason." << std::endl;
        exit(1);
    }
}
