#ifndef FUNCTION_H
#define FUNCTION_H
#include<string>
#include<map>
#include<vector>
#include<algorithm>

int convert_index(int x, int y);
std::string capitalize_string(std::string word);
std::string convert_chess_notation(char character1, char character2);
std::vector<int> decode_chess_notation(std::string initial_pos);
#endif
