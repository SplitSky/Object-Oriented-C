// this file contains classes
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#include<algorithm>
#include "functions.h"
#include "classes.h"



piece::piece() {
    position[0] = 1;
    position[1] = 1;
    name = "empty";
    point_value = 0;
};
piece::piece(int x, int y, std::string init_name, int init_point) : name{init_name}, point_value{init_point} {
    position[0] = x;
    position[1] = y;
    removed = false;
};
piece::~piece() {};

std::string piece::get_pos() {
    return std::to_string(position[0]) + "," + std::to_string(position[1]);
}

void piece::piece_moved() {
    moved = true;
}

void piece::set_pos(int x, int y) {
    position[0] = x;
    position[1] = y;
}

int* piece::get_pos_point() {
    return position;
}

bool piece::find_possible_moves(int* board) {
    return false;
}

std::vector<std::string> piece::list_moves() {return possible_moves;}

std::string piece::get_name() {return name;}

bool piece::is_removed() { return removed; }

int piece::get_point() { return this->point_value; }

bool piece::find_attack_moves(int* board) {return false;}

void piece::set_possible_moves(std::vector<std::string> moves) {
    std::vector<std::string>().swap(possible_moves);
    // deallocates memory
    possible_moves = moves;
}

void piece::remove() {removed = true;}


// pawn definitions

pawn::pawn() :piece{} {
    name = "pawn";
    point_value = 1;
};
pawn::pawn(int x, int y, int init_point) : piece{x,y,"pawn", init_point} {}
pawn::~pawn() {
    possible_moves.clear();
    possible_moves.swap(possible_moves);
}

bool pawn::find_possible_moves(int* board) {
    possible_moves.clear();
    std::string temp_string;
    bool check{false};
    int* x_moves;
    x_moves = new int[2]{+1,-1};
    possible_moves.clear();


    // move ahead
    if ((position[1]-point_value >= 1) || (position[1]-point_value <= 8)) {
        if (board[convert_index(position[0], position[1] + point_value)] == 0) { // if the place ahead is empty
            temp_string = std::to_string(position[0]) + std::to_string(position[1] + point_value);
            possible_moves.push_back(temp_string);
            temp_string = "";
            
            if ((board[convert_index(position[0], position[1] + 2*point_value)] == 0) && (moved == false)) {
                // double move
                temp_string = std::to_string(position[0]) + std::to_string(position[1] + 2*point_value);
                possible_moves.push_back(temp_string);
                temp_string = "";              
            }

        }
    }

    for (size_t i{0}; i<2; i++) {
        if ((1 <= position[0] + x_moves[i]) && (8 >= position[0] + x_moves[i])) { // check range y-axis
            if ((1 <= position[1] + point_value) && (8 >= position[1] + point_value)) { // check range x-axis
                if (board[convert_index(position[0] + x_moves[i], position[1] + point_value)]*point_value < 0) { // the piece in the place is enemy
                    temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + point_value);
                    possible_moves.push_back(temp_string);
                    temp_string = "";                           
                    if (board[convert_index(position[0] + x_moves[i], position[1] + point_value)]*point_value == -10) {check = true;}
                }
            }
        }
    }
    delete x_moves;

    return check;
}

bool pawn::find_attack_moves(int* board) {
    possible_moves.clear();
    std::string temp_string;
    bool check{false};
    int* x_moves;
    x_moves = new int[2]{+1,-1};
    possible_moves.clear();

    for (size_t i{0}; i<2; i++) {
        if ((1 <= position[0] + x_moves[i]) && (8 >= position[0] + x_moves[i])) { // check range y-axis
            if ((1 <= position[1] + point_value) && (8 >= position[1] + point_value)) { // check range x-axis
                if (board[convert_index(position[0] + x_moves[i], position[1] + point_value)]*point_value < 0) { // the piece in the place is enemy
                    temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + point_value);
                    danger_moves.push_back(temp_string);
                    temp_string = "";                           
                    if (board[convert_index(position[0] + x_moves[i], position[1] + point_value)]*point_value == -10) {check = true;}
                }
            }
        }
    }
    delete x_moves;
    return check;
}

