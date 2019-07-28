#pragma once
#include <unordered_map>
#include <string>

struct VisualizableNoun { std::string word = ""; int score = INT_MIN; };

extern std::unordered_map<std::string, VisualizableNoun> dictionary;

