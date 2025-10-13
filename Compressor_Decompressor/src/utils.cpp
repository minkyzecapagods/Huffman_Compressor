#include "../include/utils.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include <unordered_map>

using namespace std;

unordered_map<string, size_t> frequencyCheet;

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
            frequencyCheet.insert({key, value});
        } else {
            cerr << "Linha inválida: " << line << endl;
        }
    }
}