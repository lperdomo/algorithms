#include "hollowheap.hpp"

HHItem::HHItem()
{
    this->value = 0;
}

HHItem::HHItem(long value)
{
    this->value = value;
}

HHItem::~HHItem()
{
}

HHNode::HHNode(long key, HHItem *item)
{
	this->key = key;
	this->item = item;
	this->child = NULL;
	this->next = NULL;
	this->altparent = NULL;
	this->rank = 0;
	this->hollow = false;
}

HHNode::~HHNode()
{
}

HollowHeap::HollowHeap()
{
	this->root = NULL;
	this->size = 0;
    this->inserts = 0;
    this->deletemins = 0;
    this->decreasekeys = 0;
    this->melds = 0;
    this->hollows = 0;
    this->delhollows = 0;
    this->links = 0;
}

HollowHeap::~HollowHeap()
{
}

void HollowHeap::addChild(HHNode *parent, HHNode *child)
{
	child->next = parent->child;
	parent->child = child;
}

HHNode *HollowHeap::link(HHNode *node1, HHNode *node2)
{
	if (node1->key >= node2->key) {
		addChild(node2, node1);
		return node2;
	} else {
		addChild(node1, node2);
		return node1;
	}
	links++;
}

void HollowHeap::meld(HHNode *node)
{
	if (node != NULL) {
		if (this->root == NULL) {
			this->root = node;
		} else {
			this->root = link(this->root, node);
		}
	}
	melds++;
}

void HollowHeap::insert(HHNode *node)
{
	meld(node);
	this->size++;
	inserts++;
}

HHItem *HollowHeap::deleteMin()
{
	HHItem *item = this->root->item;
	this->root->altparent = NULL;
	this->root->hollow = true;
	hollows++;

	long maxRank = 0;
	this->root->next = NULL;

	while (this->root != NULL) {
		HHNode *current = this->root->child;
		HHNode *parent = this->root;
		HHNode *prev;
		this->root = this->root->next;
		while (current != NULL) {
			prev = current;
			current = current->next;
			if (prev->hollow == true) {
				if (prev->altparent == NULL) {
					prev->next = this->root;
					this->root = prev;
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
				while (this->aux[prev->rank] != NULL) {
					prev = link(prev, this->aux[prev->rank]);
					this->aux[prev->rank++] = NULL;
				}
				this->aux[prev->rank] = prev;
				if (prev->rank > maxRank) {
					maxRank = prev->rank;
				}
			}
		}
		delete parent;
	}

	for (unsigned i = 0; i <= maxRank; i++) {
		if (this->aux[i] != NULL) {
			if (this->root == NULL) {
				this->root = this->aux[i];
			} else {
				this->root = link(this->root, this->aux[i]);
			}
			this->aux[i] = NULL;
		}
	}

	this->size--;
	deletemins++;
	return item;
}

void HollowHeap::decreaseKey(HHNode *node, long key)
{
	if (node == this->root) {
		this->root->key = key;
		return;
	}

	HHNode *aux1 = new HHNode(key, node->item);
	node->hollow = true;
	if (node->rank  > 2) {
		aux1->rank = node->rank - 2;
	}
	if (key > this->root->key) {
		aux1->child = node;
		node->altparent = aux1;
	} else {
		node->altparent = NULL;
	}
	meld(aux1);
	this->size++;
	decreasekeys++;
	hollows++;
}
