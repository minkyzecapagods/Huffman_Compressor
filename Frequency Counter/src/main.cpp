#include "../include/FrequencyCounter.hpp"
#include "../include/utils.hpp"

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

    printToFile("teste");

    return 0;
}