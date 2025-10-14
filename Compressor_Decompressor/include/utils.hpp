#pragma once
#include "HuffmanTree.hpp"
#include <iostream>
#include <unordered_map>

extern unordered_map<string, size_t> frequencySheet;

//comparador de HuffmanNodes para a criação da priority queue
struct compare{
    bool operator()(const NodePtr& left, const NodePtr& right);
};


//transforma o .txt do Frequency_Counter em um unordered_map
void processFile(const string& fileName);

string escapeCharToChar(string s);

string binToString(const string& filename);

string byteToBinaryString(unsigned char byte);

string decToBinary(int n);

string decodeBitSequence(const NodePtr root, const string& bits, size_t& index);