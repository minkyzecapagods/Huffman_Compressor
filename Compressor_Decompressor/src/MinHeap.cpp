#include "../include/MinHeap.hpp"
#include "../include/HuffmanTree.hpp"

void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap[index]->frequency >= heap[parentIndex]->frequency) break;
        swap(heap[index], heap[parentIndex]);
        index = parentIndex;
    }
}

void MinHeap::heapifyDown(int index) {
    int size = heap.size();
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && heap[leftChild]->frequency < heap[smallest]->frequency) {
            smallest = leftChild;
        }
        if (rightChild < size && heap[rightChild]->frequency < heap[smallest]->frequency) {
            smallest = rightChild;
        }
        if (smallest == index) break;
        swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

void MinHeap::push(const NodePtr& node) {
    heap.push_back(node);
    heapifyUp(heap.size() - 1);
}

NodePtr MinHeap::pop() {
    if (heap.empty()) return nullptr;
    NodePtr root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return root;
}

bool MinHeap::isEmpty() const {
    return heap.empty();
}

int MinHeap::size() const {
    return heap.size();
}