#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<iostream>

int convert_index(int x, int y) {
    return (x-1) + 8*(y-1);
}

// translate number to chess notation
std::string capitalizeString(std::string word) {
    transform(word.begin(), word.end(), word.begin(), [](unsigned char c){return std::toupper(c);});
    return word;
}
 
std::string convert_chess_notation(char character1, char character2) { // not tested
    std::cout << "does this even run?" << std::endl;
    std::string* position_map = new std::string[8]{"A","B","C","D","E","F","G","H"}; 
    int position;
    char* temp_character = &character1;
    std::sscanf(temp_character, "%d", &position);
    std::cout << "position" << position << " character1 " << character1<< std::endl;
    std::string chess_notation;
    for (int i{0}; i<8; i++) {
        if (position == i+1) {
            //character1 = position_map[i];
            //delete[] position_map;
            std::cout << "returns: " << position_map[i] << " " << character2 << std::endl;
            std::cout << "The retun is " << position_map[i]+std::to_string(character2) << std::endl;
            return position_map[i]+std::to_string(character2);
        }
    }
    return "";
}

std::vector<int> decode_chess_notation(std::string notation) {
    std::vector<int> position = {0,0};
    char character1 = notation[0];
    char character2 = notation[1];
    char* position_map = new char[8]{'A','B','C','D','E','F','G','H'}; 
    for (int i{0}; i<8; i++) {
        if (character1 == position_map[i]) {
            delete[] position_map;
            position[0] = i;
            position[1] = int(character2);
            return position;
        }
    }
    return {};  
}


