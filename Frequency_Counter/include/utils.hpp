#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

string extractWord(const string& text, size_t pos);

size_t ignoreCommentOrString(const string& text, size_t pos);

bool sortByFrequency(const pair<string, int> a, const pair<string, int> b);

vector<pair<string, int>> unifyAndSort(const map<string, int> stringFrequency,
                                       const map<string, int> charFrequency);

void printToFile(string filename);