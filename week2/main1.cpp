
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
	int N{0};
	std::string file_line;
	std::ifstream my_file("courselist.dat");
	if (!my_file.good()) {
        std::cout << "The file couldn't be loaded";
        return -1;
    } else {
		// count the number of lines in the file
		while(!my_file.eof()) {
			getline(my_file,file_line);
			std::cout << "File Line: " << file_line << std::endl;
			N++;
		}
		my_file.close();
			
	}

	std::ifstream my_file("courselist.dat");
	
	//float *data_array{new float[N]};
	std::string *data_array{new std::string[N]};
	std::cout << data_array;
	
	for(int i=0;i<N;i++) {
		getline(my_file,file_line);
		data_array[i] = file_line;
		
		std::cout << "File Line: " << file_line << std::endl;
		std::cout << "Data content: " << data_array << std::endl;
		std::cout << i << std::endl;
		
		
		
	}
    // Ask user to enter number of courses
    // Or determine in another way
    //int number_courses{};
    // Ask user to enter filename
    //std::cout<<"Enter data filename: ";
    //std::cin>>data_file;
    // Open file and check if successful
    //std::fstream course_stream(data_file);
	delete[] data_array;
    return 0;
	my_file.close();
	
	
	////
	
	// open file first time
	//
}

