#include <cstring>
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#include<algorithm>
#include "functions.h"
#include "classes.h"
#include "board_class.h"

board::board() = default;
board::board(bool default_board) {
    if (default_board == true) {
        // load in the initial file
        load_game(true);
        //print_data();
    } else {
        // load in a different name
        // read in the game file
        load_game(false);
    }
}
board::~board() {
        delete[] board_rep;
        delete[] pawn_memory;
        delete[] knight_memory;
        delete[] rook_memory;
        delete[] queen_memory;
        delete[] king_memory;
    }

int board::sum_board() {
    int sum{0};
    for (size_t i{0}; i<65; i++) {
        sum += board_rep[i];
    }
    return sum;
}

// initialization function
void board::start_game() {
    // print introduction screen
    // select gamemode
    // 1. player vs player
    // 2. player vs AI
    // 3. load game
    //
    std::cout << "Welcome! What would you like to do?:" << std::endl;
    std::cout << "1. Player vs Player" << std::endl;
    std::cout << "2. Player vs AI" << std::endl;
    std::string choice;
    std::cin >> choice;
}


void board::load_game(bool default_mode) { // works
    //std::vector<int> board_2;
    std::string line;
    // loads the default board set up from a file
    std::fstream my_file;

    if (default_mode) {
        my_file.open("default.txt", std::ios::in);
    } else {
        my_file.open("last_game.txt", std::ios::in);
    }
    if (!my_file) {
        std::cout << "No such file!" << std::endl;
    } else {
        std::cout << "File present!" << std::endl;
        for (size_t i{0}; i<64; i++) {
            line = "";
            getline(my_file, line);
            board_rep[i] = std::stoi(line);
        }
        my_file.close();
    }
    // decode and create objects
    int* counters = new int[6];
    for (size_t i{0}; i<6; i++) {counters[i] = 0;} // fill it with zeroes
    // pawn, knight, bishop, king, queen
    for (int j{1}; j<=8; j++) {
        for (int i{1}; i<=8;i++) { 

            if (board_rep[convert_index(i,j)] == 1 || board_rep[convert_index(i,j)] == -1) { // experimental pawn loading
                // pawn 
                pawn_memory[counters[0]] = pawn{i,j,board_rep[convert_index(i,j)]}; // assigns memory for objects
                pieces_array.push_back(&pawn_memory[counters[0]]);
                counters[0]++;

            } else if (board_rep[convert_index(i,j)] == 3 || board_rep[convert_index(i,j)] == -3) {
                // knight

                knight_memory[counters[1]] = knight{i,j,board_rep[convert_index(i,j)]};
                pieces_array.push_back(&knight_memory[counters[1]]);
                counters[1]++;

            } else if (board_rep[convert_index(i,j)] == 4 || board_rep[convert_index(i,j)] == -4) {
                // bishop
                
                bishop_memory[counters[2]] = bishop{i,j,board_rep[convert_index(i,j)]};
                pieces_array.push_back(&bishop_memory[counters[2]]);
                counters[2]++;

            } else if (board_rep[convert_index(i,j)] == 5 || board_rep[convert_index(i,j)] == -5) {
                // rook
                rook_memory[counters[3]] = rook{i,j,board_rep[convert_index(i,j)]};
                pieces_array.push_back(&rook_memory[counters[3]]);
                counters[3]++;

            } else if (board_rep[convert_index(i,j)] == 10 || board_rep[convert_index(i,j)] == -10) {
                // king
                king_memory[counters[4]] = king{i,j,board_rep[convert_index(i,j)]};
                pieces_array.push_back(&king_memory[counters[4]]);
                counters[4]++;

            } else if (board_rep[convert_index(i,j)] == 9 || board_rep[convert_index(i,j)] == -9) {
                // queen
                queen_memory[counters[5]] = queen{i,j,board_rep[convert_index(i,j)]};
                pieces_array.push_back(&queen_memory[counters[5]]);
                counters[5]++;
            }
        }
    }
    delete[] counters;
}

void board::print_data() {
    for (size_t i{0}; i<64; i++) {
        std::cout << board_rep[i] << ", ";
    }
    std::cout << std::endl;
}

void board::save_game() { // works
    std::cout << "saving game" << std::endl;
    // delete old file
    std::remove("last_game.txt"); 
    std::ofstream file("last_game.txt");
    for (size_t j{1}; j<=8; j++) {
        for (size_t i{1}; i<=8;i++) {
            file << board_rep[convert_index(i,j)] << std::endl;
        }
    }
    file.close();
}


std::vector<std::string> board::list_moves() {
    std::cout << "Listing possible moves: " << std::endl;
    std::string temp_name;
    std::vector<std::string> moves;
    std::vector<std::string> temp_moves;
    for (size_t i{0}; i<pieces_array.size(); i++) {
        // check if empty
        if (pieces_array[i]->is_removed() == false) { 
            pieces_array[i]->find_possible_moves(board_rep);
             
            std::cout << "moves for ";
            std::cout << pieces_array[i]->get_name();
            std::cout << " positioned at : " << convert_chess_notation(pieces_array[i]->get_pos()[0],pieces_array[i]->get_pos()[2]);
            temp_moves = pieces_array[i]->list_moves();
            for (size_t j{0}; j < temp_moves.size() ; j++) {
                moves.push_back(temp_moves[j]);
            }
        }
    }
    return moves;
}

