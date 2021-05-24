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
        load_game(true);
    } else {
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
        pieces_array.clear();
        pieces_array.swap(pieces_array);

    }

int board::sum_board() {
    int sum{0};
    for (size_t i{0}; i<65; i++) {
        sum += board_rep[i];
    }
    return sum;
}

void board::load_game(bool default_mode) {
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
    for (int j{1}; j<=8; j++) {
        for (int i{1}; i<=8;i++) { 
            if (board_rep[convert_index(i,j)] == 1 || board_rep[convert_index(i,j)] == -1) {
                // pawn 
                pawn_memory[counters[0]] = pawn{i,j,board_rep[convert_index(i,j)]}; // assigns memory for objects
                pieces_array.push_back(&pawn_memory[counters[0]]); // push pointer
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

void board::save_game() { // works
    std::cout << "saving game" << std::endl;
    std::remove("last_game.txt"); 
    std::ofstream file("last_game.txt");
    for (size_t j{1}; j<=8; j++) {
        for (size_t i{1}; i<=8;i++) {
            file << board_rep[convert_index(i,j)] << std::endl;
        }
    }
    file.close();
}

void board::pvp() {
    int i{1};
    //white player starts
    int player{1};
    while (mate == false) {
        std::cout << "The turn no." << i << " starts!" << std::endl;
        if (player == 1) {
            std::cout << "White has the move now." << std::endl;
            std::cout << "To continue press any key. To quit and save type x" << std::endl;
            std::string choice;
            std::cin >> choice;
            if (choice == "x") {
                save_game();
                check = true;
                mate = true;
            }
        } else {
            std::cout << "Black has the move now." << std::endl; 
        }
        play_turn(player);
        player = player*-1;
        i++;
    }
    std::cout << "Game over." << std::endl;
    if (player == 1) {
        std::cout << "White wins!" << std::endl;
    } else {
        std::cout << "Black wins!" << std::endl;
    } 
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
        return capitalize_string(piece);
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
                    all_moves.clear();
                    all_moves.swap(all_moves);
                    return true;
                }
            }
        }
    }
    all_moves.clear();
    all_moves.swap(all_moves);
    return false;
}

std::vector<std::string> board::alter_king_moves(int player, int king_index) {
    std::vector<std::string> king_moves = pieces_array[king_index]->list_moves();
    std::vector<std::string> all_moves;
    for (size_t i{0}; i<pieces_array.size(); i++) {
        // check if the piece was removed
        if (pieces_array[i]->get_point()*player < 0) { // find only moves for enemy pieces
            if (pieces_array[i]->is_removed() == false) {
                // list moves but with special function to find squares which do check the king
                if ((pieces_array[i]->get_name() == "king") || (pieces_array[i]->get_name() == "knight")) {
                    pieces_array[i]->find_possible_moves(board_rep);
                } else { 
                    pieces_array[i]->find_attack_moves(board_rep);
                }
            }
            all_moves = pieces_array[i]->list_moves();

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
    pieces_array[king_index]->set_possible_moves(new_moves);
    king_moves.clear();
    king_moves.swap(king_moves);
    all_moves.clear();
    all_moves.swap(all_moves);
    return new_moves;
}

bool board::can_king_move(int player) {
    int king_index = find_king_index(player);
    std::vector<std::string> new_moves = alter_king_moves(player, king_index);
    if (new_moves.size() == 0) {
        // king can't move
        new_moves.swap(new_moves);
        return true; // mate
    } else {
        pieces_array[king_index]->set_possible_moves(new_moves);
        new_moves.clear();
        new_moves.swap(new_moves);
        // override the king moves
        return false; // can still do something
    }
}

void board::find_all_moves(int player) {
    // +1 if white, -1 if black;
    std::vector<std::string> player_moves;
    for (size_t i{0}; i<pieces_array.size(); i++) {
        if (pieces_array[i]->is_removed() == false) {
            pieces_array[i]->find_possible_moves(board_rep);
        }
    }
    alter_king_moves(player,find_king_index(player));
    player_moves.clear();
    player_moves.swap(player_moves);
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
                return i;
            } 
        }
        std::cout << "Enter the position of the piece (in form ex. A1): ";
        std::cin >> choice;
    }
    return -1;
}

