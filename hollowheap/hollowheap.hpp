/*
 * hollowheap.hpp
 *
 *  Created on: 22 de abr de 2017
 *      Author: leo
 */

#ifndef HOLLOWHEAP_HPP_
#define HOLLOWHEAP_HPP_

typedef struct HHEAP_ITEM* HHEAP_item;
typedef struct HHEAP_NODE* HHEAP_node;
typedef struct HHEAP_WRAPPER* hheap;

struct HHEAP_ITEM {
	unsigned value;
};

struct HHEAP_NODE {
	HHEAP_node altparent;
	HHEAP_node next;
	HHEAP_node child;
	HHEAP_item item;
	unsigned key;
	unsigned rank;
	bool hollow;
};

struct HHEAP_WRAPPER {
	HHEAP_node root;
	HHEAP_node* aux;
	unsigned size;
};

void HHEAP_makeHeap(hheap &heap);

void HHEAP_resizeAux(hheap &heap, unsigned size);

void HHEAP_findMin(hheap &heap, HHEAP_item &ret);

HHEAP_item HHEAP_newItem(unsigned value);

HHEAP_node HHEAP_newNode(unsigned key, HHEAP_item &item);

void HHEAP_addChild(HHEAP_node &parent, HHEAP_node &child);

void HHEAP_link(HHEAP_node &node1, HHEAP_node &node2, HHEAP_node &ret);

void HHEAP_meld(hheap &heap, HHEAP_node &node);

void HHEAP_insert(hheap &heap, unsigned key, HHEAP_item item);

void HHEAP_delete(hheap &heap, HHEAP_node &node);

HHEAP_item HHEAP_deleteMin(hheap &heap);

void HHEAP_decreaseKey(hheap &heap, HHEAP_node &node, unsigned key);

void HHEAP_printstats();

void HHEAP_resetstats();

void HHEAP_print(hheap heap);

void HHEAP_printc(HHEAP_node node);

#endif /* HOLLOWHEAP_HPP_ */
