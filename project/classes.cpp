// this file contains classes
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF
#define BLACK_KING '\u2654'
#define BLACK_QUEEN '\u2655'
#define BLACK_ROOK '\u2656'
#define BLACK_BISHOP '\u2657'
#define BLACK_KNIGHT '\u2658'
#define BLACK_PAWN '\u2659'

#define WHITE_KING '\u265A'
#define WHITE_QUEEN '\u265B'
#define WHITE_ROOK '\u265C'
#define WHITE_BISHOP '\u265D'
#define WHITE_KNIGHT '\u265E'
#define WHITE_PAWN '\u265F'
//
// copy and move constructors only used for the board class

int convert_index(int x, int y) {
    return (x-1) + 8*(y-1);
}

// translate number to chess notation

class piece {
    protected:
        // protected variables
        int position[2]; // array of two numbers. First is letter second is number i.e. [1,1] is A1
        std::string name; // e.g. pawn
        int point_value; // the colour depends on the sign of the point value. black is positive
    public:
        bool removed{false};
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

                        if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])] == 0) { // if the place is empty
                            temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                            possible_moves.push_back(temp_string);
                            temp_string = "";

                        } else if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])]*point_value < 0) {
                            temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                            possible_moves.push_back(temp_string);
                            temp_string = "";                           
                            // enemy piece on the square
                        }
                }
            }


        
            delete x_moves;
            delete y_moves;
        }
};

class bishop : public piece { // get the find moves function outside of the class definition
    protected:
        // protected variables
        std::vector<std::string> possible_moves;

    public:
        bishop() : piece{} {
            name = "bishop";
            point_value = 3;
        }

        void find_possible_moves(int* board) {
            std::string temp_string;
            int multiplier;
            int* x_moves;
            x_moves = new int[8]{-1,+1,+1,-1};
            int* y_moves;
            y_moves = new int[8]{+1,+1,-1,-1};
            for (size_t i{0}; i<4; i++) {
                // loops over four directions
                bool keep_going{true};
                multiplier = 0;
                while (keep_going) {
                    if (board[convert_index(position[0] + multiplier*x_moves[i], position[1] + multiplier*y_moves[i])] == 0) {
                        temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";

                    } else {
                        if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value < 0) { // enemy piece
                            temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                            possible_moves.push_back(temp_string);
                            temp_string = "";                            // append move and stop
                            // stop
                            keep_going = false;
                        } else {
                            // friendly piece
                            // stop without appending
                            keep_going = false;
                        }
                    }
                    multiplier += 1;
                } // end while
                
            }

            delete x_moves;
            delete y_moves;
        }
};

class rook : public piece { // get the find moves function outside of the class definition
    protected:
        // protected variables
        std::vector<std::string> possible_moves;
    public:
        rook() : piece{} {
            name = "rook";
            point_value = 5;
        }

        void find_possible_moves(int* board) {
            std::string temp_string;
            int multiplier;
            int* x_moves;
            x_moves = new int[8]{0,+1,0,-1};
            int* y_moves;
            y_moves = new int[8]{+1,0,-1,0};
            for (size_t i{0}; i<4; i++) {
                // loops over four directions
                bool keep_going{true};
                multiplier = 0;
                while (keep_going) {
                    if (board[convert_index(position[0] + multiplier*x_moves[i], position[1] + multiplier*y_moves[i])] == 0) {
                        temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";

                    } else {
                        if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value < 0) { // enemy piece
                            temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                            possible_moves.push_back(temp_string);
                            temp_string = "";                            // append move and stop
                            // stop
                            keep_going = false;
                        } else {
                            // friendly piece
                            // stop without appending
                            keep_going = false;
                        }
                    }
                    multiplier += 1;
                } // end while
                
            }

            delete x_moves;
            delete y_moves;
        }
};

class queen : public piece { // combine the two functions from above into one  -----
    protected:
        // protected variables
        std::vector<std::string> possible_moves;
    public:
        queen() : piece{} {
            name = "queen";
            point_value = 9;
        }
        void find_possible_moves(int* board) {
            std::string temp_string;
            int multiplier;
            int* x_moves;
            x_moves = new int[8]{0,+1,0,-1,-1,+1,+1,-1};
            int* y_moves;
            y_moves = new int[8]{+1,0,-1,0,+1,+1,-1,-1};

            for (size_t i{0}; i<8; i++) {
                // loops over four directions
                bool keep_going{true};
                multiplier = 0;
                while (keep_going) {
                    if (board[convert_index(position[0] + multiplier*x_moves[i], position[1] + multiplier*y_moves[i])] == 0) {
                        temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";

                    } else {
                        if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value < 0) { // enemy piece
                            temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                            possible_moves.push_back(temp_string);
                            temp_string = "";                            // append move and stop
                            // stop
                            keep_going = false;
                        } else {
                            // friendly piece
                            // stop without appending
                            keep_going = false;
                        }
                    }
                    multiplier += 1;
                } // end while
                
            }

