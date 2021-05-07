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
    public:
        
        pawn() :piece{} {
            name = "pawn";
            point_value = 1;
        };
        pawn(int init_position, std::string init_name, bool init_colour) : piece{init_position,"pawn", init_colour} {}
        virtual ~pawn() {};
};

class board {
    // copy and move operators

    // The pieces array contains all the pieces used.
    // The board contains the references to the point values and the position of the pieces.
    // The board construction allows for the calculation of the score of the board easily
    // the pieces pointers get the position modified and stores the actual position
    // when a piece moves update the actual position and then update the integer array
    private:
        piece *pieces_array[32];
        int *board;
        int board[64]; // the index is col*(j-1) + (i-1)
    public:
        board() = default;
        board() {} /// bookmark

        int sum_board() {
            int sum{0};
            for (size_t i{0}; i<65; i++) {
                sum += board[i];
            }
        }
        
};
