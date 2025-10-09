#pragma once
#include "huffmanTree.hpp"
#include <iostream>

// Comparator for priority_queue used by Huffman tree (min-heap by frequency)
struct compare{
    bool operator()(const shared_ptr<HuffmanNode>& left, const shared_ptr<HuffmanNode>& right);
};