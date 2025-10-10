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

    //construtor
    HuffmanNode(string data, size_t frequency, shared_ptr<HuffmanNode> left = nullptr, shared_ptr<HuffmanNode> right = nullptr);

};

//constrói a arvore
void buildHuffmanTree(const unordered_map<string, size_t>& frequencyCheet);

//guarda os códigos de cada token no unordered_map huffmanCodes
void storeCodes(const shared_ptr<HuffmanNode>& root, const string& str);

