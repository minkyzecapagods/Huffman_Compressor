#include "../include/frequencyCounter.hpp"
#include "../include/utils.hpp"

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

map<string, int> keywordCount;
map<string, int> operatorCount;
map<string, int> identifierCount;
map<string, int> charCount;
map<string, int> whitespaceCount;
map<string, int> frequentIdentifiers;

vector<pair<string, int>> sortedTokens;

int minimumFrequency = 2;

void processFile(const string& filename){
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return;
    }

    string fullText;
    string line;

    while(getline(file, line)){
        fullText += line + "\n";
    }
    file.close();

    size_t totalchars = fullText.length();

    //primeiro checa a quantidade de vezes que cada palavra (identifier) aparece
    for (size_t i = 0; i < fullText.length(); i++){
        char currentChar = fullText[i];

        if(isspace(currentChar)){ continue; }

        if (isInStringOrComment(fullText, i)) { continue; }

        string multiOp = isMultiCharOp(fullText, i);
        if (!multiOp.empty()){
            i += multiOp.length() - 1;
            continue;
        }

        if (isSingleCharOp(currentChar)) { continue; }

        if (isalpha(currentChar) || currentChar == '_'){
            string word = extractWord(fullText, i);

            if (!isKeyword(word)){
                identifierCount[word]++;
            }
            i +=word.length() - 1;
            continue;
        }
    }

    for (size_t i = 0; i < totalchars; i++){
        char currentChar = fullText[i];

        if (currentChar == '\n') {
            whitespaceCount["\\n"]++;
            continue;
        } else if (isspace(currentChar)) {
            string tempString(1, currentChar);
            whitespaceCount[tempString]++;
            continue;
        }

        if (isInStringOrComment(fullText, i)){
            string tempString(1, currentChar);
            charCount[tempString]++;
            continue;
        }

        string multiOp = isMultiCharOp(fullText, i);
        if(!multiOp.empty()){
            operatorCount[multiOp]++;
            for(char c : multiOp){
                string tempString(1, c);
                charCount[tempString]++;
            }
            i += multiOp.length();
            continue;
        }

        if (isSingleCharOp(currentChar)){
            string singleOp(1, currentChar);
            operatorCount[singleOp]++;
            continue;
        }

        if(isalpha(currentChar) || currentChar == '_') {
            string word = extractWord(fullText, i);

            if(isKeyword(word)){
                keywordCount[word]++;
            } else if (identifierCount[word] <= minimumFrequency) { //se a palavra for pouco frequente;
                for (char c : word){ 
                    string tempString(1, c);                               //os chars dela são contados
                    charCount[tempString]++;
                }
            }


            i+= word.length() - 1; //pula para o final da palavra
            continue;
        }
    }

    for (const auto& identifier : identifierCount){ //filtra palavras pouco frequentes 
        if (identifier.second > minimumFrequency){
            frequentIdentifiers[identifier.first] = identifier.second;
        }
    }  
}

void organizeTokens(){
    vector<pair<string, int>> allTokens;

    sortedTokens = unifyAndSort(keywordCount,
                                operatorCount,
                                frequentIdentifiers,
                                charCount,
                                whitespaceCount);
}