#include "../include/compressor.hpp"
#include "../include/decompressor.hpp"
#include "../include/HuffmanTree.hpp"
#include "../include/utils.hpp"
#include <string>

void decompressFile(const string& filename){
    string allBits = binToString(filename);

    if (allBits.empty()) {
        cerr << "Error: no bits read from file '" << filename << "'" << endl;
        return;
    }

    // First byte contains padding (8 bits)
    if (allBits.size() < 8) {
        cerr << "Error: input too short to contain padding info" << endl;
        return;
    }

    string binPadding = allBits.substr(0, 8);
    int padding = stoi(binPadding, nullptr, 2);

    // The rest are data bits; remove the padding bits at the end
    string dataBits = allBits.substr(8);
    if (padding > 0 && padding <= static_cast<int>(dataBits.size())) {
        dataBits = dataBits.substr(0, dataBits.size() - padding);
    }

    string finalText = "";
    size_t index = 0;
    while (index < dataBits.length()) {
        string decoded = decodeBitSequence(treeRoot, dataBits, index);
        if (decoded.empty()) break;
        finalText.append(decoded);
    }

    size_t pos = filename.find("_compressed.bin");
    string basename = filename;
    if (pos != string::npos) {
        basename = filename.substr(0, pos);
    }

    // write to output file with original basename + _decompressed
    string outFilename = basename + "_decompressed";
    ofstream outFile(outFilename);
    if (!outFile) {
        cerr << "Error: could not create output file '" << outFilename << "'" << endl;
        return;
    }

    outFile << finalText;
    outFile.close();
}