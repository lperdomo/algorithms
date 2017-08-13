#ifndef HEAPN_H_
#define HEAPN_H_

#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

const int N = 4;

typedef struct node *Node;
struct node {
	unsigned component;
	unsigned weight;
};

Node HEAPN_node(unsigned component, unsigned weight);

void HEAPN_heapifyup(vector<Node>& heapn, vector<unsigned>& map, unsigned index);

void HEAPN_insert(vector<Node>& heapn, vector<unsigned>& map, Node node);

void HEAPN_heapifydown(vector<Node>& heapn, vector<unsigned>& map, unsigned index);

void HEAPN_update(vector<Node>& heapn, vector<unsigned>& map, Node node);

Node HEAPN_delete(vector<Node>& heapn, vector<unsigned>& map, unsigned index);

Node HEAPN_deleteMin(vector<Node>& heapn, vector<unsigned>& map);

void HEAPN_print(vector<Node> &heapn);

#endif
