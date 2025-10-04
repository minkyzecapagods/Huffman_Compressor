#include "../include/FrequencyCounter.hpp"

#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main (int argc, char* argv[]){

    if(argc != 2){
        cerr << "Erro: número incorreto de argumentos!" << endl;
        return 1;
    }
    string filename = argv[1];

    processFile(filename);
    
    organizeTokens();
    
    for (pair<string, int> i : sortedTokens){
        cout << i.first << " : " << i.second << endl;
    }

    
    return 0;
}