// this file contains classes
#include<string>
//
// copy and move constructors only used for the board class
//
class piece {
    protected:
        // protected variables
        std::string position; // two character position e.g. A1
        std::string name; // e.g. pawn
        int point_value; // the colour depends on the sign of the point value. black is positive
        
    public:
        piece() {
            position = "00";    
        };
        piece(std::string init_position, std::string init_name, bool init_colour) : position{init_position}, name{init_name} {};
        virtual ~piece() {};

        std::string get_pos() {
            return this->position;
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

        pawn(std::string init_position, std::string init_name, bool init_colour) : piece{init_position,"pawn", init_colour} {}
        virtual ~pawn() {};
        
};

class board {

};
