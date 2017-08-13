#include "heapn.h"

Node HEAPN_node(unsigned component, unsigned weight)
{
    Node current = (Node)malloc(sizeof(struct node));
    current->component = component;
    current->weight = weight;
    return current;
}

void HEAPN_heapifyup(vector<Node>& heapn, vector<unsigned>& map, unsigned index)
{
    if (index == 0) return;
    unsigned parent = round((double(index-1)/N));
	if ((heapn[parent]->weight > heapn[index]->weight)) {
        map[heapn[index]->component] = map[heapn[parent]->component];
		map[heapn[parent]->component] = index;

		Node tmp = heapn[parent];
		heapn[parent] = heapn[index];
        heapn[index] = tmp;

        HEAPN_heapifyup(heapn, map, parent);
    }
}

void HEAPN_insert(vector<Node>& heapn, vector<unsigned>& map, Node node)
{
	heapn.push_back(node);
	map[node->component] = heapn.size() - 1;
	HEAPN_heapifyup(heapn, map, heapn.size() - 1);
}

void HEAPN_heapifydown(vector<Node>& heapn, vector<unsigned>& map, unsigned index)
{
	if ((index*N)+1 > heapn.size()) return;
	unsigned i = 1, child = (index*N)+1, aux;
	while ((index*N)+i < heapn.size() && i <= N) {
		if (heapn[(index*N)+i]->weight < heapn[child]->weight) {
			child = (index*N)+i;
		}
		i++;
	}
	if (heapn[child]->weight < heapn[index]->weight) {
		aux = map[heapn[index]->component];
        map[heapn[index]->component] = map[heapn[child]->component];
		map[heapn[child]->component] = aux;

		Node tmp = heapn[index];
		heapn[index] = heapn[child];
		heapn[child] = tmp;
		HEAPN_heapifydown(heapn, map, child);
	}
}

void HEAPN_update(vector<Node>& heapn, vector<unsigned>& map, Node node)
{
	unsigned index = map[node->component];
	if (node->weight < heapn[index]->weight) {
		heapn[map[node->component]] = node;
		HEAPN_heapifyup(heapn, map, index);
	} else {
		heapn[map[node->component]] = node;
		HEAPN_heapifydown(heapn, map, index);
	}
}

Node HEAPN_delete(vector<Node>& heapn, vector<unsigned>& map, unsigned index)
{
	Node element = heapn.at(index);
	heapn[index] = heapn.at(heapn.size() - 1);
	map[heapn[index]->component] = index;
	heapn.pop_back();
	HEAPN_heapifydown(heapn, map, index);
	return element;
}

Node HEAPN_deleteMin(vector<Node>& heapn, vector<unsigned>& map)
{
	return HEAPN_delete(heapn, map, 0);
}


void HEAPN_print(vector<Node> &heapn)
{
    vector<Node>::iterator pos = heapn.begin();
    cout << "Heap = ";
    while ( pos != heapn.end() ) {
        cout << (*pos)->component << ":" << (*pos)->weight << " ";
        ++pos;
    }
    cout << endl;
}
