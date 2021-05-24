#ifndef BOARD_CLASS_H
#define BOARD_CLASS_H
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#include<algorithm>
#include "functions.h"
#include "classes.h"

class board {
    private:
        std::map<int, std::string> position_map = {{1,"A",},{2,"B",},{3,"C",},{4,"D",},{5,"E",},{6,"F",},{7,"G",},{8,"H",}};
        int standard_game[64] = {+5,+3,+4,+9,+10,+4,+3,+5,+1,+1,+1,+1,+1,+1,+1,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-5,-3,-4,-10,-9,-4,-3,-5};
        int *board_rep = new int[64];  // dynamically assign an integer array for board representation
        std::vector<piece*> pieces_array;
        bool check{false};
        bool mate{false};
        pawn *pawn_memory = new pawn[16];
        king *king_memory = new king[2];
        queen *queen_memory = new queen[2];
        knight *knight_memory = new knight[4];
        rook *rook_memory = new rook[4];
        bishop *bishop_memory = new bishop[4];

    public:
        board();
        board(bool default_board);
        ~board();
        int sum_board(); 
        void load_game(bool default_mode); 
        void print_data();
        void save_game();
        std::vector<std::string> list_moves();
        void PvP();
        void LoadGame();
        void print_board();
        std::string get_piece_name(int n);
        void printLine(int y);
        bool is_king_safe(int player);
        std::vector<std::string> alter_king_moves(int player, int king_index);
        bool can_king_move(int player);
        void find_all_moves(int player);
        int get_choice(int player);
        int find_king_index(int player);
        piece* return_piece(int x, int y);
        void play_turn(int player);
        void move_piece(int piece_index, std::string new_pos);

        void play_AI_turn(int player, bool check);
        int do_trial_move(int piece_index, std::string move);
        void PvE();
        void optimise_move(int piece_index, int* score, std::string* ai_move, int* best_piece);

};
#endif
