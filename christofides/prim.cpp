#include "prim.h"

Prim::Prim()
{
}

void Prim::run(std::vector<std::pair<double,double> > &nodes)
{
    mst.resize(nodes.size());
    std::vector<FibonnaciHeapHandle> aux(nodes.size());
	std::vector<bool> visited(nodes.size(), false);
	FibonnaciHeap q;

	for (unsigned i = 0; i < nodes.size(); i++) {
		mst[i] = std::make_pair(i, std::numeric_limits<long>::max());
		aux[i] = q.emplace(std::make_pair(i, std::numeric_limits<long>::max()));
	}

  	q.update(aux[0], std::make_pair(0, 0));
  	q.update(aux[0]);

    long distance = 0;
    FibonnaciHeapHandle qHandler;
	while (!q.empty()) {
		std::pair<Vertex, long> current = q.top();
		visited[current.first] = true;
		q.pop();

		for (unsigned i = 0; i < nodes.size(); i++) {
			if (!visited[i]) {
                qHandler = aux[i];
				distance = Util::euclideanDistance(nodes[current.first].first, nodes[current.first].second, nodes[i].first, nodes[i].second);
				if ((*qHandler).second > distance) {
                    mst[i] = std::make_pair(current.first, distance);
					q.update(qHandler, std::make_pair(i, distance));
                    q.update(qHandler);
				}
			}
		}
    }
}
