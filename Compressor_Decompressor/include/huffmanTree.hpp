#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
using namespace std;

extern unordered_map<string, string> huffmanCodes;

struct HuffmanNode{
    string data;
    size_t frequency;
    shared_ptr<HuffmanNode> left;
    shared_ptr<HuffmanNode> right;

    HuffmanNode(string data, size_t frequency, shared_ptr<HuffmanNode> left = nullptr, shared_ptr<HuffmanNode> right = nullptr);

};

void buildHuffmanTree(const unordered_map<string, size_t>& frequencyCheet);

void storeCodes(const shared_ptr<HuffmanNode>& root, const string& str);

