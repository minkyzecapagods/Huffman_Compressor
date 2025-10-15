#include "../include/HuffmanTree.hpp"
#include "../include/MinHeap.hpp"
#include "../include/utils.hpp"

#include <memory>
#include <iostream>
#include <cstdint>
#include <unordered_map>

using namespace std;

unordered_map<string, string> huffmanCodes;
size_t maxTokenLength = 0;
NodePtr treeRoot = nullptr;

HuffmanNode::HuffmanNode(string data, size_t frequency, NodePtr left, NodePtr right){
    this->data = data;
    this->frequency = frequency;
    this->left = left;
    this->right = right;
}

bool HuffmanNode::isLeaf(){
    return this->left == nullptr && this->right == nullptr;
}

void storeCodes(const NodePtr& root, const string& str){
    if (!root) return;

    if (!root->left && !root->right){
        huffmanCodes[root->data] = str;
        return;
    }

    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

void buildHuffmanTree(const unordered_map<string, size_t>& frequencySheet){

    MinHeap pq;

    for (const auto& pair : frequencySheet) {
        pq.push(make_shared<HuffmanNode>(escapeCharToChar(pair.first), pair.second));
    }

    while (pq.size() > 1) {
        auto left = pq.pop();
        auto right = pq.pop();

        size_t sum = left->frequency + right->frequency;
        pq.push(make_shared<HuffmanNode>(string(), sum, left, right));
    }
    
    treeRoot = pq.pop();
    storeCodes(treeRoot, "");
    updateMaxTokenLength();
}


void updateMaxTokenLength(){
    for (const auto pair : huffmanCodes){
        if(pair.first.length() > maxTokenLength){
            maxTokenLength = pair.first.length();
        }
    }
}