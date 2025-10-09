#include "../include/utils.hpp"
#include "../include/frequencyCounter.hpp"

#include <fstream>

using namespace std;

set<string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while", "class", "namespace",
        "new", "delete", "this", "friend", "private", "protected",
        "public", "virtual", "inline", "operator", "template", "try",
        "catch", "throw", "bool", "true", "false", "using", "typename",
        "explicit", "mutable", "export", "const_cast", "dynamic_cast",
        "reinterpret_cast", "static_cast", "and", "or", "not", "xor",
        "nullptr", "constexpr", "decltype", "noexcept", "override", "final"
    };

set<char> singleCharOps = {
    '+', '-', '*', '/', '%', '=', '<', '>', '!', '&', '|', '^', '~',
    '(', ')', '[', ']', '{', '}', ',', '.', ':', ';', '?'
};

set<string> twoCharOps = {
        "<<", ">>", "<=", ">=", "==", "!=", "&&", "||", "++", "--",
        "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=",
        "->", "::", ".*", "->*", "...", "##"
    };

set<string> threeCharOps = {"<<=", ">>=", "->*", "..."};

set<string> whitespaces = {
    " ", "\t", "\n", "\r", "\v", "\f"
};

bool isKeyword(const string& word){
    return keywords.find(word) != keywords.end();
}

string extractWord(const string& text, size_t pos){
    string word;

    while (pos < text.length() && (isalnum(text[pos]) || text[pos] == '_')) {
        word += text[pos];
        pos++;
    } 
    return word;
}

string isMultiCharOp(const string& text, size_t pos){
    if (pos + 3 <= text.length()){ //checa se é um operador de 3 caracteres
        string op3 = text.substr(pos, 3);
        if (threeCharOps.find(op3) != threeCharOps.end()){
            return op3;
        }
    } else if (pos + 2 <= text. length()) {
        string op2 = text.substr(pos, 2);
        if (twoCharOps.find(op2) != twoCharOps.end()){
            return op2;
        }
    }

    return ""; //caso nn seja
}

bool isSingleCharOp(char c) {
    return singleCharOps.find(c) != singleCharOps.end();
}

bool isInStringOrComment(const string& text, size_t pos){
    bool inSingleLineComment = false;
    bool inMultiLineComment = false;
    bool inString = false;
    bool inChar = false;
    char stringDelimiter = '"';
    char charDelimiter = '\'';

    for (size_t i = 0; i <= pos && i < text.length(); i++) {
        if (inSingleLineComment) {
            if (text[i] == '\n') {
                inSingleLineComment = false;
            }
            continue;
        }
        
        if (inMultiLineComment) {
            if (i > 0 && text[i-1] == '*' && text[i] == '/') {
                inMultiLineComment = false;
            }
            continue;
        }
        
        if (inString) {
            if (text[i] == stringDelimiter && text[i-1] != '\\') {
                inString = false;
            }
            continue;
        }
        
        if (inChar) {
            if (text[i] == charDelimiter && text[i-1] != '\\') {
                inChar = false;
            }
            continue;
        }
        
        // Check for comments and strings
        if (i + 1 < text.length()) {
            if (text[i] == '/' && text[i+1] == '/') {
                inSingleLineComment = true;
                i++;
                continue;
            }
            if (text[i] == '/' && text[i+1] == '*') {
                inMultiLineComment = true;
                i++;
                continue;
            }
        }
        
        if (text[i] == '"') {
            inString = true;
            stringDelimiter = '"';
            continue;
        }
        
        if (text[i] == '\'') {

            inChar = true;
            charDelimiter = '\'';
            continue;
        }
    }
    
    return inSingleLineComment || inMultiLineComment || inString || inChar;
}

bool sortByFrequency(const pair<string, int> a, const pair<string, int> b){
    return a.second > b.second; 
}

vector<pair<string, int>> unifyAndSort(const map<string, int> keywordCount,
                                       const map<string, int> operatorCount,
                                       const map<string, int> frequentIdentifiers,
                                       const map<string, int> charCount,
                                       const map<string, int> whitespaceCount){
    vector<pair<string, int>> allTokens;

    for (const auto& pair : keywordCount){
        allTokens.push_back(make_pair(pair.first, pair.second));
    }

    for (const auto& pair : operatorCount){
        allTokens.push_back(make_pair(pair.first, pair.second));
    }

    for (const auto& pair : frequentIdentifiers){
        allTokens.push_back(make_pair(pair.first, pair.second));
    }

    for (const auto& pair : charCount){
        allTokens.push_back(make_pair(pair.first, pair.second));
    }

    for (const auto& pair : whitespaceCount){
        allTokens.push_back(make_pair(pair.first, pair.second));
    }

    sort(allTokens.begin(), allTokens.end(), sortByFrequency);

    return allTokens;
};


void printToFile(string filename){
    ofstream outputFile("frequency_cheat/" +filename + ".txt");
    for (pair<string, int> i : sortedTokens){
        outputFile << '"' << i.first << '"' << ' ' << i.second << endl;
    }
}