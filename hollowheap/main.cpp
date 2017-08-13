#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#include "dijkstra.h"
//#include "hollowheap.hpp"
using namespace std;

void read_dimacs(istream& in, unsigned & n, unsigned & m, Digraph& a) {
	string line="", dummy;
	while (line.substr(0,4) != "p sp")
		getline(in,line);
	stringstream linestr;
	linestr.str(line);
	linestr >> dummy >> dummy >> n >> m;
	a = DIGRAPH_init(n);
	unsigned i = 0;
	while (i < m) {
		getline(in,line);
		if (line.substr(0,2) == "a ") {
			stringstream arc(line);
			unsigned u,v,w;
			char ac;
			arc >> ac >> u >> v >> w;
			DIGRAPH_insertArc(a, u, v, w);
			i++;
		}
	}
}

int main(int argc, char *argv[])
{
	unsigned src = atoi(argv[1]);
	double dst = atof(argv[2]);

	unsigned n, m;

	Digraph graph;
	read_dimacs(std::cin, n, m, graph);
	//cout << "DIMACS file loaded!" << endl;
	srand(time(NULL));
	//dst = rand()%n;
	vector<unsigned> dist;
	dijkstra(graph, src, dist);
	//cout << "Source: " << src+1 << " Destination: " << dst+1 << " Distance: ";
	if (dist[dst] == numeric_limits<unsigned>::max()) {
		cout << "INF" << endl;
	} else {
		cout << dist[dst] << endl;
	}
	//DIGRAPH_printstats(graph);
	//HHEAP_printstats();
	delete graph;

	return 0;
}

/*
 * DELETEMINS
hheap h;
HHEAP_makeHeap(h);
int po = 2;
HHEAP_resizeAux(h, pow(2,po));
for (unsigned i = 0; i < pow(2,po)-1; i++) {
	unsigned a = rand();
	HHEAP_item item = HHEAP_newItem(a);
	HHEAP_insert(h, a, item);
}
HHEAP_resetstats();
chrono::system_clock::time_point t = chrono::system_clock::now();
for (unsigned i = 0; i < pow(2,po-1); i++) {
	HHEAP_deleteMin(h);
}
HHEAP_printstats();
cout << "TEMPO: " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() << endl;
delete h

*/

/*
 * DECREASEKEYS
hheap h;
HHEAP_makeHeap(h);
int po = 1;
for (unsigned i = 0; i < pow(2,po)-1; i++) {
	HHEAP_item item = HHEAP_newItem(pow(2,po)+1);
	HHEAP_insert(h, pow(2,po)+1, item);
}
for (unsigned i = 0; i < pow(2,po); i++) {
	HHEAP_item item = HHEAP_newItem(pow(2,po)+2);
	HHEAP_insert(h, pow(2,po)+2, item);
}
HHEAP_resetstats();
chrono::system_clock::time_point t = chrono::system_clock::now();
for (unsigned i = 0; i < pow(2,po); i++) {
	HHEAP_item item = HHEAP_newItem(pow(2,po)+2);
	HHEAP_node node = HHEAP_newNode(pow(2,po)-i, item);
	HHEAP_decreaseKey(h, node, pow(2,po)+2);
}
HHEAP_printstats();
cout << "TEMPO: " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() << endl;
delete h

*/

/*
 * INSERTS
hheap h;
HHEAP_makeHeap(h);
chrono::system_clock::time_point t = chrono::system_clock::now();
for (unsigned i = pow(2, 23)-1; i > 0; i--) {
    HHEAP_item item = HHEAP_newItem(i);
	HHEAP_insert(h, i, item);
}
HHEAP_printstats();
cout << "TEMPO: " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() << endl;
delete h
*/

/* TESTES ESTRUTURA HOLLOW HEAP
hheap h;
HHEAP_makeHeap(h);

Digraph graph = DIGRAPH_init(7);
DIGRAPH_insertArc(graph, 0, 1, 1);
DIGRAPH_insertArc(graph, 0, 2, 2);
DIGRAPH_insertArc(graph, 1, 3, 7);
DIGRAPH_insertArc(graph, 1, 4, 8);
DIGRAPH_insertArc(graph, 2, 3, 5);
DIGRAPH_insertArc(graph, 2, 4, 6);
DIGRAPH_insertArc(graph, 3, 5, 1);
DIGRAPH_insertArc(graph, 4, 5, 8);
DIGRAPH_insertArc(graph, 6, 5, 1);
vector<unsigned> dist;
dijkstra(graph, 0, dist);

for (int i = 0; i < 7; i++) {
	cout << " custo " << dist[i] << endl;
}*/

