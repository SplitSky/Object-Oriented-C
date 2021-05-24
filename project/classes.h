// this file contains the definitions of the functions for the piece classes
#ifndef CLASSES_H
#define CLASSES_H
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#include<algorithm>
#include "functions.h"

class piece {
    public:
        int position[2]; // array of two numbers. First is letter second is number i.e. [1,1] is A1
        std::string name; // e.g. pawn
        int point_value; // the colour depends on the sign of the point value. while is positive
        std::vector<std::string> possible_moves;
        bool removed;
        bool moved{false};
        piece();
        piece(int x, int y, std::string init_name, int init_point);
        virtual ~piece();

        std::string get_pos(); 
        void set_pos(int x, int y);
        int* get_pos_point(); 
        virtual bool find_possible_moves(int* board);
        std::vector<std::string> list_moves(); 

        std::string get_name();
        bool is_removed();
        int get_point();

        virtual bool find_attack_moves(int* board);
        void set_possible_moves(std::vector<std::string> moves);
        void remove();
        void piece_moved();
};

class pawn : public piece {
    protected:
        // protected variables
        bool not_moved{true};
        //std::vector<std::string> possible_moves;
        bool ascend{false};
        std::vector<std::string> danger_moves;
    public:
        pawn();
        pawn(int x, int y, int init_point);
        virtual ~pawn();
        virtual bool find_possible_moves(int* board); 
        bool find_attack_moves(int* board);
};

class knight : public piece {
    public:
        knight();
        knight(int x, int y, int init_point); 
        virtual ~knight();
        bool find_possible_moves(int* board);
};

class bishop : public piece { 
    public:
        bishop();
        bishop(int x, int y, int init_point);
        ~bishop();
        bool find_possible_moves(int* board);
        bool find_attack_moves(int* board);
};

class rook : public piece {   
    public:
        rook();
        rook(int x, int y, int init_point);
        ~rook();
        bool find_possible_moves(int* board);
        bool find_attack_moves(int* board);
};

class queen : public piece {
public:
    queen();
    queen(int x, int y, int init_point);
    ~queen();
    bool find_possible_moves(int* board);
    bool find_attack_moves(int* board);
};

class king : public piece { // one in each direction
    protected:
        bool safe{true};
    public:
        king();
        king(int x, int y, int init_point);
        ~king();
        bool find_possible_moves(int* board);
};
#endif
