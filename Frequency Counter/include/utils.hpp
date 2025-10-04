#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

// Declarations only: define these in a single .cpp to avoid multiple-definition linker errors
extern set<string> keywords;
extern set<char> singleCharOps;
extern set<string> twoCharOps;
extern set<string> threeCharOps;
extern set<string> whitespaces;

bool isKeyword(const string& word);

string extractWord(const string& text, size_t pos);

bool isSingleCharOp(char c);

string isMultiCharOp(const string& text, size_t pos);

bool isInStringOrComment(const string& text, size_t pos);

bool sortByFrequency(const pair<string, int> a, const pair<string, int> b);

vector<pair<string, int>> unifyAndSort(const map<string, int> keywordCount,
                                       const map<string, int> operatorCount,
                                       const map<string, int> frequentIdentifiers,
                                       const map<string, int> charCount,
                                       const map<string, int> whitespaceCount);