// knight definitions

knight::knight() :piece{} {
    name = "knight";
    point_value = 3;
}
knight::knight(int x, int y, int init_point) : piece{x,y,"knight", init_point} {
    // position holds values 1-8
    position[0] = x;
    position[1] = y;
}
knight::~knight() {
    possible_moves.clear();
    possible_moves.swap(possible_moves);
};
bool knight::find_possible_moves(int* board) {
    std::string temp_string;
    possible_moves.clear();
    bool check{false};
    // first move
    int* x_moves;
    x_moves = new int[8]{-2,-1,+2,-1,-2,+1,+2,+1};
    int* y_moves;
    y_moves = new int[8]{-1,-2,+1,+2,+1,-2,-1,+2};

    for (size_t i{0}; i<8; i++) {
        if ((0 < position[0] + x_moves[i]) && (9 > position[0] + x_moves[i])) { // check range
            if ((0 < position[1] + y_moves[i]) && (9 > position[1] + y_moves[i])) {

                if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])] == 0) { // if the place is empty
                    temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";

                } else if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])]*point_value < 0) {
                    temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";                           
                    // enemy piece on the square
                    if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])]*point_value == -30) {
                        check = true;
                    }
                }
            }
        }
    }
    delete x_moves;
    delete y_moves;
    return check;
}

// bishop definitions

bishop::bishop() : piece{} {
    name = "bishop";
    point_value = 4;
}

bishop::bishop(int x, int y, int init_point) : piece{x,y,"bishop", init_point} {
    position[0] = x;
    position[1] = y;
}

bishop::~bishop() {
    possible_moves.clear();
    possible_moves.swap(possible_moves);
}

bool bishop::find_possible_moves(int* board) {
    possible_moves.clear();
    std::string temp_string;
    bool check{false};
    int multiplier;
    int* x_moves;
    x_moves = new int[4]{-1,+1,+1,-1};
    int* y_moves;
    y_moves = new int[4]{+1,+1,-1,-1};
    for (size_t i{0}; i<4; i++) {
        // loops over four directions
        bool keep_going{true};
        multiplier = 1;
        while (keep_going) {
            
            if ((position[0] + multiplier*x_moves[i] < 9) && (position[0] + multiplier*x_moves[i] > 0) && (position[1] + multiplier*y_moves[i] < 9) && (position[1] + multiplier*y_moves[i] > 0)) {
                // values within range
                if (board[convert_index(position[0] + multiplier*x_moves[i], position[1] + multiplier*y_moves[i])] == 0) {
                    temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";

                } else {
                    if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value < 0) { // enemy piece
                        temp_string = std::to_string(position[0] + multiplier * x_moves[i]) + std::to_string(position[1] + multiplier* y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";                             
                        keep_going = false;
                        if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value == -40) {
                            check = true;
                        }
                    } else {
                        // friendly piece
                        // stop without appending
                        keep_going = false;
                    }
                }
                multiplier += 1;
            } else {
                keep_going = false;
            }


        } // end while
        
    }

    delete x_moves;
    delete y_moves;
    return check;
}


