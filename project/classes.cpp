// this file contains classes
#include<string>
#include<vector>
#include<map>
//
// copy and move constructors only used for the board class

int convert_index(int x, int y) {
    return (x-1) + 8*(y-1);
}


class piece {
    protected:
        // protected variables
        int position[2]; // array of two numbers. First is letter second is number i.e. [1,1] is A1
        std::string name; // e.g. pawn
        int point_value; // the colour depends on the sign of the point value. black is positive
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
        std::vector<std::string> possible_moves;
        bool ascend{false};
    public:
        pawn() :piece{} {
            name = "pawn";
            point_value = 1;
        };
        pawn(int init_position, std::string init_name, bool init_colour) : piece{init_position,"pawn", init_colour} {if (init_colour) {point_value=1;}}
        virtual ~pawn() {};

        void find_possible_moves(int* board) {
            // cross reference the board with the current position
            possible_moves = {}; // reset the number of moves
            std::string temp_string;
            // the point value is the length of the move in the correct direction
            // if -1 it is black but if it's +1 it's white
            // start if
            
            // position[0] ranges from 0 - 7. +1 for the real value

            if ((position[1]+1 == 8) || (position[1]-1 == -1) ) {
                
                if (board[convert_index(position[0], position[1] + point_value)] == 0) {
                    // the board place is empty
                    temp_string = std::to_string(position[0]) + std::to_string(position[1] + point_value);
                    possible_moves.push_back(temp_string);
                    temp_string = "";
                }

                if ((not_moved == true) &&  (board[convert_index(position[0], position[1] + 2*point_value)] == 0)) {
                    temp_string = std::to_string(position[0]) + std::to_string(position[1] + point_value);
                    possible_moves.push_back(temp_string);
                    temp_string = "";                   
                }

                // check the edge
                if (position[0]+1 != 8) {
                    if (board[convert_index(position[0] + 1, position[1] + point_value)] == 0) {
                        // forward and to the right
                        temp_string = std::to_string(position[0] + 1) + std::to_string(position[1] + point_value);
                        possible_moves.push_back(temp_string);
                        temp_string = "";
                    }
                } 

                // check the other edge
                if (position[0]-1 != -1) {
                    if (board[convert_index(position[0] - 1, position[1] + point_value)]) {
                       // forward to the left
                       temp_string = std::to_string(position[0] - 1) + std::to_string(position[1] + point_value);
                       possible_moves.push_back(temp_string);
                       temp_string = "";
                    }
                }

            }  else {
                ascend = true; // can't move pawn. Only exchange for different piece.
            }
        } // end of the find_possible_moves
};

class knight : public piece {
    protected:
        // protected variables
        std::vector<std::string> possible_moves;
    public:
        knight() :piece{} {
            name = "knight";
            point_value = 3;
        }
        knight(int init_position, std::string init_name, bool init_colour) : piece{init_position,"knight", init_colour} {}
        virtual ~knight() {};

        void find_possible_moves(int* board) {
            std::string temp_string;
            // first move
            int* x_moves;
            x_moves = new int[8]{-2,-1,+2,-1,-2,+1,+2,+1};
            int* y_moves;
            y_moves = new int[8]{-1,-2,+1,+2,+1,-2,-1,+2};

            for (size_t i{0}; i<8; i++) {
                if ((0 <= position[0] + x_moves[i]) && (7 >= position[0] + x_moves[i])) { // check range
                    if ((0 <= position[1] + y_moves[i]) && (7 >= position[1] + y_moves[i])) {
                        // do something idk ......... finish the knight move

                    }
                }
            }

            temp_string = std::to_string(position[0] - 1) + std::to_string(position[1] + point_value);
            possible_moves.push_back(temp_string);
            temp_string = "";
        
            delete x_moves;
            delete y_moves;
        }
};

class bishop : public piece { // get the find moves function outside of the class definition
    protected:
        // protected variables
    public:
        bishop() : piece{} {
            name = "bishop";
            point_value = 3;
        }
};

class rook : public piece { // get the find moves function outside of the class definition
    protected:
        // protected variables
    public:
        rook() : piece{} {
            name = "rook";
            point_value = 5;
        }
};

class queen : public piece { // combine the two functions from above into one  -----
    protected:
        // protected variables
    public:
        queen() : piece{} {
            name = "queen";
            point_value = 9;
        }
};

class king : public piece { // one in each direction
    protected:
        // protected variables
        std::vector<std::string> possible_moves;
    public:
        king() : piece {} {
            name = "king";
            point_value = 10;
        }

        void find_possible_moves() {
            std::string temp_string;
            // first move
            int* x_moves;
            x_moves = new int[8]{1,1,0,1,0,-1,-1,-1};
            int* y_moves;
            y_moves = new int[8]{0,1,1,-1,-1,-1,0,1};

            for (size_t i{0}; i<8; i++) {
                if ((0 <= position[0] + x_moves[i]) && (7 >= position[0] + x_moves[i])) { // check range
                    if ((0 <= position[1] + y_moves[i]) && (7 >= position[1] + y_moves[i])) {
                        // do something idk ......... finish the knight move
                        // check if the 
                    }
                }
            }

            temp_string = std::to_string(position[0] - 1) + std::to_string(position[1] + point_value);
            possible_moves.push_back(temp_string);
            temp_string = "";
        
            delete x_moves;
            delete y_moves;

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
