#include "../include/huffmanTree.hpp"
#include "../include/utils.hpp"

#include <memory>
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

unordered_map<string, string> huffmanCodes;

HuffmanNode::HuffmanNode(string data, size_t frequency, NodePtr left, NodePtr right){
    this->data = data;
    this->frequency = frequency;
    this->left = left;
    this->right = right;
}

void buildHuffmanTree(const unordered_map<string, size_t>& frequencyCheet){

    priority_queue<NodePtr, vector<NodePtr>, compare> pq;

    for (const auto& pair : frequencyCheet) {
        pq.push(make_shared<HuffmanNode>(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();

        size_t sum = left->frequency + right->frequency;
        pq.push(make_shared<HuffmanNode>(string(), sum, left, right));
    }
    
    auto root = pq.top();
    storeCodes(root, "");
}

void storeCodes(const NodePtr& root, const string& str){
    if (!root) return;

    if (!root->left && !root->right){
        huffmanCodes[root->data] = str;
    }

    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

