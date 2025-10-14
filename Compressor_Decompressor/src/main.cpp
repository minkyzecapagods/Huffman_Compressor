#include "../include/HuffmanTree.hpp"
#include "../include/utils.hpp"
#include "../include/compressor.hpp"
#include "../include/decompressor.hpp"

#include <iostream>

int main (int argc, char* argv[]){
    string argv1, argv2, argv3;
    if (argc >= 2) argv1 = argv[1];
    if (argc >= 3) argv2 = argv[2];
    if (argc >= 4) argv3 = argv[3];

    if (argc == 2 && (argv1 == "--help" || argv1 == "-h")) {
        cout << "Usage: " << argv[0] << " <frequency_sheet> <file_to_compress>" << endl;
        return 0;
    }

    cout << "Arguments received: " << endl;

    if (argv1 == "--compress" || argv1 == "-c") {
        cout << "Compressing file: " << argv3 << " using frequency sheet: " << argv2 << endl;
        processFile(argv2); //popula o unordered_map frequencySheet
        buildHuffmanTree(frequencySheet);
        compressFile(argv3);

        return 0;
    }

    if (argv1 == "--decompress" || argv1 == "-d") {
        cout << "Decompressing file: " << argv3 << " using frequency sheet: " << argv2 << endl;
        processFile(argv2); //popula o unordered_map frequencySheet
        buildHuffmanTree(frequencySheet);
        decompressFile(argv3);

        return 0;
    }

    for (auto pair : huffmanCodes){
       cout << pair.first << " : " << pair.second << endl;
    }
//zzzzzz
    return 0;
}