#include "../include/huffmanTree.hpp"
#include "../include/utils.hpp"

#include <iostream>

int main (int argc, char* argv[]){

    if(argc != 2){
        cerr << "Erro: número incorreto de argumentos!" << endl;
        return 1;
    }

    string name = argv[1];
    string filename = name + ".txt";

    processFile(filename); //popula o unordered_map frequencyCheet

    buildHuffmanTree(frequencyCheet);

    for (auto pair : huffmanCodes){
        cout << pair.first << " : " << pair.second << endl;
    }

    return 0;
}