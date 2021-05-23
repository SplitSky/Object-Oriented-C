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
        std::cout << "loading the game - constructor" << std::endl;
        //print_data();
    } else {
        // load in a different name
        // read in the game file
        load_game(false);
    }
}
board::~board() {
        delete[] board_rep;
        //delete[] pieces_array;
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
        // std::cout << "No such file!" << std::endl;
    } else {
        // std::cout << "File present!" << std::endl;
        for (size_t i{0}; i<64; i++) {
            line = "";
            getline(my_file, line);
            board_rep[i] = std::stoi(line);
        }
        my_file.close();
    }
    // decode and create objects
    int piece_count{0};
    for (int j{1}; j<=8; j++) {
        for (int i{1}; i<=8;i++) { 

            if (board_rep[convert_index(i,j)] == 1 || board_rep[convert_index(i,j)] == -1) {
                // pawn
                piece_count++;
                pieces_array.push_back(pawn{i,j,board_rep[convert_index(i,j)]});
            } else if (board_rep[convert_index(i,j)] == 3 || board_rep[convert_index(i,j)] == -3) {
                // knight
                piece_count++;
                pieces_array.push_back(knight{i,j,board_rep[convert_index(i,j)]});
            } else if (board_rep[convert_index(i,j)] == 4 || board_rep[convert_index(i,j)] == -4) {
                // bishop
                piece_count++;
                pieces_array.push_back(bishop{i,j,board_rep[convert_index(i,j)]}); 
            } else if (board_rep[convert_index(i,j)] == 5 || board_rep[convert_index(i,j)] == -5) {
                // rook
                piece_count++;
                pieces_array.push_back(rook{i,j,board_rep[convert_index(i,j)]}); 
            } else if (board_rep[convert_index(i,j)] == 10 || board_rep[convert_index(i,j)] == -10) {
                // king
                piece_count++;
                pieces_array.push_back(king{i,j,board_rep[convert_index(i,j)]});
            } else if (board_rep[convert_index(i,j)] == 9 || board_rep[convert_index(i,j)] == -9) {
                // queen
                piece_count++;
                pieces_array.push_back(queen{i,j,board_rep[convert_index(i,j)]});
            }
        }
    }
}

void board::print_data() {
    for (size_t i{0}; i<64; i++) {
        std::cout << "the variable entry" << board_rep[i] << ", ";
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
            std::cout << "iteration" << std::endl;
            std::cout << "The index saved: " << board_rep[convert_index(i,j)] << std::endl;
            file << board_rep[convert_index(i,j)] << std::endl;
        }
    }
    file.close();
}


