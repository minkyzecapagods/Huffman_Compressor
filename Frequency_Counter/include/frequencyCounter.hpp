#pragma once

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

extern map<string, int> keywordCount;
extern map<string, int> operatorCount;
extern map<string, int> identifierCount;
extern map<string, int> charCount;
extern map<string, int> whitespaceCount;
extern map<string, int> frequentIdentifiers;

extern vector<pair<string, int>> sortedTokens;

extern int minimumFrequency; //frequencia minima para que a palavra seja considerada

void processFile(const string& filename);

void organizeTokens();