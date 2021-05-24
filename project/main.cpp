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
#include "functions.h"
#include "board_class.h"



int main() {
    std::cout <<  "#### Welcome to Chess! ####"  << std::endl;


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
        board *current_game = new board(true);
        current_game->PvP();
    } else if (choice == 2) {
        board *current_game = new board(true);
        current_game->PvAI();
    } else if (choice == 3) {
        board *current_game = new board(false);
        current_game->PvP();
    } else if(choice == 4) {
        std::cout << "Quitting chess!" << std::endl;
    } else {
        std::cout << "Invalid choice. Try again.";
        std::cin.clear();
        std::cin.ignore();
    }
    return 0;
}
