#ifndef HOLLOWHEAP_HPP_
#define HOLLOWHEAP_HPP_

#include <stdlib.h>
#include <vector>
using namespace std;

class HHItem
{
    public:
        HHItem();
        HHItem(long value);
        ~HHItem();
        long value;
};

class HHNode
{
    public:
        HHNode();
        HHNode(long key, HHItem *item);
        ~HHNode();
        HHNode *altparent;
        HHNode *next;
        HHNode *child;
        HHItem *item;
        long key;
        long rank;
        bool hollow;
};

class HollowHeap
{
    public:
        HollowHeap();
        ~HollowHeap();
        long inserts;
        long deletemins;
        long decreasekeys;
        long melds;
        long hollows;
        long delhollows;
        long links;
        HHNode* root;
        vector<HHNode*> aux;
        long size;
        void addChild(HHNode *parent, HHNode *child);
        HHNode *link(HHNode *node1, HHNode *node2);
        void meld(HHNode *node);
        void insert(HHNode *node);
        HHItem *deleteMin();
        void decreaseKey(HHNode *node, long key);
};
#endif /* HOLLOWHEAP_HPP_ */
