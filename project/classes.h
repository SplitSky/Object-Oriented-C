// this file contains classes
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>
#include<algorithm>


int convert_index(int x, int y) {
    return (x-1) + 8*(y-1);
}

// translate number to chess notation
std::string capitalizeString(std::string word) {
    transform(word.begin(), word.end(), word.begin(), [](unsigned char c){return std::toupper(c);});
    return word;
}
 
std::string convert_chess_notation(std::string initial_pos) { // not tested
    // initial position is a string of two numbers i.e. 11, 24
    std::map<int, std::string> position_map = {{1,"A",},{2,"B",},{3,"C",},{4,"D",},{5,"E",},{6,"F",},{7,"G",},{8,"H",}};
    std::string chess_notation;
    chess_notation = position_map.find(int(initial_pos[0]))->second;
    return chess_notation + initial_pos[1];
}

std::vector<int> decode_chess_notation(std::string notation) {
    std::vector<int> position = {0,0};
    char temp_string = notation[0];
    std::map<int, char> position_map = {{1,'A',},{2,'B',},{3,'C',},{4,'D',},{5,'E',},{6,'F',},{7,'G',},{8,'H',}};
    position[0] = position_map.find(temp_string)->first;
    position[1] = int(notation[1]);
    return position;
}

class piece {
    protected:
        // protected variables
        int position[2]; // array of two numbers. First is letter second is number i.e. [1,1] is A1
        std::string name; // e.g. pawn
        int point_value; // the colour depends on the sign of the point value. while is positive
        std::vector<std::string> possible_moves;
    public:
        bool removed{false};
        piece() {
            position[0] = 1;
            position[1] = 1;
            name = "empty";
            point_value = 0;
        };
        piece(int x, int y, std::string init_name, int init_point) : name{init_name}, point_value{init_point} {
            std::cout << "making the " << name << " at: " << x << ", "<<y << std::endl;
            position[0] = x;
            position[1] = y;
        };
        virtual ~piece() {};

        std::string get_pos() {
            return std::to_string(position[0]) + "," + std::to_string(position[1]);
        }

        void set_pos(int x, int y) {
            position[0] = x;
            position[1] = y;
        }

        virtual bool find_possible_moves(int* board) {
            possible_moves.push_back("00");
            return false;
        }

        std::vector<std::string> list_moves() {return possible_moves;}

        std::string get_name() {return name;}

        bool is_removed() { return removed; }

        int get_point() { return point_value; }

        virtual bool find_attack_moves(int* board) {return false;}

        void set_possible_moves(std::vector<std::string> moves) {possible_moves = moves;}

};

class pawn : public piece {
    protected:
        // protected variables
        bool not_moved{true};
        //std::vector<std::string> possible_moves;
        bool ascend{false};
        std::vector<std::string> danger_moves;
    public:
        pawn() :piece{} {
            name = "pawn";
            point_value = 1;
        };
        pawn(int x, int y, int init_point) : piece{x,y,"pawn", init_point} {}
        virtual ~pawn() {};

