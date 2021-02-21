
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

// Functions to compute mean and standard deviation

// Main function

int main() {
    // import the file
    std::fstream my_file("courselist.dat");
    if (!my_file.good()) {
        // print out error message
        std::cout << "The file couldn't be loaded";
        return -1;
    }

    bool test2{};
    char data_array[100];
    my_file>>data_array;
    my_file>>test2;
    std::cout << data_array << std::endl;
    std::cout << test2;
    
    // Ask user to enter number of courses
    // Or determine in another way
    //int number_courses{};
    // Ask user to enter filename
    //std::cout<<"Enter data filename: ";
    //std::cin>>data_file;
    // Open file and check if successful
    //std::fstream course_stream(data_file);
    return 0;
}