void board::PvP() {
    // player vs player game
    // 1. load the initial set up. Player 1 is white. Player 2 is black.
    // 2. Play game
    // 3. Type "X" if you want to quit.
    // 4. Type "XS" if you want to quit and save the game
    int i{1};
    //white player starts
    int player{1};
    while (mate == false) {
        std::cout << "The turn no." << i << " starts!" << std::endl;
        if (player == 1) {
            std::cout << "White has the move now." << std::endl;
        } else {
            std::cout << "Black has the move now." << std::endl; 
        }
        play_turn(player);
        player = player*-1;
        i++;
    }
}

void board::PvAI() {
    // player vs AI
    // 1. load the initial set up. Player colour is random. AI takes the other one.
    // 2. Play the game
    // 3. Type "X" if you want to quit.
    // 4. Type "XS" if you want to quit and save the game 
}

void board::LoadGame() {
    // Select the game type
    // 1. Load the game
    // 2. Resume the PvAI game
}

void board::print_board() {
    std::cout << "   | A | B | C | D | E | F | G | H | " << std::endl;
    std::cout << "##########################################" << std::endl;
        for (size_t i{1}; i <=8; i++) {
            // Line starting with BLACK
            printLine(i);
        }
    std::cout << "##########################################" << std::endl;
}

std::string board::get_piece_name(int n) {
    int temp_n = n;
    if (temp_n < 0) {
        temp_n = temp_n*-1;
    }
    std::string piece;
    if (temp_n == 0) {
        return " ";
    } else {
        if (temp_n == 1 || temp_n == -1 ) {
            // pawn
            piece = "p";
        } else if (temp_n == 3 || temp_n == -3) {
            // knight
            piece = "n";
        } else if (temp_n == 4 || temp_n == -4) {
            // bishop
            piece = "b";
        } else if (temp_n == 5 || temp_n == -5) {
            // rook
            piece = "r";
        } else if (temp_n == 10 || temp_n == -10) {
            // king
            piece = "k";
        } else if (temp_n == 9 || temp_n == -9) {
            // queen
            piece = "q";
        }
    }
    if (n < 0) {
        return capitalizeString(piece);
    }
    return piece;
}

void board::printLine(int y) {
    for (size_t i{0}; i<9; i++) {
        for (size_t j{0}; j<3; j++) {std::cout << " ";}
        std::cout << "|";
    }
    std::cout<<std::endl;
    std::cout << " " << y << " |";
    for (size_t i{1}; i<=8; i++) { 
        std::cout << " " << get_piece_name(board_rep[convert_index(i,y)]) << " ";
        std::cout << "|";
    }
    std::cout << std::endl;

    for (size_t i{0}; i<9; i++) {
        for (size_t j{0}; j<3; j++) {std::cout << " ";}
        std::cout << "|";
    }
    std::cout<<std::endl;
    std::cout << "----------------------------------------" << std::endl;

}

