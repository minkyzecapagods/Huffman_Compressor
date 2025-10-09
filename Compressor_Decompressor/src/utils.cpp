#include "../include/utils.hpp"
#include <iostream>
#include <unordered_map>

using namespace std;

bool compare::operator()(const shared_ptr<HuffmanNode>& left, 
                        const shared_ptr<HuffmanNode>& right) {
    // Min-heap: menor frequência tem maior prioridade
    return left->frequency > right->frequency;
}