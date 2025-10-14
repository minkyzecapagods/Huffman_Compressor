#include "../include/compressor.hpp"
#include "../include/HuffmanTree.hpp"
#include "../include/utils.hpp"

#include <cstddef>
#include <fstream>
#include <utility>
#include <cstdint>
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

string findLongestToken(ifstream& file){
    string longestMatch;
    string currentMatch;
    char ch;
    auto startPos = file.tellg();

    for(size_t i = 0; i < maxTokenLength && file.get(ch); i++){
        currentMatch += ch;

        if(huffmanCodes.find(currentMatch) != huffmanCodes.end()){
            longestMatch = currentMatch;
        }
    }

    file.clear();
    if (startPos != -1) {
        file.seekg(startPos + static_cast<std::streamoff>(longestMatch.length()));
    }
    return longestMatch;
}

void compressFile(const string& filename){
    ifstream inFile(filename);
    ofstream outFile(filename + "_compressed.bin", ios::binary);
    string allBits = "";
    if (!inFile.is_open()) {
        cerr << "Error: unable to open '" << filename << "'." << endl;
        return;
    }
    if (!outFile.is_open()){
        cerr << "Error: unable to create compressed file." << endl;
        return;
    }
    //maxTokenLength == 8
    while(inFile.peek() != EOF){
        string token = findLongestToken(inFile);
        if(!token.empty()){
            allBits += huffmanCodes.at(token);
        } else {
            char ch;
            inFile.get(ch);
            cerr << "Error: character not found in FrequencySheet" << endl;
            return;
        }
    }

    int padding = (8 - (allBits.length()%8)) % 8;
    string binPadding = decToBinary(padding); //quantos bits faltam para que tudo seja multiplo de 8

    allBits.append(padding, '0');

    unsigned char paddingByte = static_cast<unsigned char>(padding);

    outFile.write(reinterpret_cast<const char*>(&paddingByte), 1);

    for(size_t i = 0; i < allBits.size(); i += 8){
        string byteStr = allBits.substr(i, 8);
        unsigned char byte = static_cast<unsigned char>(stoi(byteStr, nullptr, 2));
        outFile.write(reinterpret_cast<const char*>(&byte), 1);
    }
    inFile.close(); outFile.close();
    cout << "Succesfull compression!" << endl;
}
