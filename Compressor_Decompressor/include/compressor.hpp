#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

void compressFile(const std::string& filename);

string findLongestToken(ifstream& file);