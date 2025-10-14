#include "../include/frequencyCounter.hpp"
#include "../include/utils.hpp"

#include <fstream>
#include <utility>

using namespace std;

map<string, int> stringFrequency;
map<string, int> charFrequency;

vector<pair<string, int>> sortedTokens;

const int MIN_FREQUENCY = 3;

void processFile(const string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: unable to open '" << filename << "'." << endl;
        return;
    }

    string fullText((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    file.close();

    size_t totalChars = fullText.length();

    for (size_t i = 0; i < totalChars; i++) {
        char currentChar = fullText[i];

        if (isalnum(currentChar) || currentChar == '_'){
            string word = extractWord(fullText, i);
            stringFrequency[word]++;
            i += word.length() - 1; //pula para o final da palavra
            continue;
        }

        size_t j = ignoreCommentOrString(fullText, i);
        if (j != string::npos) {
            i = j - 1;
            continue;
        }
        
        charFrequency[getPrintableChar(fullText[i])]++;
    }

    for (auto it = stringFrequency.begin(); it != stringFrequency.end(); ){ //filtra palavras pouco frequentes 
        if (it->second < MIN_FREQUENCY){
            for (char c : it->first)
                charFrequency[string(1, c)] += it->second;
            it = stringFrequency.erase(it);
        }
        else ++it;
    }  
}