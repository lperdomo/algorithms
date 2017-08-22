#include "heapn.h"

HeapN::HeapN(int N)
{
    this->N = N;
}

HeapN::~HeapN()
{
}

bool HeapN::empty()
{
    return heap.empty();
}

long HeapN::parent(long index)
{
    return round((double(index-1)/N));
}

long HeapN::child(long index, long n)
{
    return (index*N)+n;
}

Node HeapN::makeNode(long component, long weight)
{
    return make_pair(component, weight);
}

void HeapN::heapifyUp(long index)
{
    if (index == 0) return;
    long p = parent(index);
	if ((heap[p].second > heap[index].second)) {
        map[heap[index].first] = map[heap[p].first];
		map[heap[p].first] = index;
		swap(heap[p], heap[index]);
        this->heapifyUp(p);
    }
}

void HeapN::insert(Node node)
{
	heap.push_back(node);
	map[node.first] = heap.size() - 1;
	this->heapifyUp(heap.size() - 1);
}

void HeapN::heapifyDown(long index)
{
	long n = 1, c = child(index, n);
	if (c >= heap.size()) return;
	while (child(index, n) < heap.size() && n <= N) {
		if (heap[child(index, n)].second < heap[c].second) {
			c = child(index, n);
		}
		n++;
	}
	if (heap[c].second < heap[index].second) {
        swap(map[heap[index].first], map[heap[c].first]);
        swap(heap[index], heap[c]);
		this->heapifyDown(c);
	}
}

void HeapN::update(Node node)
{
	long index = map[node.first];
	if (node.second < heap[index].second) {
		heap[map[node.first]] = node;
		this->heapifyUp(index);
	} else {
		heap[map[node.first]] = node;
		this->heapifyDown(index);
	}
}

Node HeapN::deleteMin()
{
	Node element = heap.at(0);
	heap[0] = heap.at(heap.size() - 1);
	map[heap[0].first] = 0;
	heap.pop_back();
	this->heapifyDown(0);
	return element;
}