/*
HHEAP_item item1 = HHEAP_newItem(14);
HHEAP_insert(h, 14, item1);
HHEAP_item item2 = HHEAP_newItem(11);
HHEAP_insert(h, 11, item2);
HHEAP_item item3 = HHEAP_newItem(5);
HHEAP_insert(h, 5, item3);
HHEAP_item item4 = HHEAP_newItem(9);
HHEAP_insert(h, 9, item4);
HHEAP_item item5 = HHEAP_newItem(1);
HHEAP_insert(h, 1, item5);
HHEAP_item item6 = HHEAP_newItem(8);
HHEAP_insert(h, 8, item6);
HHEAP_item item7 = HHEAP_newItem(10);
HHEAP_insert(h, 10, item7);
HHEAP_item item8 = HHEAP_newItem(3);
HHEAP_insert(h, 3, item8);
HHEAP_item item9 = HHEAP_newItem(6);
HHEAP_insert(h, 6, item9);
HHEAP_item item10 = HHEAP_newItem(12);
HHEAP_insert(h, 12, item10);
HHEAP_item item11 = HHEAP_newItem(13);
HHEAP_insert(h, 13, item11);
HHEAP_item item12 = HHEAP_newItem(4);
HHEAP_insert(h, 4, item12);
HHEAP_resizeAux(h, 15);
HHEAP_node node;
if (h->root->key != 1) cout << "erro root key não é 1" << endl;
node = h->root->child;
if (node->key != 4) cout << "erro node key não é 4" << endl;
node = node->next;
if (node->key != 13) cout << "erro node key não é 13" << endl;
node = node->next;
if (node->key != 12) cout << "erro node key não é 12" << endl;
node = node->next;
if (node->key != 6) cout << "erro node key não é 6" << endl;
node = node->next;
if (node->key != 3) cout << "erro node key não é 3" << endl;
node = node->next;
if (node->key != 10) cout << "erro node key não é 10" << endl;
node = node->next;
if (node->key != 8) cout << "erro node key não é 8" << endl;
node = node->next;
if (node->key != 5) cout << "erro node key não é 5" << endl;
if (node->next != NULL) cout << "erro node next não é nulo" << endl;
node = node->child;
if (node->key != 9) cout << "erro node key não é 9" << endl;
node = node->next;
if (node->key != 11) cout << "erro node key não é 11" << endl;
node = node->child;
if (node->key != 14) cout << "erro node key não é 14" << endl;
cout << "terminou inserts" << endl;
*/

/*
HHEAP_decreaseKey(h, h->root->child, 2);
if (h->root->child->key != 2) cout << "erro decreasekeyunderroot não é 2" << endl;
cout << "terminou decreasekeyunderroot";
*/

/*
HHEAP_deleteMin(h);
node = h->root;
if (node->key != 3) cout << "erro deletemin nao é 3" << endl;
cout << "terminou deletemin" << endl;
*/

/*
HHEAP_item item;
HHEAP_findMin(h, item);
if (item->value != 1) cout << "erro findmin não é 1" << endl;
cout << "terminou findmin" << endl;
*/

/*
hheap hb;
HHEAP_makeHeap(hb);
HHEAP_item item13 = HHEAP_newItem(0);
HHEAP_insert(hb, 0, item13);
HHEAP_item item14 = HHEAP_newItem(5);
HHEAP_insert(hb, 5, item14);
HHEAP_item item15 = HHEAP_newItem(6);
HHEAP_insert(hb, 6, item15);
HHEAP_node altroot = hb->root;
hb->root = NULL;
HHEAP_meld(h, altroot);
HHEAP_item item;
HHEAP_findMin(h, item);
if (item->value != 0) cout << "erro findminaftermeld não é 0" << endl;
cout << "terminou findminaftermeld" << endl;
*/

/*
hheap hb;
HHEAP_makeHeap(hb);
HHEAP_item item13 = HHEAP_newItem(2);
HHEAP_insert(hb, 2, item13);
HHEAP_item item14 = HHEAP_newItem(5);
HHEAP_insert(hb, 5, item14);
HHEAP_item item15 = HHEAP_newItem(6);
HHEAP_insert(hb, 6, item15);

HHEAP_node altroot = hb->root;
hb->root = NULL;
HHEAP_meld(h, altroot);
node = h->root;
if (node->key != 1) cout << "erro meldhighermax node key não é 1" << endl;
node = node->child;
HHEAP_node sroot = node;
if (node->key != 2) cout << "erro meldhighermax node key não é 2" << endl;
node = node->next;
if (node->key != 4) cout << "erro meldhighermax node key não é 4" << endl;
node = node->next;
if (node->key != 13) cout << "erro meldhighermax node key não é 13" << endl;
node = sroot->child;
if (node->key != 6) cout << "erro meldhighermax node key não é 6" << endl;
node = node->next;
if (node->key != 5) cout << "erro meldhighermax node key não é 5" << endl;
cout << "terminou meldhighermax" << endl;
*/

/*
hheap hb;
HHEAP_makeHeap(hb);
HHEAP_item item13 = HHEAP_newItem(0);
HHEAP_insert(hb, 0, item13);
HHEAP_item item14 = HHEAP_newItem(5);
HHEAP_insert(hb, 5, item14);
HHEAP_item item15 = HHEAP_newItem(6);
HHEAP_insert(hb, 6, item15);
HHEAP_node altroot = hb->root;
hb->root = NULL;
HHEAP_meld(h, altroot);
node = h->root;
if (node->key != 0) cout << "erro meldlowermax node key não é 0" << endl;
node = node->child;
HHEAP_node sroot = node;
if (node->key != 1) cout << "erro meldlowermax node key não é 1" << endl;
node = node->next;
if (node->key != 6) cout << "erro meldlowermax node key não é 6" << endl;
node = node->next;
if (node->key != 5) cout << "erro meldlowermax node key não é 5" << endl;
node = sroot->child;
if (node->key != 4) cout << "erro meldlowermax node key não é 4" << endl;
node = node->next;
if (node->key != 13) cout << "erro meldlowermax node key não é 13" << endl;
node = node->next;
if (node->key != 12) cout << "erro meldlowermax node key não é 12" << endl;
cout << "terminou meldlowermax" << endl;
*/

/*
unsigned i;
for (i = 0; i < pow(2, 25); i++) {
    HHEAP_item item = HHEAP_newItem(i);
	HHEAP_insert(h, i, item);
}

cout << "inserts" << i << endl;
cout << h->size << endl;

HHEAP_resizeAux(h, pow(2,25));
for (i = 1; i < pow(2, 25); i++) {
	HHEAP_deleteMin(h);
}

cout << "deletemins" << i << endl;
cout << h->size << endl;
*/

//delete h;