        bool find_possible_moves(int* board) {
            // position[0] ranges from 0 - 7. +1 for the real value
            std::string temp_string;
            bool check{false};
            // first move

            // possible moves
            // +1,0 -1,0 or pv+,0
            // if first 2 check then check
            int* x_moves;
            x_moves = new int[2]{+1,-1};
            possible_moves = {};

            // move ahead
            if ((position[1]+point_value >= 1) || (position[1]+point_value <= 8)) {
                if (board[convert_index(position[0], position[1] + point_value)] == 0) { // if the place ahead is empty
                    temp_string = std::to_string(position[0]) + std::to_string(position[1] + point_value);
                    possible_moves.push_back(temp_string);
                    temp_string = "";
                }
            }
 
            for (size_t i{0}; i<2; i++) {
                if ((1 <= position[0] + x_moves[i]) && (8 >= position[0] + x_moves[i])) { // check range y-axis
                    if ((1 <= position[1] + point_value) && (8 >= position[1] + point_value)) { // check range x-axis
                        if (board[convert_index(position[0] + x_moves[i], position[1] + point_value)]*point_value < 0) { // the piece in the place is enemy
                            temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + point_value);
                            possible_moves.push_back(temp_string);
                            temp_string = "";                           
                            if (board[convert_index(position[0] + x_moves[i], position[1] + point_value)]*point_value == -10) {check = true;}
                        }
                    }
                }
            }
            delete x_moves;
            return check;
        }

        bool find_attack_moves(int* board) {
            std::string temp_string;
            bool check{false};
            int* x_moves;
            x_moves = new int[2]{+1,-1};
            possible_moves = {};

            for (size_t i{0}; i<2; i++) {
                if ((1 <= position[0] + x_moves[i]) && (8 >= position[0] + x_moves[i])) { // check range y-axis
                    if ((1 <= position[1] + point_value) && (8 >= position[1] + point_value)) { // check range x-axis
                        if (board[convert_index(position[0] + x_moves[i], position[1] + point_value)]*point_value < 0) { // the piece in the place is enemy
                            temp_string = std::to_string(position[0] + x_moves[i]) + std::to_string(position[1] + point_value);
                            danger_moves.push_back(temp_string);
                            temp_string = "";                           
                            if (board[convert_index(position[0] + x_moves[i], position[1] + point_value)]*point_value == -10) {check = true;}
                        }
                    }
                }
            }
            delete x_moves;
            return check;
        }
};

class knight : public piece {
    protected:
        // protected variables
        //std::vector<std::string> possible_moves;
    public:
        knight() :piece{} {
            name = "knight";
            point_value = 3;
        }
        knight(int x, int y, int init_point) : piece{x,y,"knight", init_point} {
            position[0] = x;
            position[1] = y;
        }
        virtual ~knight() {};
        bool find_possible_moves(int* board) {
            std::string temp_string;
            bool check{false};
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
                            if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])]*point_value == -30) {
                                check = true;
                            }
                        }
                    }
                }
            }
            delete x_moves;
            delete y_moves;
            return check;
        }
};

class bishop : public piece { // get the find moves function outside of the class definition
    protected:
        // protected variables
        //std::vector<std::string> possible_moves;

    public:
        bishop() : piece{} {
            name = "bishop";
            point_value = 4;
        }

        bishop(int x, int y, int init_point) : piece{x,y,"bishop", init_point} {
            position[0] = x;
            position[1] = y;
        }

        bool find_possible_moves(int* board) {
            std::string temp_string;
            bool check{false};
            int multiplier;
            int* x_moves;
            x_moves = new int[4]{-1,+1,+1,-1};
            int* y_moves;
            y_moves = new int[4]{+1,+1,-1,-1};
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
                            temp_string = "";                             
                            keep_going = false;
                            if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value == -40) {
                                check = true;
                            }
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
            return check;
        }
};

class rook : public piece { // get the find moves function outside of the class definition
    protected:
        // protected variables
        //std::vector<std::string> possible_moves;
    public:
        rook() : piece{} {
            name = "rook";
            point_value = 5;
        }

        rook(int x, int y, int init_point) : piece{x,y,"rook", init_point} {
            position[0] = x;
            position[1] = y;
        }

        ~rook() {}

        bool find_possible_moves(int* board) {
            bool check{false};
            std::string temp_string;
            int multiplier;
            int* x_moves;
            x_moves = new int[4]{0,+1,0,-1};
            int* y_moves;
            y_moves = new int[4]{+1,0,-1,0};

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
                            temp_string = "";                            
                            // stop
                            keep_going = false;
                            if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])]* point_value == -50) {
                                check = true;
                            }

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
            return check;
        }
};

class queen : public piece {
    protected:
        // protected variables
        //std::vector<std::string> possible_moves;
    public:
        queen() : piece{} {
            name = "queen";
            point_value = 9;
        }

