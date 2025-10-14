#include "../include/utils.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include <unordered_map>

using namespace std;

unordered_map<string, size_t> frequencySheet;

bool compare::operator()(const NodePtr& left, 
                        const NodePtr& right) {
    // Min-heap: menor frequência tem maior prioridade
    return left->frequency > right->frequency;
}

void processFile(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error: unable to open '" << filename << "'." << endl;
        return;
    }
    regex linePattern(R"REG(^"((?:\\x[0-9A-Fa-f]{2}|\\[abfnrtv\\'"]|[A-Za-z0-9_]|.)+)" ([0-9]+)$)REG");
    string line;
    smatch match;

    while (getline(file, line)) {
        if (regex_match(line, match, linePattern)) {
            string key = match[1].str();   // conteúdo entre aspas
            int value = stoi(match[2].str()); // número após o espaço
            frequencySheet.insert({key, value});
        } else {
            cerr << "Linha inválida: " << line << endl;
        }
    }
}

string escapeCharToChar(string s) {
    if (s == "\\n") return "\n";
    if (s == "\\a") return "\a";
    if (s == "\\b") return "\b";
    if (s == "\\t") return "\t";
    if (s == "\\v") return "\v";
    if (s == "\\f") return "\f";
    if (s == "\\r") return "\r";
    if (s.size() == 4 && s.compare(0, 2, "\\x") == 0) return s.erase(0, 1);
    return s;
}

string byteToBinaryString(unsigned char byte){
    return bitset<8>(byte).to_string();
}

string binToString(const string& filename = "../output.bin"){
    ifstream bin(filename);

    if(!bin){
        cerr << "Error: could not open " << filename << endl;
        return "";
    }

    string bytesAsBinary;
    unsigned char byte;

    while(bin.read(reinterpret_cast<char*>(&byte), sizeof(byte))){
        string binaryStr = byteToBinaryString(byte);
        bytesAsBinary += binaryStr;
    }

    bin.close();

    return bytesAsBinary;
}

string decToBinary(int n){
    
    string bin = "";
    while (n > 0) {
        // checking the mod 
		int bit = n%2;
      	bin.push_back('0' + bit);
        n /= 2;
    }
    
    // reverse the string 
	reverse(bin.begin(), bin.end());
    return bin;
}

string decodeBitSequence(const NodePtr root, const string& bits, size_t& index){
    NodePtr current = root;
    // Traverse the tree consuming bits until a leaf is reached or we run out of bits
    while (!current->isLeaf() && index < bits.size()) {
        if (bits[index] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        // advance the index for each bit consumed
        ++index;
        if (!current) break;
    }

    if (current && current->isLeaf()) {
        return current->data;
    } else {
        cerr << "Error: could not get to a leaf node in the Huffman Tree." << endl;
        return "";
    }
}