bool bishop::find_attack_moves(int* board) {
    possible_moves.clear();
    std::string temp_string;
    bool check{false};
    int multiplier;
    int* x_moves;
    x_moves = new int[4]{-1,+1,+1,-1};
    int* y_moves;
    y_moves = new int[4]{+1,+1,-1,-1};
    for (size_t i{0}; i<4; i++) {
        // loops over four directions
        bool keep_going{true};
        multiplier = 1;
        while (keep_going) {
            
            if ((position[0] + multiplier*x_moves[i] < 9) && (position[0] + multiplier*x_moves[i] > 0) && (position[1] + multiplier*y_moves[i] < 9) && (position[1] + multiplier*y_moves[i] > 0)) {
                // values within range
                if (board[convert_index(position[0] + multiplier*x_moves[i], position[1] + multiplier*y_moves[i])] == 0) {
                    temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";

                } else {
                    if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value < 0) { // enemy piece
                        temp_string = std::to_string(position[0] + multiplier * x_moves[i]) + std::to_string(position[1] + multiplier* y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";                             
                        if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value == -40) {
                            check = true;
                        }
                    } else {
                        // friendly piece
                        // stop without appending
                        keep_going = false;
                    }
                }
                multiplier += 1;
            } else {
                keep_going = false;
            }
        }
    }
    delete x_moves;
    delete y_moves;
    return check;
}

// rook defintions

rook::rook() : piece{} {
    name = "rook";
    point_value = 5;
}

rook::rook(int x, int y, int init_point) : piece{x,y,"rook", init_point} {
    position[0] = x;
    position[1] = y;
}

rook::~rook() {
    possible_moves.clear();
    possible_moves.swap(possible_moves);
}

bool rook::find_possible_moves(int* board) {
    bool check{false};
    possible_moves.clear();
    std::string temp_string;
    int multiplier;
    int* x_moves;
    x_moves = new int[4]{0,+1,0,-1};
    int* y_moves;
    y_moves = new int[4]{+1,0,-1,0};
    for (size_t i{0}; i<4; i++) {
        // loops over four directions
        bool keep_going{true};
        multiplier = 1;
        while (keep_going) {
            if ((position[0] + multiplier*x_moves[i] > 0) && (position[0] + multiplier*x_moves[i] < 9) && (position[1] + multiplier*y_moves[i] > 0) && (position[1] + multiplier*y_moves[i] < 9)) {
                if (board[convert_index(position[0] + multiplier*x_moves[i], position[1] + multiplier*y_moves[i])] == 0) {
                    temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";
                } else {
                    if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value < 0) { // enemy piece
                        temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";                            
                        // stop
                        keep_going = false;
                        if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value == -50) {
                            check = true;
                        }

                    } else {
                        // friendly piece
                        // stop without appending
                        keep_going = false;
                    }
                }
                multiplier += 1;
            } else {
                keep_going = false;
            }
        }
        
    }

    delete x_moves;
    delete y_moves;
    return check;
}

bool rook::find_attack_moves(int* board) {
    bool check{false};
    possible_moves.clear();
    std::string temp_string;
    int multiplier;
    int* x_moves;
    x_moves = new int[4]{0,+1,0,-1};
    int* y_moves;
    y_moves = new int[4]{+1,0,-1,0};

    for (size_t i{0}; i<4; i++) {
        // loops over four directions
        bool keep_going{true};
        multiplier = 1;
        while (keep_going) {
            if ((position[0] + multiplier*x_moves[i] > 0) && (position[0] + multiplier*x_moves[i] < 9) && (position[1] + multiplier*y_moves[i] > 0) && (position[1] + multiplier*y_moves[i] < 9)) {
                if (board[convert_index(position[0] + multiplier*x_moves[i], position[1] + multiplier*y_moves[i])] == 0) {
                    temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";
                } else {
                    if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value < 0) { // enemy piece
                        temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";                            
                        // stop
                        if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value == -50) {
                            check = true;
                        }

                    } else {
                        // friendly piece
                        // stop without appending
                        keep_going = false;
                    }
                }
                multiplier += 1;
            } else {
                keep_going = false;
            }
        }// end while
        
    }

    delete x_moves;
    delete y_moves;
    return check;
                 
}

// queen definitions

queen::queen() : piece{} {
    name = "queen";
    point_value = 9;
}

queen::queen(int x, int y, int init_point) : piece{x,y,"queen", init_point} {
    position[0] = x;
    position[1] = y;
}

queen::~queen() {
    possible_moves.clear();
    possible_moves.swap(possible_moves);
}