bool board::is_king_safe(int player) { 
    // this function returns the negative of king's safety
    int king_index = find_king_index(player);
    pieces_array[king_index]->find_possible_moves(board_rep);
    std::string position = convert_chess_notation(pieces_array[king_index]->get_pos()[0], pieces_array[king_index]->get_pos()[2]);
    std::vector<std::string> all_moves;
    for (size_t i{0}; i<pieces_array.size(); i++) {
        if (pieces_array[i]->get_point()*player < 0) { // find only moves for enemy pieces
            if (pieces_array[i]->is_removed() == false) {
                if (pieces_array[i]->get_name() == "pawn") {
                    pieces_array[i]->find_attack_moves(board_rep);
                } else { 
                    pieces_array[i]->find_possible_moves(board_rep);
                }
            }
            all_moves = pieces_array[i]->list_moves();
            for (size_t j{0}; j<all_moves.size(); j++) {
                if (position == convert_chess_notation(all_moves[j][0],all_moves[j][1])) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool board::can_king_move(int player) {
    int king_index = find_king_index(player);
    std::vector<std::string> king_moves = pieces_array[king_index]->list_moves();
    
    std::vector<std::string> all_moves;
    for (size_t i{0}; i<pieces_array.size(); i++) {
        // check if the piece was removed
        if (pieces_array[i]->get_point()*player < 0) { // find only moves for enemy pieces
            if (pieces_array[i]->is_removed() == false) {
                // list moves but with special function to find hot squares
                if ((pieces_array[i]->get_name() == "king") || (pieces_array[i]->get_name() == "knight")) {
                    pieces_array[i]->find_possible_moves(board_rep);
                } else { 
                    pieces_array[i]->find_attack_moves(board_rep);
                }
            }
            all_moves = pieces_array[i]->list_moves();
            // loop through all moves
            for (size_t j{0}; j<all_moves.size(); j++) {
                for (size_t k{0}; k<king_moves.size(); k++) {
                    std::string current_move = convert_chess_notation(king_moves[k][0], king_moves[k][1]);
                    if (current_move == convert_chess_notation(all_moves[j][0], all_moves[j][1])) {
                        king_moves[k] = "forbidden";
                    }
                }
            }
        }
    }

    std::vector<std::string> new_moves;
    for (size_t i{0}; i<king_moves.size(); i++) {
        if (king_moves[i] != "forbidden") {
            new_moves.push_back(king_moves[i]);
        }
    }

    if (new_moves.size() == 0) {
        // king can't move
        return true; // mate
    } else {
        pieces_array[king_index]->set_possible_moves(new_moves);
        // override the king moves
        return false; // can still do something
    }
   
}




void board::find_all_moves(int player) { // adjust it to only allow player's moves
    // +1 if white, -1 if black;
    std::vector<std::string> player_moves;
    for (size_t i{0}; i<pieces_array.size(); i++) { // loops through the pieces
        if (pieces_array[i]->is_removed() == false) {
            pieces_array[i]->find_possible_moves(board_rep);
        }
    }
}

int board::get_choice(int player) {
    bool valid = false;
    std::string choice;
    std::cout << "Enter the position of the piece (in form ex. A1): ";
    std::cin >> choice;
    int point_value;
    size_t moves_list;
    while (valid == false) {
        for (size_t i{0}; i<pieces_array.size(); i++) {
            std::string temp_string = pieces_array[i]->get_pos();
            point_value = pieces_array[i]->get_point(); // get point for comparison
            temp_string = convert_chess_notation(temp_string[0], temp_string[2]);
            moves_list = pieces_array[i]->list_moves().size();

            if ((choice == temp_string) && (point_value*player > 0) && (moves_list > 0) && (pieces_array[i]->is_removed() == false)) { 
                // there is a piece on the square and its friendly and it has moves available and it wasn't removed
                return i; // the piece with an available position was selected
            } 
        }
        std::cout << "Enter the position of the piece (in form ex. A1): ";
        std::cin >> choice;
    }
    return -1;
}

int board::find_king_index(int player) {
    // w>0 ; b<0
    for (size_t i{0}; i<pieces_array.size(); i++) { // loop through pieces array
        if (pieces_array[i]->get_name() == "king") {
            if (pieces_array[i]->get_point()*player > 0) {
                return i;
            }
        }
    }
    return 0;
}


piece* board::return_piece(int x, int y) {
    int* array_temp;
    piece* current_object;
    for (size_t i{0}; i<pieces_array.size(); i++) {
        if (pieces_array[i]->is_removed() == false) {
            current_object = pieces_array[i];
            array_temp = current_object->get_pos_point();
            if ((array_temp[0] == x) && (array_temp[1] == y)) {
                return current_object;
            }
        } 

    }
    return nullptr;
}

void board::play_turn(int player) {
    print_board();
    std::string temp_string;
    int indicator;
    std::vector<std::string> possible_moves;
    std::vector<int> piece_location;
    find_all_moves(player); // generates possible moves
    check = is_king_safe(player);
    if (check) {mate = can_king_move(player);}

    std::cout << "Check status = " << check << std::endl;
    std::cout << "mate status = " << mate << std::endl;

    //// get choice for move
    indicator = get_choice(player);
    while (indicator == -1) {
        std::cout << "The input is incorrect. Try again";
        indicator = get_choice(player);
    }
    piece* current_piece = pieces_array[indicator];
    // display moves for the piece selected:
    possible_moves = current_piece->list_moves();
    std::cout << "The moves for " << current_piece->get_name() << " are: " << std::endl;
    for (size_t i{0}; i<possible_moves.size();i++) {
        std::cout << convert_chess_notation(possible_moves[i][0], possible_moves[i][1]) << ", ";
    }
    std::cout << std::endl;

    
    //// pick where to move it
    std::cout << "Where do you want to move it?" << std::endl;
    bool valid{false};
    std::string choice;
    while (valid == false) {
        std::cout << "Input your choice: ";
        std::cin >> choice;
        // check if the choice is an allowed move
        for (size_t i{0}; i<possible_moves.size(); i++) {
            if (choice == convert_chess_notation(possible_moves[i][0], possible_moves[i][1]) ) {
                valid = true;
            }
        }
        if (valid == false) { std::cout << "Incorrect move. Try again" << std::endl; }

    }
    move_piece(indicator, choice);

}

void board::move_piece(int piece_index, std::string new_pos) {
    std::vector<int> move = decode_chess_notation(new_pos);
    piece* current_piece = pieces_array[piece_index];

    if (board_rep[convert_index(move[0], move[1])] != 0) {
        piece* enemy_piece = return_piece(move[0], move[1]);
        enemy_piece->remove();
    }
    int* pos_point = current_piece->get_pos_point();
    board_rep[convert_index(move[0], move[1])] = board_rep[convert_index(pos_point[0], pos_point[1])]; //override the board
    board_rep[convert_index(pos_point[0], pos_point[1])] = 0; // clear up the old position
    current_piece->set_pos(move[0], move[1]);

}


