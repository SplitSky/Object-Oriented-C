
// PHYS 30762 Programming in C++
// Assignment 2
// Tomasz Neska 20/02/2021

// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file

// Skeleton code - assessed components are missing

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>

// Functions

double splicing(std::string long_string, int first_index, int last_index) {
    std::string word{};
    char temp_array[20];
    for (int i = first_index; i <= last_index ;i++) {
        word = word + long_string[i];
    }
    double number = std::stod(word);
    // number to float is number = std::stof(word)
    return number;
}

// Main function

int main() {
	    // declare variables
    int N{0};
    std::string file_line;
    std::fstream my_file("courselist.dat");

    if (!my_file.good()) {
        std::cout << "The file couldn't be loaded";
        return -1;
    } else {
        // count the number of lines in the file
	while(!my_file.eof()) {
	    getline(my_file,file_line);
	    N++;
	}
	my_file.close();		
    }
    
    std::ifstream my_file2("courselist.dat");
    std::string *data_array{new std::string[N]}; // stores data as strings
    double standard_deviation{};
    double mean{};
    double std_error{};
    double sum{0};
    float *scores{new float[N]}; // used for scores

    for(int i{0}; i < N-1; i++) {
        getline(my_file2, file_line);
        data_array[i] = file_line;
        scores[i] = splicing(file_line,0,3);
        sum = sum + scores[i];
    }
    // casting an int into a double for increased precision
    double N_2 = static_cast<double>(N);
    mean = 1/N_2 * sum;
    sum = 0;

    for(int i{0}; i < N-1; i++) {
        sum = sum + pow(scores[i] - mean,2);
    }
    standard_deviation = pow(1/(N_2-1) * sum ,0.5);
    std_error = standard_deviation/pow(N_2,0.5);
    delete[] data_array;
    

    std::cout << "The mean is: " << mean << std::endl;
    std::cout << "The standard deviation: " << standard_deviation << std::endl;
    std::cout << "The standard deviation error: " << std_error << std::endl;

    return 0;    
}

