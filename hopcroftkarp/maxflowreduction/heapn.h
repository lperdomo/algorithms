#ifndef HEAPB_H_
#define HEAPB_H_

#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

typedef pair<long, long> Node;

class HeapN {
	public:
		HeapN(int N);
		~HeapN();
		long size();
		void insert(Node node);
		void insert(long vertex, long capacity);
		void update(long vertex, long capacity);
		void update(Node node);
		Node deleteMax();
		Node makeNode(long vertex, long capacity);
		vector<long> map;

	private:
        int N;
		vector<Node> heap;
		long child(long index, long n);
		long parent(long child);
		void heapifyup(long id);
		void heapifydown(long id);
};

#endif