            delete x_moves;
            delete y_moves;
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

               void find_possible_moves(int* board) {
            std::string temp_string;
            int* x_moves;
            x_moves = new int[8]{0,+1,0,-1,-1,+1,+1,-1};
            int* y_moves;
            y_moves = new int[8]{+1,0,-1,0,+1,+1,-1,-1};

            for (size_t i{0}; i<8; i++) {
                if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])] == 0) {
                    temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                    possible_moves.push_back(temp_string);
                    temp_string = "";

                } else {
                    if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])]* point_value < 0) { // enemy piece
                        temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + y_moves[i]);
                        possible_moves.push_back(temp_string);
                        temp_string = "";
                    }
                }
            }

            delete x_moves;
            delete y_moves;
        }};

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

        // initialization function
        void start_game() {
            // print introduction screen
            // select gamemode
            // 1. player vs player
            // 2. player vs AI
            // 3. load game
            //
            std::cout << "Welcome! What would you like to do?:" << std::endl;
            std::cout << "1. Player vs Player" << std::endl;
            std::cout << "2. Player vs AI" << std::endl;
            std::cout << "3. Load Previous game" << std::endl;
            std::string choice;
            std::cin >> choice;
        }

        std::vector<int> load_default() {
            std::vector<int> board;
            std::string line;
            // loads the default board set up from a file
            std::fstream my_file;
            my_file.open("default.txt", std::ios::in);
            if (!my_file) {
                std::cout << "No such file!" << std::endl;
            } else {
                std::cout << "File present!" << std::endl;
                
                while (!my_file.eof()) {
                    line = "";
                    getline(my_file, line);
                    board.push_back(stoi(line));
                }
                my_file.close();
            }

            // decode and create objects



            return board;
        }

        std::vector<std::string> list_moves() {
            // loop through all objects and list moves
            std::vector<std::string> moves;

            for (size_t i; i<32; i++) {
              
            }
        

            return moves;
        }

        bool save_game(std::vector<int>) {
            std::string line;

            return true;
        }

        void PvP() {
            // player vs player game
            // 1. load the initial set up. Player 1 is white. Player 2 is black.
            // 2. Play game
            // 3. Type "X" if you want to quit.
            // 4. Type "XS" if you want to quit and save the game
        }

        void PvAI() {
            // player vs AI
            // 1. load the initial set up. Player colour is random. AI takes the other one.
            // 2. Play the game
            // 3. Type "X" if you want to quit.
            // 4. Type "XS" if you want to quit and save the game 
        }

        void LoadGame() {
            // Select the game type
            // 1. Load the game
            // 2. Resume the PvAI game
        }

        void print_board() {
            std::cout << "   A     B     C     D     E     F     G     H" << std::endl;
                for (int iLine = 7; iLine >= 0; iLine--) {
                    if ( iLine%2 == 0) {
                    // Line starting with BLACK
                        printLine(iLine, BLACK_SQUARE, WHITE_SQUARE);
                    } else {
                        // Line starting with WHITE
                        printLine(iLine, WHITE_SQUARE, BLACK_SQUARE);
                    }
                }
        }

        void printLine(int y, int iColor1, int iColor2) {
           int const CELL = 6;

           // Since the width of the characters BLACK and WHITE is half of the height, 
           // we need to use two characters in a row.
           // So if we have CELL characters, we must have CELL/2 sublines
           for (int subLine = 0; subLine < CELL/2; subLine++) {
              // A sub-line is consisted of 8 cells, but we can group it
              // in 4 iPairs of black&white
              for (int iPair = 0; iPair < 4; iPair++) {
                 // First cell of the pair
                 for (int subColumn = 0; subColumn < CELL; subColumn++) {
                    // The piece should be in the "middle" of the cell
                    // For 3 sub-lines, in sub-line 1
                    // For 6 sub-columns, sub-column 3
                    if ( subLine == 1 && subColumn == 3) {
                        std::cout << char(game.getPieceAtPosition(iLine, iPair*2) != 0x20 ? 
                                     game.getPieceAtPosition(iLine, iPair*2) : iColor1);
                    } else {
                        std::cout << char(iColor1);
                    }
                 }

                 // Second cell of the pair
                 for (int subColumn = 0; subColumn < CELL; subColumn++) {
                    // The piece should be in the "middle" of the cell
                    // For 3 sub-lines, in sub-line 1
                    // For 6 sub-columns, sub-column 3
                    if ( subLine == 1 && subColumn == 3) {
                       cout << char(game.getPieceAtPosition(iLine,iPair*2+1) != 0x20 ? 
                                      game.getPieceAtPosition(iLine,iPair*2+1) : iColor2);
                    }
                    else  {
                       cout << char(iColor2);
                    }
                 }
              }
           }
        }


};
