#include<string>
#include<map>
#include<vector>
#include<algorithm>

int convert_index(int x, int y) {
    return (x-1) + 8*(y-1);
}

// translate number to chess notation
std::string capitalizeString(std::string word) {
    transform(word.begin(), word.end(), word.begin(), [](unsigned char c){return std::toupper(c);});
    return word;
}
 
std::string convert_chess_notation(std::string initial_pos) { // not tested
    // initial position is a string of two numbers i.e. 11, 24
    std::map<int, std::string> position_map = {{1,"A",},{2,"B",},{3,"C",},{4,"D",},{5,"E",},{6,"F",},{7,"G",},{8,"H",}};
    std::string chess_notation;
    chess_notation = position_map.find(int(initial_pos[0]))->second;
    return chess_notation + initial_pos[1];
}

std::vector<int> decode_chess_notation(std::string notation) {
    std::vector<int> position = {0,0};
    char temp_string = notation[0];
    std::map<int, char> position_map = {{1,'A',},{2,'B',},{3,'C',},{4,'D',},{5,'E',},{6,'F',},{7,'G',},{8,'H',}};
    position[0] = position_map.find(temp_string)->first;
    position[1] = int(notation[1]);
    return position;
}


