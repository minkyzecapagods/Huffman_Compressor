#pragma once

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

extern unordered_map<string, int> stringFrequency;
extern unordered_map<string, int> charFrequency;

extern vector<pair<string, int>> sortedTokens;

void processFile(const string& filename);