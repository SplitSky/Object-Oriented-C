// GeneralCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// Assignment 1 - skeleton code
// Your name and date
// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<string>

int main()
{
    // Declare variables here
    constant double electron_volt{ 1.6E-19 };
    int Z{ 0 };
    int n_1{ 0 };
    int n_2{ 0 };
    double E{ 0 };
    // Ask user to enter atomic number
    std::cout << "Enter the atomic number: " << std::endl;
    std::cin >> Z;
    while (std::cin.fail()) {
        std::cout << "The atomic number is incorrect";
        std::cin.clear();
        std::cin.ignore();
        std::cin >> Z;
    }
    // Ask user to enter initial and final quantum numbers
    std::cout << "Enter the first quantum number n: " << std::endl;
    std::cin >> n_1;
    // validation

    std:cout << "Enter the second quantum number n: " << std::endl;
    std::cin >> n_2;


    // Compute photon energy, Delta E = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
    std:cout << "Should it be displayed in eV or Joules? (e/J)" << std::endl;



    // Output answer

    return 0;
}