        queen(int x, int y, int init_point) : piece{x,y,"queen", init_point} {
            position[0] = x;
            position[1] = y;
        }

        bool find_possible_moves(int* board) {
            std::string temp_string;
            int multiplier;
            int* x_moves;
            x_moves = new int[8]{0,+1,0,-1,-1,+1,+1,-1};
            int* y_moves;
            y_moves = new int[8]{+1,0,-1,0,+1,+1,-1,-1};
            bool check{false};

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
                            temp_string = "";                            
                            // stop
                            keep_going = false;
                            if (board[convert_index(position[0] + multiplier * x_moves[i], position[1] + multiplier * y_moves[i])] * point_value == -90) { // check
                                check = true;
                            }

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
            return check;
        }
};

class king : public piece { // one in each direction
    protected:
        bool safe{true};
    public:
        king() : piece {} {
            name = "king";
            point_value = 10;
        }

        king(int x, int y, int init_point) : piece{x,y,"king", init_point} {
            position[0] = x;
            position[1] = y;
        }

        ~king() {}

        bool find_possible_moves(int* board) {
            bool check{false};
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
                        // check if it's a check
                        if (board[convert_index(position[0] + x_moves[i], position[1] + y_moves[i])] * point_value == -100) {
                            check = true;
                        } // check logic
                    }
                }
            }

            delete x_moves;
            delete y_moves;
            return check;
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
        int standard_game[64] = {+5,+3,+4,+9,+10,+4,+3,+5,+1,+1,+1,+1,+1,+1,+1,+1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-5,-3,-4,-10,-9,-4,-3,-5};
        int *board_rep = new int[64];  // dynamically assign an integer array for board representation
        piece** pieces_array = new piece*[32];
        bool check{false};
        bool mate{false};

    public:
        board() = default;
        board(bool default_board) {

            if (default_board == true) {
                // load in the initial file
                load_game(true);
                //print_data();
                print_board();
            } else {
                // load in a different name
                // read in the game file
                load_game(false);
                print_board();
            }
        }
        ~board() {
            delete[] board_rep;
            
            for (size_t i{0}; i<32; i++) {
                delete pieces_array[i];
            }
            delete[] pieces_array;
        }

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
            std::string choice;
            std::cin >> choice;
        }


        void load_game(bool default_mode) { // works

            std::cout << "loading game" << std::endl;
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
                    std::cout << "loading this into vector: "<< line << std::endl;
                    board_rep[i] = std::stoi(line);
                    std::cout << "index: " << i << std::endl;
                    std::cout << "This is board_rep at i: " << board_rep[i] << std::endl;
                }
                my_file.close();
            }

            // decode and create objects
            int *board_rep2 = board_rep;
            
            int piece_count{0};
            for (int j{1}; j<=8; j++) {
                for (int i{1}; i<=8;i++) { 

                    if (board_rep[convert_index(i,j)] == 1 || board_rep[convert_index(i,j)] == -1) {
                        // pawn
                        //board_rep[convert_index(i,j)] = board_2[convert_index(i,j)];
                        piece_count++;
                        pieces_array[piece_count] = new pawn{i,j,board_rep[convert_index(i,j)]};

                    } else if (board_rep[convert_index(i,j)] == 3 || board_rep[convert_index(i,j)] == -3) {
                        // knight
                        //board_rep[convert_index(i,j)] = board_2[convert_index(i,j)];
                        piece_count++;
                        pieces_array[piece_count] = new knight{i,j,board_rep[convert_index(i,j)]};

                    } else if (board_rep[convert_index(i,j)] == 4 || board_rep[convert_index(i,j)] == -4) {
                        // bishop
                        //board_rep[convert_index(i,j)] = board_2[convert_index(i,j)];
                        piece_count++;
                        pieces_array[piece_count] = new bishop{i,j,board_rep[convert_index(i,j)]}; 

                    } else if (board_rep[convert_index(i,j)] == 5 || board_rep[convert_index(i,j)] == -5) {
                        // rook
                        //board_rep[convert_index(i,j)] = board_2[convert_index(i,j)];
                        piece_count++;
                        pieces_array[piece_count] = new rook{i,j,board_rep[convert_index(i,j)]}; 

                    } else if (board_rep[convert_index(i,j)] == 10 || board_rep[convert_index(i,j)] == -10) {
                        // king
                        //board_rep[convert_index(i,j)] = board_2[convert_index(i,j)];
                        piece_count++;
                        pieces_array[piece_count] = new king{i,j,board_rep[convert_index(i,j)]};

                    } else if (board_rep[convert_index(i,j)] == 9 || board_rep[convert_index(i,j)] == -9) {
                        // queen
                        //board_rep[convert_index(i,j)] = board_2[convert_index(i,j)];
                        piece_count++;
                        pieces_array[piece_count] = new queen{i,j,board_rep[convert_index(i,j)]};
                    } else {
                        //board_rep[convert_index(i,j)] = 0;
                    }
        
                }
            }
        }

        void print_data() {
            for (size_t i{0}; i<64; i++) {
                std::cout << "the variable entry" << board_rep[i] << std::endl;
            }  
        }

        void save_game() { // works
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

        void purge_objects() {
            for (size_t i{0}; i<32; i++) {
                //delete pieces_array[i];
            }
        }


        std::vector<std::string> list_moves() { // list all moves without check monitoring
            // loop through all objects and list moves
            std::cout << "Listing possible moves: " << std::endl;
            std::string temp_name;
            std::vector<std::string> moves;
            std::vector<std::string> temp_moves;
            for (size_t i{0}; i<32; i++) {
                // check if empty
                if (pieces_array[i]->is_removed() == false) { 
                    pieces_array[i]->find_possible_moves(board_rep);
                     
                    std::cout << "moves for ";
                    std::cout << pieces_array[i]->get_name();
                    std::cout << " positioned at : " << pieces_array[i]->get_pos();

                    temp_moves = pieces_array[i]->list_moves();
                    for (size_t j{0}; j < temp_moves.size() ; j++) {
                        moves.push_back(temp_moves[j]); // iterate over the individual moves
                    }
                }
            }
            return moves;
        }



        void PvP() {
            // player vs player game
            // 1. load the initial set up. Player 1 is white. Player 2 is black.
            // 2. Play game
            // 3. Type "X" if you want to quit.
            // 4. Type "XS" if you want to quit and save the game
            
            // white player starts
            int player{1};
            while (mate == false) {
                play_turn(player);
                player = player*-1;
            }
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
            std::cout << "   | A | B | C | D | E | F | G | H | " << std::endl;
            std::cout << "################################################" << std::endl;
                for (size_t i{8}; i != 0; i--) {
                    // Line starting with BLACK
                    printLine(i);
                }
            std::cout << "################################################" << std::endl;
        }

        std::string return_piece(int n) {
            int temp_n = n;
            if (temp_n < 0) {
                temp_n = temp_n*-1;
            }
            std::string piece;
            if (temp_n == 0) {
                return "0";
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

        void printLine(int y) {

            for (size_t i{0}; i<9; i++) {
                for (size_t j{0}; j<3; j++) {std::cout << " ";}
                std::cout << "|";
            }
            std::cout<<std::endl;
            
            std::cout << " " << y << " |";
            for (size_t i{1}; i<=8; i++) { 
                std::cout << " " << return_piece(board_rep[convert_index(i,y)]) << " ";

                //std::cout << std::endl << "the index: " << convert_index(i,y) << std::endl;

                std::cout << "|";
            }
            std::cout << std::endl;

            for (size_t i{0}; i<9; i++) {
                for (size_t j{0}; j<3; j++) {std::cout << " ";}
                std::cout << "|";
            }
            std::cout<<std::endl;
            std::cout << "----------------------------------------------" << std::endl;

        }

        bool is_king_safe(int player, int king_index) {
            bool safe{true};
            pieces_array[king_index]->find_possible_moves(board_rep);
            std::string position = pieces_array[king_index]->get_pos();
            std::vector<std::string> all_moves;
            std::vector<std::string> king_moves = pieces_array[king_index]->list_moves();
            // get array of enemy attack moves;
            for (size_t i{0}; i<32; i++) {
                // check if the piece was removed
                if (pieces_array[king_index]->get_point()*player < 0) { // find only moves for enemy pieces
                    if (pieces_array[i]->is_removed() == false) {
                        // list moves but with special function for pawns
                        if (pieces_array[i]->get_name() == "pawn") {
                            pieces_array[i]->find_attack_moves(board_rep);
                        } else { 
                            pieces_array[i]->find_possible_moves(board_rep);
                        }
                    }
                    // append all lists together
                    all_moves = pieces_array[i]->list_moves();
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

        /// notes notes ntoes
        //
        // can the king moves runs once. The attack moves should be added as a variable in the board class
        // The can king move uses that array and returns the list of the king's moves which the player can select.
        // If the king can't move and is not safe the game ends

        bool can_king_move(int player, int king_index) {
            bool safe{true};
            pieces_array[king_index]->find_possible_moves(board_rep);
            std::string position = pieces_array[king_index]->get_pos();
            std::vector<std::string> all_moves;
            std::vector<std::string> king_moves = pieces_array[king_index]->list_moves();
            int counter{0};
            // get array of enemy attack moves;
            for (size_t i{0}; i<32; i++) {
                // check if the piece was removed
                if (pieces_array[king_index]->get_point()*player < 0) { // find only moves for enemy pieces
                    if (pieces_array[i]->is_removed() == false) {
                        // list moves but with special function for pawns
                        if (pieces_array[i]->get_name() == "pawn") {
                            pieces_array[i]->find_attack_moves(board_rep);
                        } else { 
                            pieces_array[i]->find_possible_moves(board_rep);
                        }
                    }
                    // append all lists together
                    all_moves = pieces_array[i]->list_moves();
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

            pieces_array[king_index]->set_possible_moves(all_moves); // overwrite the possible moves after check verification
            
            if (all_moves.size() == 0) {
                return false; // check mate
            } else {
                return true; // just check
            }

        }           


        void find_all_moves(int player) {
            // +1 if white, -1 if black;
        
            bool indicator{false};
            std::vector<std::string> player_moves;
            for (size_t i{0}; i<32; i++) { // loops through the pieces 
                if (pieces_array[i]->get_point()*player > 0) { // this check makes sure the pieces for which moves we find belong to the player
                    indicator = pieces_array[i]->find_possible_moves(board_rep);
                }   
            }
            // enemy moves contains all the moves from a piece which checks our king
        }

        int get_choice() {
            bool valid = false;
            int piece_index;
            std::string choice;
            std::cout << "Enter the position of the piece (in form ex. A1): ";
            std::cin >> choice;

            for (size_t i{0}; i<32; i++) {
                if (choice == pieces_array[i]->get_pos()) {return piece_index;}
            }

            return -1;
        }

        int find_king_index(int player) {
            // w>0 ; b<0
            for (size_t i{0}; i<32; i++) { // loop through pieces array
                if (pieces_array[i]->get_name() == "king") {
                    if (pieces_array[i]->get_point()*player > 0) {
                        return i;
                    }
                }
            }
        }

        void play_turn(int player) {
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
            piece* current_piece = pieces_array[indicator];
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
            piece_location = decode_chess_notation(current_piece->get_pos()); 
            std::vector<int> new_position = decode_chess_notation(choice);
            board_rep[] ;

   
        }


}; // valgrind for memory leaks

