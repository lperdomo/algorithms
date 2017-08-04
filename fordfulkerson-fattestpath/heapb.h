#ifndef HEAPB_H_
#define HEAPB_H_

#include <vector>
#include <iostream>

using namespace std;

typedef pair<long, long> Node;

class HeapB {
	public:
		HeapB();
		~HeapB();
		long size();
		void insert(Node node);
		void insert(long vertex, long capacity);
		void update(long vertex, long capacity);
		Node deleteMax();
		Node makeNode(long vertex, long capacity);

	private:
		vector<Node> heap;
		long left(long parent);
		long right(long parent);
		long parent(long child);
		void heapifyup(long id);
		void heapifydown(long id);
};

#endif