bool queen::find_possible_moves(int* board) {
    std::string temp_string;
    possible_moves.clear();
    int multiplier;
    int* x_moves;
    x_moves = new int[8]{0,+1,0,-1,-1,+1,+1,-1};
    int* y_moves;
    y_moves = new int[8]{+1,0,-1,0,+1,+1,-1,-1};
    bool check{false};

    for (size_t i{0}; i<8; i++) {
        // loops over all directions
        bool keep_going{true};
        multiplier = 1;
        while (keep_going) {
            if ((position[0] + multiplier*x_moves[i] > 0) && (position[0] + multiplier*x_moves[i] < 9) && (position[1] + multiplier*y_moves[i] < 9) && (position[1] + multiplier*y_moves[i] > 0)) {
                if (board[convert_index(position[0] + multiplier*x_moves[i], position[1] + multiplier*y_moves[i])] == 0) {
                    temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";

                } else {
                    if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value < 0) { // enemy piece
                        temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";                            
                        keep_going = false;
                        if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])] * point_value == -90) { // check
                            check = true;
                        }
                    } else {
                        // friendly piece
                        // stop without appending
                        keep_going = false;
                    }
                }
                multiplier += 1;
            } else {
                keep_going = false;
            }
        }
        
    }


    delete x_moves;
    delete y_moves;
    return check;
}

bool queen::find_attack_moves(int* board) {
    std::string temp_string;
    possible_moves.clear();
    int multiplier;
    int* x_moves;
    x_moves = new int[8]{0,+1,0,-1,-1,+1,+1,-1};
    int* y_moves;
    y_moves = new int[8]{+1,0,-1,0,+1,+1,-1,-1};
    bool check{false};
    for (size_t i{0}; i<8; i++) {
        bool keep_going{true};
        multiplier = 1;
        while (keep_going) {
            if ((position[0] + multiplier*x_moves[i] > 0) && (position[0] + multiplier*x_moves[i] < 9) && (position[1] + multiplier*y_moves[i] < 9) && (position[1] + multiplier*y_moves[i] > 0)) {
                if (board[convert_index(position[0] + multiplier*x_moves[i], position[1] + multiplier*y_moves[i])] == 0) {
                    temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";

                } else {
                    if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value < 0) { // enemy piece
                        temp_string = std::to_string(position[0] + multiplier*x_moves[i]) + std::to_string(position[1] + multiplier*y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";                            
                        if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])] * point_value == -90) { // check
                            check = true;
                        }

                    } else {
                        // friendly piece
                        // stop without appending
                        keep_going = false;
                    }
                }
                multiplier += 1;
            } else {
                keep_going = false;
            }
        } 
    }
    delete x_moves;
    delete y_moves;
    return check;
}


// king definitions
king::king() : piece {} {
    name = "king";
    point_value = 10;
}

king::king(int x, int y, int init_point) : piece{x,y,"king", init_point} {
    position[0] = x;
    position[1] = y;
}

king::~king() {
    possible_moves.clear();
    possible_moves.swap(possible_moves);
}

bool king::find_possible_moves(int* board) {
    possible_moves.clear();
    bool check{false};
    std::string temp_string;
    int* x_moves;
    x_moves = new int[8]{0,+1,0,-1,-1,+1,+1,-1};
    int* y_moves;
    y_moves = new int[8]{+1,0,-1,0,+1,+1,-1,-1};

    for (size_t i{0}; i<8; i++) {
        if ((position[1] + y_moves[i] > 0 && position[1] + y_moves[i] < 9)&&(position[0] + x_moves[i] > 0 && position[0] + x_moves[i] < 9)) {
            if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])] == 0) {
                temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                possible_moves.push_back(temp_string);
                temp_string = "";

            } else {
                if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])]* point_value < 0) { // enemy piece
                    temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";
                    // check if it's a check
                    if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])] * point_value == -100) {
                        check = true;
                    }
                }
            }
        }
    }
    delete x_moves;
    delete y_moves;
    return check;
}


