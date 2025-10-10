#include "../include/utils.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>

using namespace std;

unordered_map<string, size_t> frequencyCheet;

bool compare::operator()(const shared_ptr<HuffmanNode>& left, 
                        const shared_ptr<HuffmanNode>& right) {
    // Min-heap: menor frequência tem maior prioridade
    return left->frequency > right->frequency;
}

void processFile(const string& fileName){
    ifstream file(fileName);
    if(!file.is_open()){
        cerr << "Error: Could not open the file." << endl;
        return;
    }

    string line;

    while(getline(file, line)){ //deve ter uma maneira melhor de fazer isso com regex :P
        istringstream iss(line);
        string data;
        size_t frequency;
        char c;
        
        if(!(iss >> c) || c != '"'){
            cerr << "Error: Expected opening quote." << endl;
            continue;
        }

        bool firstChar = true; // necessário para a leitura de aspas duplas literais

        while(iss.get(c)){
            if(c == '"' && !firstChar){
                break;
            }
            firstChar = false;
            data += c;
        }

        if (c != '"'){
            cerr << "Error: No closing quote found." << endl;
            continue;
        }

        iss >> ws;

        if(!(iss >> frequency)){
            cerr << "Error: Worng frequency format. Line: " << line << endl;
            continue;
        }

        frequencyCheet.insert({data, frequency});
    }
}