int board::find_king_index(int player) {
    for (size_t i{0}; i<pieces_array.size(); i++) {
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
    if (check) {
        std::cout << "Check!" << std::endl;
        mate = can_king_move(player);
        if (mate) {
            std::cout << "And Mate!" << std::endl;
            return; // game is over
        }
    }

    //// get player choice for move
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

    possible_moves.clear();
    possible_moves.swap(possible_moves);
    piece_location.clear();
    piece_location.swap(piece_location);
    // deallocate memory
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
    if (current_piece->get_name() == "pawn") {
        current_piece->piece_moved();
    }
    move.clear();
    move.swap(move);
}

// *************************** AI functions *********************************
int board::do_trial_move(int piece_index,std::string move) {
    // the AI minimizes the move as it's playing black.
    int score{0};
    std::vector<int> move_arr = decode_chess_notation(move);
    piece* current_piece = pieces_array[piece_index];
    int* pos_point = current_piece->get_pos_point();
    int back_up{board_rep[convert_index(move[0], move[1])]};
    
    if (back_up*back_up >= 100) {
        return 1000; // the move is against the king so can't be done.
    }
    board_rep[convert_index(move[0], move[1])] = board_rep[convert_index(pos_point[0], pos_point[1])];
    board_rep[convert_index(pos_point[0], pos_point[1])] = 0;
    score = sum_board();
    // revert to old board rep
    board_rep[convert_index(pos_point[0], pos_point[1])] = board_rep[convert_index(move[0], move[1])];
    board_rep[convert_index(move[0], move[1])] = back_up;

    move.clear();
    move.swap(move);
    return score;
}

void board::play_AI_turn(int player, bool check) {
    std::string ai_move;
    std::vector<std::string> possible_moves;
    find_all_moves(player);
    
    int score;
    int piece_index;
    piece* current_piece;
    std::vector<std::string> temp_array;
    check = is_king_safe(player);
    bool first{true};
    if (check) { // compose the moves allowed
        // move king
        mate = can_king_move(player);
        if (mate) {
            return;
        } else { // only include the king moves to get out of check
            int king_index = find_king_index(player);
            possible_moves = pieces_array[king_index]->list_moves();
            // select the first move that gets the king out of trouble
            ai_move = convert_chess_notation(possible_moves[0][0],possible_moves[0][1]);
            piece_index = king_index;
        }
    } else {
        for (size_t i{0}; i<pieces_array.size(); i++) {
            current_piece = pieces_array[i];
            // for each piece
            if ((current_piece->get_point()*player > 0) && (current_piece->is_removed() == false) && (current_piece->list_moves().size() > 0)) {
                if (first) {
                    ai_move = convert_chess_notation(current_piece->list_moves()[0][0],current_piece->list_moves()[0][1]);
                    score = do_trial_move(i,ai_move);
                    first = false;
                    piece_index = i;
                } // assign an initial move for comparison
                optimise_move(i, &score, &ai_move, &piece_index);
            } 
        }
    }
    std::cout << "The chosen AI move: " << ai_move << std::endl;
    move_piece(piece_index, ai_move); // do the chosen move
    temp_array.clear();
    temp_array.swap(temp_array);
}

void board::optimise_move(int piece_index, int* score, std::string* ai_move, int* best_piece) {
    // take it one piece at the time
    // optimises the moves for this piece
    std::string best_move;
    int sum;
    
    piece* current_piece = pieces_array[piece_index];
    std::vector<std::string> all_moves = current_piece->list_moves();
    for (size_t i{0}; i<all_moves.size(); i++) {
        sum = do_trial_move(piece_index,all_moves[i]);
        if (sum < *score) {
            // better move found
            *ai_move = convert_chess_notation(all_moves[i][0], all_moves[i][1]);
            *score = sum;
            *best_piece = piece_index;
        }
    }
    all_moves.clear();
    all_moves.swap(all_moves);
} 


void board::pve() {
    int i{1};
    //white player starts - human
    int player{1};
    while (mate == false) {
        std::cout << "The turn no." << i << " starts!" << std::endl;
        if (player == 1) {
            std::cout << "White has the move now. Go ahead human" << std::endl;
            std::cout << "To continue press any key. To quit and save type x" << std::endl;
            std::string choice;
            std::cin >> choice;
            if (choice == "x") {
                save_game();
                check = true;
                mate = true;
            }
            play_turn(player);
        } else {
            std::cout << "Black has the move now. My turn now." << std::endl;
            play_AI_turn(player, check);
        }

        player = player*-1;
        i++;
    }
    std::cout << "Game over." << std::endl;
    if (player == 1) {
        std::cout << "White wins! Shame." << std::endl;
    } else {
        std::cout << "Black wins! Duh." << std::endl; // insult for good measure
    } 
}
