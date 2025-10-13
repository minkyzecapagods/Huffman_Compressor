#include "../include/HuffmanTree.hpp"
#include "../include/utils.hpp"

#include <iostream>

int main (int argc, char* argv[]){

    if(argc != 2){
        cerr << "Erro: número incorreto de argumentos!" << endl;
        return 1;
    }

    string filename = argv[1];

    processFile(filename); //popula o unordered_map frequencyCheet

    buildHuffmanTree(frequencyCheet);

    for (auto pair : huffmanCodes){
        cout << pair.first << " : " << pair.second << endl;
    }

    return 0;
}