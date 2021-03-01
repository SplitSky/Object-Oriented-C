
// PHYS 30762 Programming in C++
// Assignment 2

// Program to compute mean, standard deviation and standard
// error of the a set of courses. Data is read from file

// Skeleton code - assessed components are missing

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<tuple>
#include<vector>
#include<string>
#include<algorithm>
// Functions to compute mean and standard deviation
double calculate_mean(std::string array) {
    double mean;
    double standard_deviation;
    double std_error;

    // the calculation depends on the format of the array
    double return_array[3];
    return_array[0] = mean;
    return_array[1] = standard_deviation;
    return_array[2] = std_error;
    
    return mean; 
} 

int count_courses(std::string file_name){
    int N{0};
    std::string file_line;
    std::ifstream my_file(file_name);

    // count the number of lines in the file
    while(!my_file.eof()){
        getline(my_file,file_line);
        N++;
    }

    my_file.close();
    return N;
}

// Main function
int main() {
    std::string data_file_name;
    bool validation = false;
    int number_courses{0};
    std::string file_line;
    // Ask user to enter filename
    std::cout<<"Enter data filename: ";
    std::cin>>data_file_name;
    // Open file and check if successful
    std::ifstream course_stream(data_file_name);
    
    while (!validation) {
        std::cout << "The file couldn't be loaded. Try again.";
        std::cin>>data_file_name;
        std::ifstream course_stream(data_file_name); 
        validation = course_stream.good();
    }

    //number_courses = count_courses(data_file_name); // may not be needed

    // Allocate memory for data 
    //std::string *full_data{new std::vector<std::string>(number_courses)};
    std::vector<std::string> full_data; // suppose it works like a python list
    // declares the data array

    // Read data from file
    for(int i{0};i<number_courses;i++) {
        getline(course_stream,file_line);
        full_data.push_back(file_line);
        number_courses ++;
    }

    // Close file
    course_stream.close();
    
    // testing start
    std::cout << "The file array printing" << std::endl;
    std::cout << full_data[0] << std::endl;
    // testing end

    // Print number of courses read in
    std::vector<std::string>::iterator vector_begin{full_data.begin()};
    std::vector<std::string>::iterator vector_end{full_data.end()};
    std::vector<std::string>::iterator vector_iterator; // check whether you can run it without matching the type
    for (vector_iterator = vector_begin; vector_iterator<vector_end; ++vector_iterator) std::cout << *vector_iterator << std::endl;
    // Compute mean, standard deviation and  standard error of mean

    // Free memory
    

    return 0;
}

