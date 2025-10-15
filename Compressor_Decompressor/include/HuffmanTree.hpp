#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
using namespace std;

extern unordered_map<string, string> huffmanCodes;
extern size_t maxTokenLength;

struct HuffmanNode{
    string data;
    size_t frequency;
    shared_ptr<HuffmanNode> left;
    shared_ptr<HuffmanNode> right;

    //construtor
    HuffmanNode(string data, size_t frequency, shared_ptr<HuffmanNode> left = nullptr, shared_ptr<HuffmanNode> right = nullptr);

    bool isLeaf();
};

using NodePtr = std::shared_ptr<HuffmanNode>;

extern NodePtr treeRoot;

//constrói a arvore
void buildHuffmanTree(const unordered_map<string, size_t>& frequencySheet);

void updateMaxTokenLength();
