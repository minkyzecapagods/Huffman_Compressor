#include "../include/frequencyCounter.hpp"
#include "../include/utils.hpp"

using namespace std;

int main (int argc, char* argv[]){

    if(argc != 2){
        cerr << "Error: incorrect number of arguments!" << endl;
        return 1;
    }
    string filename = argv[1];

    getFullCharMap();

    processFile(filename);
    
    sortedTokens = unifyAndSort(stringFrequency, charFrequency);

    printToFile("output");

    return 0;
}