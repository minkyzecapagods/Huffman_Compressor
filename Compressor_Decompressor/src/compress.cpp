#include "../include/compressor.hpp"
#include "../include/HuffmanTree.hpp"

#include <fstream>
#include <utility>
#include <vector>

using namespace std;

vector<unsigned char> bitsToBytes(const string& bits) {
    vector<unsigned char> bytes;
    unsigned char currentByte = 0;
    int bitCount = 0;

    for (char bit : bits) {
        currentByte <<= 1;
        if (bit == '1') currentByte |= 1;
        bitCount++;

        if (bitCount == 8) {
            bytes.push_back(currentByte);
            currentByte = 0;
            bitCount = 0;
        }
    }

    if (bitCount > 0) {
        currentByte <<= (8 - bitCount); // completa com zeros à direita
        bytes.push_back(currentByte);
    }

    return bytes;
}

void compressFile(const string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: unable to open '" << filename << "'." << endl;
        return;
    }

    string fullText((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    file.close();

    ofstream output("output.bin", ios::binary);
    if (!output.is_open()) {
        cerr << "Error: unable to create output file." << endl;
        return;
    }

    vector<unsigned char> serializedTree = serializeTree();
    uint64_t treeSize = serializedTree.size();
    output.write(reinterpret_cast<const char*>(&treeSize), sizeof(treeSize));
    output.write(reinterpret_cast<const char*>(serializedTree.data()), serializedTree.size());

    string compressedText = "";

    for (size_t i = 0; i < fullText.size(); i++) {
        string currentChar = string(1, fullText[i]);
        if (huffmanCodes.find(currentChar) != huffmanCodes.end()){
            compressedText += huffmanCodes[currentChar];
            cout << huffmanCodes[currentChar] << " ";
        }
        else {
            cerr << "Warning: character '" << currentChar << "' not found in Huffman codes." << endl;
        }
    }
    vector<unsigned char> byteData = bitsToBytes(compressedText);
    output.write(reinterpret_cast<const char*>(byteData.data()), byteData.size());

    output.close();
}