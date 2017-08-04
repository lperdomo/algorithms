#include "hopcroftkarp.h"

HopcroftKarp::HopcroftKarp()
{
}

void HopcroftKarp::inputDIMACSfile()
{
	string lineType, line = "", dummy;
	while (cin) {
		getline(cin,line);
		lineType = line.substr(0,2);
		stringstream lineStream(line);
		if (lineType == "e ") {
			long u, v, w;
			char ac;
			lineStream >> ac >> u >> v;
			if (u != v) {
                Edge e = add_edge(u, v, g).first;
                distanceLeft[u] = 0;
                distanceRight[v] = 0;
                matchingLeft[u] = -1;
                matchingRight[v] = -1;
            }
		}
	}
	vertices = matchingLeft.size()+matchingRight.size();
	edges = num_edges(g);
}

void HopcroftKarp::init()
{
    for (map<long, long>::iterator it = distanceLeft.begin(); it != distanceLeft.end(); ++it) {
        it->second = 0;
        matchingLeft[it->first] = -1;
    }
    for (map<long, long>::iterator it = distanceRight.begin(); it != distanceRight.end(); ++it) {
        it->second = 0;
        matchingRight[it->first] = -1;
    }
    matchings = 0;
    phases = 0;
    maximalExtraction = 0;
}

void HopcroftKarp::reset()
{
    for (map<long, long>::iterator it = distanceLeft.begin(); it != distanceLeft.end(); ++it) {
        it->second = 0;
    }
    for (map<long, long>::iterator it = distanceRight.begin(); it != distanceRight.end(); ++it) {
        it->second = 0;
    }
}

bool HopcroftKarp::depthFirstSearch(long left)
{
    maximalExtraction++;

    for (pair<adjacency_it, adjacency_it> neighbours = adjacent_vertices(vertex(left, g), g);
     neighbours.first != neighbours.second; ++neighbours.first) {
        if (distanceRight[*neighbours.first] == distanceLeft[left]+1) {
            distanceRight[*neighbours.first] = 0;
            if (matchingRight[*neighbours.first] == -1 || this->depthFirstSearch(matchingRight[*neighbours.first])) {
                matchingLeft[left] = *neighbours.first;
                matchingRight[*neighbours.first] = left;
                return true;
            }
        }
    }
    return false;
}

bool HopcroftKarp::breadthFirstSearch()
{
    bool finish = false;
    std::queue<long> q;
    this->reset();
    for (map<long, long>::iterator it = matchingLeft.begin(); it != matchingLeft.end(); ++it) {
        if (it->second == -1) {
            q.push(it->first);
        }
    }

    while (!q.empty()) {
        long left = q.front();
        q.pop();
        for (pair<adjacency_it, adjacency_it> neighbours = adjacent_vertices(vertex(left, g), g);
         neighbours.first != neighbours.second; ++neighbours.first) {
            if (!distanceRight[*neighbours.first]) {
                distanceRight[*neighbours.first] = distanceLeft[left] + 1;
                if (matchingRight[*neighbours.first] == -1) {
                    finish = true;
                } else {
                    distanceLeft[matchingRight[*neighbours.first]] = 0;
                    distanceRight[*neighbours.first]+1;
                    q.push(matchingRight[*neighbours.first]);
                }
            }

        }
    }
    return finish;
}

void HopcroftKarp::result()
{
    if (matchings > 0) {
        cout << matchings << endl;//maximum cardinality
    } else {
        cout << "INF" << endl;
    }
    //cerr << vertices << " " << edges << " " << phases << " " << maximalExtraction << " " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-timeInit).count() << endl;
}

void HopcroftKarp::findMaxMatching()
{
    this->inputDIMACSfile();
    this->init();
    //timeInit = chrono::system_clock::now();
    while (this->breadthFirstSearch()) {
        phases++;
        for (map<long, long>::iterator it = matchingLeft.begin(); it != matchingLeft.end(); ++it) {
            if (it->second == -1 && this->depthFirstSearch(it->first)) {
                matchings++;
            }
        }
    }

    this->result();
}

int main()
{
    HopcroftKarp hk;
    hk.findMaxMatching();
    return 0;
}
