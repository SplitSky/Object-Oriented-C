
// PHYS 30762 Programming in C++
// Assignment 2

// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file

// Skeleton code - assessed components are missing

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>

// Functions to compute mean and standard deviation

// Main function

int main() {
  char data_file[100];

  // Ask user to enter number of courses
  // Or determine in another way
  int number_courses{};

  // Ask user to enter filename
  std::cout<<"Enter data filename: ";
  std::cin>>data_file;

  // Open file and check if successful
  std::fstream course_stream(data_file);

  // Allocate memory for data 

  // Read data from file
  for(int i{};i<Ndata;i++) {

    }

  // Close file
  course_stream.close();

  // Print number of courses read in

  // Compute mean, standard deviation and  standard error of mean

  // Free memory


  return 0;
}

