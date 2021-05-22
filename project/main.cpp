// Object oriented C++ - Project main
//
// Tomasz Neska
// 05/05/2021
#include<fstream>
#include<iostream>
#include<cmath>
#include<array>
#include<iterator>
#include<cstring>
#include "classes.h" // header including all class definitions



int main() {
    std::cout <<  "#### Welcome to Chess! ####"  << std::endl;
    bool loop{true};


    board *a = new board(true);

    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1) New Game - 2 Players" << std::endl;
    std::cout << "2) New Game - AI" << std::endl;
    std::cout << "3) Load Previous Game" << std::endl;
    std::cout << "4) Close" << std::endl;
    int choice;
    std::cout << "Enter your choice: ";
    //std::cin >> choice;
    choice = 1; // testing
    while (std::cin.fail()) {
        std::cout << "The input is incorrect. Try again" << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }

    //validation for input
    if (choice == 1) {
        // declare board object
        board *Current_game = new board(true);
        // populate the board
        // Start game
        Current_game->PvP();
        // Player 1 turn
        // player 2 turn
        // loop until game end
    } else if (choice == 2) {
        // declare the board object
        //board *Current_game = new board(true);
        // populate the board
        // Start game
        // Player 1 turn
        // Player 2 turn
        // loop until game end
    } else if (choice == 3) {
        // declare the board object
        //board *Current_game = new board(false);
        // load the board
        // resume the game
        // note: check the point value of the last piece and resume the other colour
    } else if(choice == 4) {
        loop = false;
    } else {
        std::cout << "Invalid choice. Try again.";
        std::cin.clear();
        std::cin.ignore();
    }
    return 0;
}