std::vector<std::string> board::list_moves() { // list all moves without check monitoring
    // loop through all objects and list moves
    std::cout << "Listing possible moves: " << std::endl;
    std::string temp_name;
    std::vector<std::string> moves;
    std::vector<std::string> temp_moves;
    for (size_t i{0}; i<32; i++) {
        // check if empty
        if (pieces_array[i].is_removed() == false) { 
            pieces_array[i].find_possible_moves(board_rep);
             
            std::cout << "moves for ";
            std::cout << pieces_array[i].get_name();
            std::cout << " positioned at : " << pieces_array[i].get_pos();

            temp_moves = pieces_array[i].list_moves();
            for (size_t j{0}; j < temp_moves.size() ; j++) {
                moves.push_back(temp_moves[j]); // iterate over the individual moves
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
    //while (mate == false) {
    std::cout << "The turn no." << i << " starts!" << std::endl;
    play_turn(player);
    player = player*-1;
    //}

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
        for (size_t i{8}; i != 0; i--) {
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

bool board::is_king_safe(int player, int king_index) {
    bool safe{true};
    pieces_array[king_index].find_possible_moves(board_rep);
    std::string position = pieces_array[king_index].get_pos();
    std::vector<std::string> all_moves;
    std::vector<std::string> king_moves = pieces_array[king_index].list_moves();
    // get array of enemy attack moves;
    for (size_t i{0}; i<32; i++) {
        // check if the piece was removed
        if (pieces_array[king_index].get_point()*player < 0) { // find only moves for enemy pieces
            if (pieces_array[i].is_removed() == false) {
                // list moves but with special function for pawns
                if (pieces_array[i].get_name() == "pawn") {
                    pieces_array[i].find_attack_moves(board_rep);
                } else { 
                    pieces_array[i].find_possible_moves(board_rep);
                }
            }
            // append all lists together
            all_moves = pieces_array[i].list_moves();
            for (size_t j{0}; j<all_moves.size(); j++) {
                for (size_t k{0}; k<king_moves.size(); k++) {
                    if (king_moves[k] == all_moves[j]) {
                        return false;
                    }
                }  
            }

        }
    }
    return true;
}

bool board::can_king_move(int player, int king_index) {
    pieces_array[king_index].find_possible_moves(board_rep);
    std::string position = pieces_array[king_index].get_pos();
    std::vector<std::string> all_moves;
    std::vector<std::string> king_moves = pieces_array[king_index].list_moves();
    // get array of enemy attack moves;
    for (size_t i{0}; i<32; i++) {
        // check if the piece was removed
        if (pieces_array[king_index].get_point()*player < 0) { // find only moves for enemy pieces
            if (pieces_array[i].is_removed() == false) {
                // list moves but with special function for pawns
                if (pieces_array[i].get_name() == "pawn") {
                    pieces_array[i].find_attack_moves(board_rep);
                } else { 
                    pieces_array[i].find_possible_moves(board_rep);
                }
            }
            // append all lists together
            all_moves = pieces_array[i].list_moves();
            for (size_t j{0}; j<all_moves.size(); j++) {
                for (size_t k{0}; k<king_moves.size(); k++) {
                    if (king_moves[k] == all_moves[j]) {
                        king_moves[k] = "forbidden"; 
                    }
                }  
            }

        }
    }
    all_moves.clear();
    // check what moves are available to the king
    for (size_t i{0}; i<king_moves.size(); i++) {
        if (king_moves[i] != "forbidden") {
            all_moves.push_back(king_moves[i]);
        }
    }

    pieces_array[king_index].set_possible_moves(all_moves); // overwrite the possible moves after check verification
    
    if (all_moves.size() == 0) {
        return false; // check mate
    } else {
        return true; // just check
    }

}           


void board::find_all_moves(int player) {
    // +1 if white, -1 if black;
    piece* temp_piece; 
    std::vector<std::string> player_moves;
    for (size_t i{0}; i<32; i++) { // loops through the pieces 
        temp_piece = &pieces_array[i];
        std::cout << "The point value for piece is: " << temp_piece->get_name();
        if (pieces_array[i].get_point()*player > 0) { // this check makes sure the pieces for which moves we find belong to the player
            pieces_array[i].find_possible_moves(board_rep);
        }   
    }
}

int board::get_choice() {
    bool valid = false;
    std::string choice;
    std::cout << "Enter the position of the piece (in form ex. A1): ";
    std::cin >> choice;

    while (valid == false) {
        for (size_t i{0}; i<32; i++) {
            std::string temp_string = pieces_array[i].get_pos();
            std::cout << "the position: " << temp_string << " and individual: " << temp_string[0] << temp_string[1] << temp_string[2] << std::endl;
            temp_string = convert_chess_notation(temp_string[0], temp_string[2]);
            std::cout << "The converted: " << temp_string << " The choice: " << choice << std::endl;
            if (choice == temp_string) {
                return i;
            } 
        }
        std::cout << "Enter the position of the piece (in form ex. A1): ";
        std::cin >> choice;
    }
    return -1;
}

int board::find_king_index(int player) {
    // w>0 ; b<0
    for (size_t i{0}; i<32; i++) { // loop through pieces array
        if (pieces_array[i].get_name() == "king") {
            if (pieces_array[i].get_point()*player > 0) {
                return i;
            }
        }
    }
    return 0;
}


piece* board::return_piece(int x, int y) {
    int* array_temp;
    piece* current_object;
    for (size_t i{0}; i<32; i++) {
        current_object = &pieces_array[i]; /// this is absolute wrong
        array_temp = current_object->get_pos_point(); 
        if (array_temp[0] == x && array_temp[1] == y){
            // position matches
            return current_object;
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
    // list all possible moves
    // check if moves causes friendly check
    // remove the ones that do
    // check if king is under check
    // if yes check if it has moves
    // if no finish game
    // get move from player
    // move the piece
    // remove piece if necessary
    // check if the enemy king is under check
    find_all_moves(player); // generates possible moves

    int king_index = find_king_index(player);
    check = is_king_safe(player, king_index);
    mate = can_king_move(player, king_index); // also overrides the king moves based on the check conditions.

    // get choice for move
    indicator = get_choice();
    while (indicator == -1) {
        std::cout << "The input is incorrect. Try again";
        indicator = get_choice();
    }
    piece* current_piece = &pieces_array[indicator];
    // display moves for the piece selected:
    possible_moves = current_piece->list_moves();
    std::cout << "The moves for " << current_piece->get_name() << " are: " << std::endl;
    for (size_t i{0}; i<possible_moves.size();i++) {
        std::cout << possible_moves[i] << ", ";
    }
    std::cout << std::endl;

    
    // pick where to move it
    std::cout << "Where do you want to move it?" << std::endl;
    bool valid{false};
    std::string choice;
    while (valid == false) {
        std::cout << "Input your choice: ";
        std::cin >> choice;
        // check if the choice is an allowed move
        for (size_t i{0}; i<possible_moves.size(); i++) {
            if (choice == possible_moves[i]) {
                valid = true;
            }
        }
        if (valid == false) { std::cout << "Incorrect move. Try again" << std::endl; }

    }
    // move the piece
    // 1. check the piece you are moving to
    // 2. If piece then remove it if empty continue
    // 3. change the board representation a. erase b. add
    
    //std::vector<int> new_position = decode_chess_notation(choice);
    //int* old_pos = current_piece->get_pos_point();
    //piece* temp_piece = return_piece(new_position[0], new_position[1]);
    //if (current_piece->get_point()*board_rep[convert_index(new_position[0], new_position[1])] < 0) { // if the new location is taken by enemy piece
        // remove the piece from board_rep
    //    temp_piece->remove();       
    //}
    //board_rep[convert_index(new_position[0], new_position[1])] = board_rep[convert_index(old_pos[0], old_pos[1])]; // override the board
    //std::cout << "The piece moved" << std::endl; 
}



