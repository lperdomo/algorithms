#ifndef HEAPN_H_
#define HEAPN_H_

#include <math.h>
#include <vector>

using namespace std;

typedef pair<long, long> Node;

class HeapN {
    public:
        HeapN(int N);
        ~HeapN();
        bool empty();
        Node makeNode(long component, long weight);
        void insert(Node node);
        void update(Node node);
        Node deleteMin();
        vector<long> map;

    private:
        int N;
        vector<Node> heap;
        long parent(long index);
        long child(long index, long n);
        void heapifyUp(long index);
        void heapifyDown(long index);
};

#endif
