#pragma once

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

extern map<string, int> charFrequency;
extern map<string, int> stringFrequency;

extern vector<pair<string, int>> sortedTokens;

void processFile(const string& filename);