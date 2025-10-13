#include "../include/HuffmanTree.hpp"
#include "../include/MinHeap.hpp"
#include "../include/utils.hpp"

#include <memory>
#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<string, string> huffmanCodes;
NodePtr treeRoot = nullptr;

HuffmanNode::HuffmanNode(string data, size_t frequency, NodePtr left, NodePtr right){
    this->data = data;
    this->frequency = frequency;
    this->left = left;
    this->right = right;
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
}

void serializeTreeBinary(NodePtr node, vector<unsigned char>& buffer) {
    if (!node) return;

    if (!node->left && !node->right) {
        buffer.push_back(1); // marcador de folha

        // grava tamanho da string (4 bytes)
        uint32_t len = node->data.size();
        const unsigned char* lenBytes = reinterpret_cast<const unsigned char*>(&len);
        buffer.insert(buffer.end(), lenBytes, lenBytes + sizeof(len));

        // grava bytes da string literal
        buffer.insert(buffer.end(), node->data.begin(), node->data.end());
    } 
    else {
        buffer.push_back(0); // marcador de nó interno
        serializeTreeBinary(node->left, buffer);
        serializeTreeBinary(node->right, buffer);
    }
}

vector<unsigned char> serializeTree() {
    vector<unsigned char> buffer;
    serializeTreeBinary(treeRoot, buffer);
    return buffer;
}