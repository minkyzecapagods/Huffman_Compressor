#pragma once

#include "HuffmanTree.hpp"
#include <vector>

using namespace std;

class MinHeap {
private:
    vector<NodePtr> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void push(const NodePtr& node);
    NodePtr pop();
    bool isEmpty() const;
    int size() const;
};