/*
 * hollowheap.cpp
 *
 *  Created on: 21 de abr de 2017
 *      Author: leo
 */

#include <stdlib.h>
#include <iostream>

#include "hollowheap.hpp"

unsigned inserts = 0;
unsigned deletemins = 0;
unsigned decreasekeys = 0;
unsigned melds = 0;
unsigned hollows = 0;
unsigned delhollows = 0;
unsigned links = 0;

HHEAP_item HHEAP_newItem(unsigned value)
{
	HHEAP_item item = (HHEAP_item)malloc(sizeof(struct HHEAP_ITEM));
	item->value = value;
	return item;
}

HHEAP_node HHEAP_newNode(unsigned key, HHEAP_item &item)
{
	HHEAP_node node = (HHEAP_node)malloc(sizeof(struct HHEAP_NODE));
	node->key = key;
	node->item = item;
	node->child = NULL;
	node->next = NULL;
	node->altparent = NULL;
	node->rank = 0;
	node->hollow = false;
	return node;
}

void HHEAP_makeHeap(hheap &heap)
{
	heap = (hheap)malloc(sizeof(struct HHEAP_WRAPPER));
	heap->root = NULL;
	heap->aux = NULL;
	heap->size = 0;
}

void HHEAP_resizeAux(hheap &heap, unsigned size)
{
    heap->aux = (HHEAP_node*)malloc(size * sizeof(struct HHEAP_NODE));
    for (unsigned i = 0; i < size; i++) {
		heap->aux[i] = NULL;
	}
}

void HHEAP_findMin(hheap &heap, HHEAP_item &ret)
{
	if (heap->root == NULL) {
		ret = NULL;
	} else {
		ret = heap->root->item;
	}
}

void HHEAP_addChild(HHEAP_node &parent, HHEAP_node &child)
{
	child->next = parent->child;
	parent->child = child;
}

void HHEAP_link(HHEAP_node &node1, HHEAP_node &node2, HHEAP_node &ret)
{
	if (node1->key >= node2->key) {
		HHEAP_addChild(node2, node1);
		ret = node2;
	} else {
		HHEAP_addChild(node1, node2);
		ret = node1;
	}
	links++;
}

void HHEAP_meld(hheap &heap, HHEAP_node &node)
{
	if (node != NULL) {
		if (heap->root == NULL) {
			heap->root = node;
		} else {
			HHEAP_link(heap->root, node, heap->root);
		}
	}
	melds++;
}

void HHEAP_insert(hheap &heap, unsigned key, HHEAP_item item)
{
	HHEAP_node node = HHEAP_newNode(key, item);
	HHEAP_meld(heap, node);
	heap->size++;
	inserts++;
}

void HHEAP_delete(hheap &heap, HHEAP_node &node)
{
	node->altparent = NULL;
	node->hollow = true;
	hollows++;
	if (node != heap->root) {
		return;
	}

	unsigned maxRank = 0;
	heap->root->next = NULL;
    //HHEAP_node* aux = (HHEAP_node*)malloc(sizeof(struct HHEAP_NODE)*h->size);
	//for (unsigned i = 0; i < h->size; i++) {
	//	aux[i] = NULL;
	//}
	while (heap->root != NULL) {
		HHEAP_node current = heap->root->child;
		HHEAP_node parent = heap->root;
		HHEAP_node prev;
		heap->root = heap->root->next;
		while (current != NULL) {
			prev = current;
			current = current->next;
			if (prev->hollow == true) {
				if (prev->altparent == NULL) {
					prev->next = heap->root;
					heap->root = prev;
				} else {
					if (prev->altparent == parent) {
						current = NULL;
					} else {
						prev->next = NULL;
					}
					prev->altparent = NULL;
				}
				delhollows++;
			} else {
				while (heap->aux[prev->rank] != NULL) {
					HHEAP_link(prev, heap->aux[prev->rank], prev);
					heap->aux[prev->rank++] = NULL;
				}
				heap->aux[prev->rank] = prev;
				if (prev->rank > maxRank) {
					maxRank = prev->rank;
				}
			}
		}
		delete parent;
	}

	for (unsigned i = 0; i <= maxRank; i++) {
		if (heap->aux[i] != NULL) {
			if (heap->root == NULL) {
				heap->root = heap->aux[i];
			} else {
				HHEAP_link(heap->root, heap->aux[i], heap->root);
			}
			heap->aux[i] = NULL;
		}
	}

	//delete aux;
	heap->size--;
}

HHEAP_item HHEAP_deleteMin(hheap &heap)
{
	HHEAP_item item = heap->root->item;
	HHEAP_delete(heap, heap->root);
	deletemins++;
	return item;
}

void HHEAP_decreaseKey(hheap &heap, HHEAP_node &node, unsigned key)
{
	if (node == heap->root) {
		heap->root->key = key;
		return;
	}

	HHEAP_node aux = HHEAP_newNode(key, node->item);
	node->hollow = true;
	if (node->rank  > 2) {
		aux->rank = node->rank - 2;
	}
	if (key > heap->root->key) {
		aux->child = node;
		node->altparent = aux;
	} else {
		node->altparent = NULL;
	}
	HHEAP_meld(heap, aux);
	heap->size++;
	decreasekeys++;
	hollows++;
}

void HHEAP_resetstats()
{
	inserts = 0;
	deletemins = 0;
	decreasekeys = 0;
	links = 0;
	melds = 0;
	hollows = 0;
	delhollows = 0;
}

void HHEAP_printstats()
{
	std::cout << inserts << ";";
	std::cout << deletemins << ";";
	std::cout << decreasekeys << ";";
	std::cout << links << ";";
	std::cout << melds << ";";
	std::cout << hollows << ";";
	std::cout << delhollows << ";";
	std::cout << (hollows-delhollows) << ";";
}

void HHEAP_print(hheap heap)
{
	HHEAP_node tmp = heap->root;
	std::cout << "root " << heap->root->key << std::endl;
	do {
		std::cout << "[" << tmp->key << "]" << std::endl;
		HHEAP_printc(tmp);
		if (tmp->next != NULL) {
			tmp = tmp->next;
		}
	} while (tmp != heap->root);
}

void HHEAP_printc(HHEAP_node node)
{
	HHEAP_node tmp = node->child;
	if (tmp != NULL) {
		do {
			std::cout << "(" << node->key << ") <-" << tmp->key << " -> " << "altparent(" << tmp->altparent << ")" << std::endl;
			HHEAP_printc(tmp);
			tmp = tmp->next;
		} while (tmp != NULL);
	}
}
