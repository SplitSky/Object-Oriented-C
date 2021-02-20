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

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>


int main(){
	
	// Declare variables here
	const double electron_volt{1.6E-19};
	int Z{0};
	int n_1{0};
	int n_2{0};
	double E{0};
	bool interrupt_bool{false};
	char choice{};
	
	
	while (interrupt_bool == false) {
		
	
		// Ask user to enter atomic number
		std::cout << "Enter the atomic number: " << std::endl;
		std::cin >> Z;
		while (std::cin.fail()) {
			std::cout << "The atomic number is incorrect. Try again: ";
			std::cin.clear();
			std::cin.ignore();
			std::cin >> Z;
		}
		
		// Ask user to enter initial and final quantum numbers
		std::cout << "Enter the first quantum number n: " << std::endl;
		std::cin >> n_1;
		// validation
		while (std::cin.fail() || n_1 <= 0) {
			std::cout << "The number is incorrect. Try again: ";
			std::cin.clear();
			std::cin.ignore();
			std::cin >> n_1;
		}
				
		std::cout << "Enter the second quantum number n: " << std::endl;
		std::cin >> n_2;
		while (std::cin.fail() || n_1 < n_2 ) {
			std::cout << "The number is incorrect. Try again: ";
					std::cin.clear();
			std::cin.ignore();
			std::cin >> n_2;
		}
		
		// Compute photon energy, Delta E = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
		std::cout << "Should it be displayed in eV or Joules? (e/J)" << std::endl;
		std::cin >> choice;
		while (std::cin.fail() || (choice != 'e' && choice != 'J')) {
			std::cout << "The choice is incorrect. Try again: ";
			std::cin.clear();
			std::cin.ignore();
			std::cin >> choice;
		}
				
		if (choice == 'J'){
			E = 13.6 * std::pow(Z,2) * (1/std::pow(n_1,2) - 1/std::pow(n_2,2)) * electron_volt;
			std::cout << "The energy is: " << std::setprecision(3) << E << " Joules" << std::endl; 
		} else {
			E = 13.6 * std::pow(Z,2) * (1/std::pow(n_1,2) - 1/std::pow(n_2,2));
			std::cout << "The energy is: " << std::setprecision(3) << E << " eV" << std::endl; 
		}
				
		
		std::cout << "Should it repeat? (y/n)" << std::endl;
		std::cin >> choice;
		while (std::cin.fail() || (choice != 'y' && choice != 'n')) {
			std::cout << "The choice is incorrect. Try again: ";
			std::cin.clear();
			std::cin.ignore();
			std::cin >> choice;
		}
			
		if (choice=='n') {
			interrupt_bool = true;
		}
		
	}
    return 0;
}