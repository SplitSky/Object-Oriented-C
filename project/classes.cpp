// this file contains classes
#include<string>
#include<vector>
#include<map>
//
// copy and move constructors only used for the board class
//
class piece {
    protected:
        // protected variables
        int position[2]; // array of two numbers. First is letter second is number i.e. [1,1] is A1
        std::string name; // e.g. pawn
        int point_value; // the colour depends on the sign of the point value. black is positive
        std::vector<int> possible_moves;

    public:
        piece() {
            position[0] = 1;
            position[1] = 1;
            name = "empty";
            point_value = 0;
        };
        piece(int init_position, std::string init_name, bool init_colour) : position{init_position}, name{init_name} {};
        virtual ~piece() {};

        std::string get_pos() {
            return std::to_string(this->position[0]) + "," + std::to_string(this->position[1]);
        }
};

class pawn : public piece {
    protected:
        // protected variables
        bool not_moved{true};
    public:
        pawn() :piece{} {
            name = "pawn";
            point_value = 1;
        };
        pawn(int init_position, std::string init_name, bool init_colour) : piece{init_position,"pawn", init_colour} {}
        virtual ~pawn() {};

        void find_possible_moves(int* board) {
            // cross reference the board with the current position
            possible_moves = {}; // reset the number of moves
            if (board[(position[0] - 1) + (position[1] - 1)*8 ] == 0) {
                // empty space for pawn
                possible_moves 
            }

        }
        
};

class knight : public piece {
    protected:
        // protected variables
    public:
        knight() :piece{} {
            name = "knight";
            point_value = 3;
        }
        knight(int init_position, std::string init_name, bool init_colour) : piece{init_position,"knight", init_colour} {}
        virtual ~knight() {};
};

class bishop : public piece {
    protected:
        // protected variables
    public:
        bishop() : piece{} {
            name = "bishop";
            point_value = 3;
        }
};

class rook : public piece {
    protected:
        // protected variables
    public:
        rook() : piece{} {
            name = "rook";
            point_value = 5;
        }
};

class queen : public piece {
    protected:
        // protected variables
    public:
        queen() : piece{} {
            name = "queen";
            point_value = 9;
        }
};

class king : public piece {
    protected:
        // protected variables
    public:
        king() : piece {} {
            name = "king";
            point_value = 10;
        }
};

class board {
    // copy and move operators

    // The pieces array contains all the pieces used.
    // The board contains the references to the point values and the position of the pieces.
    // The board construction allows for the calculation of the score of the board easily
    // the pieces pointers get the position modified and stores the actual position
    // when a piece moves update the actual position and then update the integer array
    private:
        std::map<int, std::string> position_map = {{1,"A",},{2,"B",},{3,"C",},{4,"D",},{5,"E",},{6,"F",},{7,"G",},{8,"H",}};
        int standard_game[64] = {+5,+3,+4,+9,+10,+4,+3,+5,+1,+1,+1,+1,+1,+1,+1,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-5,-3,-4,-10,-9,-4,-3,-5};
        piece *pieces_array[32];
        int *board_rep = new int[64]; // dynamically assign an integer array for board representation
        // int board[64]; // the index is col*(j-1) + (i-1)
    public:
        board() = default;
        board(bool default_board) {
            if (default_board == true) {
                // load in the initial file
            } else {
                // load in a different name
                // file name validation
                // read in the game file
            }
        } /// bookmark

        int sum_board() {
            int sum{0};
            for (size_t i{0}; i<65; i++) {
                sum += board_rep[i];
            }
            return sum;
        }
        
};
