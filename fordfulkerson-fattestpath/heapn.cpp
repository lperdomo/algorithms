#include "heapn.h"

HeapN::HeapN(int N)
{
    this->N = N;
}

HeapN::~HeapN()
{
}

long HeapN::size()
{
	return heap.size();
}

long HeapN::child(long index, long n)
{
    return (index*N)+n;
}

long HeapN::parent(long child)
{
    return round((double(child-1)/N));
}

Node HeapN::makeNode(long vertex, long capacity)
{
	return make_pair(vertex, capacity);
}

void HeapN::insert(Node node)
{
	heap.push_back(node);
	map[node.first] = heap.size() - 1;
	heapifyup(heap.size() - 1);
}

void HeapN::insert(long vertex, long capacity)
{
	Node node = makeNode(vertex, capacity);
	insert(node);
}

Node HeapN::deleteMax()
{
	Node node = heap.front();
	swap(heap[0], heap[heap.size()-1]);
	map[heap[0].first] = 0;
	heap.pop_back();
	heapifydown(0);
	return node;
}

void HeapN::update(long vertex, long capacity)
{
	long vertex2, id;
	for (long i = 0; i < heap.size(); i++) {
		if (heap[i].first == vertex) {
			vertex2 = heap[i].first;
			id = i;
			break;
		}
	}
	if (capacity > heap[id].second) {
		heap[id] = makeNode(vertex2, capacity);
		heapifyup(id);
	} else {
		heap[id] = makeNode(vertex2, capacity);
		heapifydown(id);
	}
}

void HeapN::update(Node node)
{
	long id = map[node.first];
	if (node.second > heap[id].second) {
		heap[map[node.first]] = node;
		this->heapifyup(id);
	} else {
		heap[map[node.first]] = node;
		this->heapifydown(id);
	}
}

void HeapN::heapifyup(long id)
{
	if (id == 0) return;
	long p = parent(id);
    if (heap[p].second < heap[id].second) {
        map[heap[id].first] = map[heap[p].first];
        map[heap[p].first] = id;
        swap(heap[p], heap[id]);
        heapifyup(p);
    }
}

void HeapN::heapifydown(long id)
{
	long n = 1, c = child(id, n);
	if (c >= heap.size()) return;
	while (child(id, n) < heap.size() && n <= N) {
		if (heap[child(id, n)].second < heap[c].second) {
			c = child(id, n);
		}
		n++;
	}
	if (heap[c].second > heap[id].second) {
        swap(map[heap[id].first], map[heap[c].first]);
        swap(heap[id], heap[c]);
		this->heapifydown(c);
	}
}
