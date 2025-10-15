#include "../include/utils.hpp"
#include "../include/frequencyCounter.hpp"

#include <fstream>

using namespace std;

const string outputPath = "frequency_sheet/";

string getPrintableChar(char c) {
    // Representações legíveis para caracteres de controle
    switch (c) {
        case '\a': return "\\a";
        case '\b': return "\\b";
        case '\t': return "\\t";
        case '\n': return "\\n";
        case '\v': return "\\v";
        case '\f': return "\\f";
        case '\r': return "\\r";
        default:
            if (static_cast<unsigned char>(c) < 32 || c == 127) {
                return "\\x" + to_string(static_cast<int>(c)); // outros caracteres de controle
            } else {
                return string(1, c); // caracteres imprimíveis
            }
    }
}

void getFullCharMap() {
    // ASCII de 0 a 127
    for (int i = 0; i <= 127; ++i) {
        char c = static_cast<char>(i);
        string key = getPrintableChar(c);
        if (key.rfind("\\x", 0) == 0) continue;
        charFrequency[key] = 0; // frequência inicial zero
    }
}


string extractWord(const string& text, size_t pos){
    string word = "";

    while (pos < text.length() && 
    (isalnum(static_cast<unsigned char>(text[pos])) ||
    text[pos] == '_')) {
        word += text[pos];
        pos++;
    }

    return word;
}

// Retorna a posição logo após o comentário ou string, ou npos se não for comentário ou string
size_t ignoreCommentOrString(const string& text, size_t pos){
    size_t textSize = text.size();

    if (pos + 1 < textSize && text.substr(pos, 2) == "//") {
        stringFrequency["//"]++;
        size_t end = text.find('\n', pos + 2);
        if (end == string::npos) return textSize;
        charFrequency["\\n"]++;
        return end + 1;
    }
        
    if (pos + 1 < textSize && text.substr(pos, 2) == "/*") {
        stringFrequency["/*"]++;
        size_t end = text.find("*/", pos + 2);
        if (end == string::npos) return textSize;
        stringFrequency["*/"]++;
        return end + 2;
    }

    if (text[pos] == '"') {
        charFrequency["\""]++; 
        size_t end = text.find('"', pos + 1);
        if (end == string::npos) return textSize;
        charFrequency["\""]++; 
        return end + 1;
    }

    return string::npos;
}

bool sortByFrequency(const pair<string, int> a, const pair<string, int> b){
    return a.second > b.second; 
}

vector<pair<string, int>> unifyAndSort(const unordered_map<string, int> charFrequency,
                                       const unordered_map<string, int> stringFrequency){
    vector<pair<string, int>> allTokens;

    for (const auto& pair : charFrequency)
        allTokens.push_back(pair);

    for (const auto& pair : stringFrequency)
        allTokens.push_back(pair);

    sort(allTokens.begin(), allTokens.end(), sortByFrequency);

    return allTokens;
};


void printToFile(string filename){
    ofstream outputFile(outputPath + filename + ".txt");
    for (pair<string, int> i : sortedTokens){
        outputFile << '"' << i.first << '"' << ' ' << i.second << endl;
    }
}