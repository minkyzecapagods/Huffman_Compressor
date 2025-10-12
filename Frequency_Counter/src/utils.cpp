#include "../include/utils.hpp"
#include "../include/frequencyCounter.hpp"

#include <fstream>

using namespace std;

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

vector<pair<string, int>> unifyAndSort(const map<string, int> charFrequency,
                                       const map<string, int> stringFrequency){
    vector<pair<string, int>> allTokens;

    for (const auto& pair : charFrequency)
        allTokens.push_back(pair);

    for (const auto& pair : stringFrequency)
        allTokens.push_back(pair);

    sort(allTokens.begin(), allTokens.end(), sortByFrequency);

    return allTokens;
};


void printToFile(string filename){
    ofstream outputFile("frequency_cheat/" +filename + ".txt");
    for (pair<string, int> i : sortedTokens){
        outputFile << '"' << i.first << '"' << ' ' << i.second << endl;
    }
}