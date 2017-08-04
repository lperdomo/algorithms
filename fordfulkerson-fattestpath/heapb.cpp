#include "heapb.h"

HeapB::HeapB()
{
}

HeapB::~HeapB()
{
}

long HeapB::size()
{
	return heap.size();
}

long HeapB::left(long parent)
{
	long i = 2*parent+1;
	if (i < heap.size()) {
		return i;
	}
	return -1;
}

long HeapB::right(long parent)
{
	long i = 2*parent+2;
	if (i < heap.size()) {
		return i;
	}
	return -1;
}

long HeapB::parent(long child)
{
	if (child != 0) {
		return (child-1)/2;
	}
	return -1;
}

Node HeapB::makeNode(long vertex, long capacity)
{
	return make_pair(vertex, capacity);
}

void HeapB::insert(Node node)
{
	heap.push_back(node);
	heapifyup(heap.size() - 1);
}

void HeapB::insert(long vertex, long capacity)
{
	Node node = makeNode(vertex, capacity);
	insert(node);
}

Node HeapB::deleteMax()
{
	Node node = heap.front();
	swap(heap[0], heap[heap.size()-1]);
	heap.pop_back();
	heapifydown(0);
	return node;
}

void HeapB::update(long vertex, long capacity)
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

void HeapB::heapifyup(long id)
{
	if (id != 0) {
		if (heap[parent(id)].second < heap[id].second) {
			swap(heap[parent(id)], heap[id]);
			heapifyup(parent(id));
		}
	}
}

void HeapB::heapifydown(long id)
{
	long leftChild = left(id);
	long rightChild = right(id);
	if (leftChild == -1 && rightChild == -1) {
		return;
	}
	if (rightChild == -1) {
		if (heap[leftChild].second > heap[id].second) {
			swap(heap[leftChild], heap[id]);
		}
	} else if (leftChild == -1) {
		if (heap[rightChild].second > heap[id].second) {
			swap(heap[rightChild], heap[id]);
		}
	} else if ((heap[id].second < heap[leftChild].second)
			|| (heap[id].second < heap[rightChild].second)) {
		if (heap[leftChild].second > heap[rightChild].second) {
			swap(heap[id], heap[leftChild]);
			heapifydown(leftChild);
		} else {
			swap(heap[id], heap[rightChild]);
			heapifydown(rightChild);
		}
	}
}
