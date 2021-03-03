
// PHYS 30762 Programming in C++
// Assignment 2 - week 2
// Tomasz Neska - ID: 10294857
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
#include<sstream>

// structures
struct list_node {
    double mark;
    int unit_code;
    std::string title;
};

// other functions


double calc_mean(std::vector<list_node> data_array) {
    int N = data_array.size();
    double sum{0};
    for (int i{0};i<=N;i++) {
        sum += data_array[i].mark;
    }
    return sum/static_cast<double>(N);
}

double calc_std(std::vector<list_node> data_array, double mean) {
   
    int N = data_array.size();
    double sum{0};
    for (int i{0}; i<=N; i++) {
        sum += pow(data_array[i].mark-mean,2);
    }
    return pow(sum/static_cast<double>(N), 0.5);
}
// c++ does things when you use & cuz yes
void bubble_sort(std::vector<list_node>& array, int type) {
    int size = array.size();
    bool swap{true};
    list_node holder;
 
    if (type==1) {
        while(swap==true) {
            swap = false;
            for(int i{1};i<size;i++) {
                if (array[i-1].title > array[i].title) {
                    holder.mark = array[i-1].mark;
                    holder.unit_code = array[i-1].unit_code;
                    holder.title = array[i-1].title;

                    array[i-1].mark = array[i].mark;
                    array[i-1].unit_code = array[i].unit_code;
                    array[i-1].title = array[i].title;

                    array[i].mark = holder.mark;
                    array[i].unit_code = holder.unit_code;
                    array[i].title = holder.title;
                    swap = true;
                }
            }
        }      
    } else {
         while(swap==true) {
            swap = false;
            for(int i{1};i<size;i++) {
                if (array[i-1].unit_code > array[i].unit_code) {

                    holder.mark = array[i-1].mark;
                    holder.unit_code = array[i-1].unit_code;
                    holder.title = array[i-1].title;

                    array[i-1].mark = array[i].mark;
                    array[i-1].unit_code = array[i].unit_code;
                    array[i-1].title = array[i].title;

                    array[i].mark = holder.mark;
                    array[i].unit_code = holder.unit_code;
                    array[i].title = holder.title;
                    swap = true;
                }
            }
        }       
    }
    return;
}
// Main function
int main() {
    list_node temporary;  
    double calc_mean(std::vector<list_node> data_array);
    double calc_std(std::vector<list_node> data_array, double mean);
    

    std::string data_file_name;
    int number_courses{0};
    std::string file_line;
    // Ask user to enter filename
    data_file_name = "courselist.dat";
    // Open file and check if successful
    std::ifstream course_stream(data_file_name);
    if (!course_stream.good()) {
       std::cout << "The file couldn't be loaded. Try again."<<std::endl;
       return -1;
    }
    // Allocate memory for data 
    std::vector<std::string> full_data; // the unit titles
    // declares the data array
    std::vector<list_node> chosen_data;
    std::vector<list_node> sliced_data;
    
    while(!course_stream.eof()) {
        getline(course_stream,file_line); // counts only non empty lines
        if(file_line.length() != 0) {
            temporary.mark = std::stod(file_line.substr(0,4));
            temporary.unit_code = std::stoi(file_line.substr(5,9));
            temporary.title = file_line.substr(13,file_line.length());


            sliced_data.push_back(temporary);

            full_data.push_back(file_line.substr(5,file_line.length()));
            //scores.push_back(std::stod(file_line.substr(0,4)));
            
            number_courses ++;
        }
    }
    // Close file
    course_stream.close();
    // Print number of courses read in
    std::cout << "The complete data from the file: " << std::endl;
    std::vector<std::string>::iterator vector_begin{full_data.begin()};
    std::vector<std::string>::iterator vector_end{full_data.end()};
    std::vector<std::string>::iterator vector_iterator; // check whether you can run it without matching the type
    for (vector_iterator=vector_begin; vector_iterator<vector_end; ++vector_iterator){
        std::cout << "PHYS "<< *vector_iterator << std::endl;
    }

    
    double mean = calc_mean(sliced_data);
    double standard_deviation{calc_std(sliced_data,mean)};
    double std_error = standard_deviation/(pow(static_cast<double>(number_courses),0.5));

    // Compute mean, standard deviation and  standard error of mean
    std::cout << std::setprecision(3) << "The mean for the full data set is: " << mean << std::endl;
    std::cout << std::setprecision(3) << "The standard deviation is: " << standard_deviation << " +- " << std_error <<std::endl;
    std::cout << std::endl;
    

    int year{0};
    // print out custom range
    std::cout << "Enter the year you want to display: " << std::endl;
    std::cin >> year;
    while (std::cin.fail()) {
        std::cout << "Error 1: The number if incorrect";
        std::cin.clear();
        std::cin.ignore();
        std::cin >> year;
    }
    

    // Choose the data
    int choice;
    std::cout << "Sort by [1]title or by [2]unit_code: ";
    std::cin >> choice;

    std::string temp;
    std::cout << "The data for the selected range";

    std::cout << sliced_data.size() << std::endl;


    for(int i{0}; i<sliced_data.size();i++) {
        if(sliced_data[i].unit_code/ 10000 == year) { 
            chosen_data.push_back(sliced_data[i]);
            std::cout << "PHYS" << std::to_string(sliced_data[i].unit_code) << " " << sliced_data[i].title <<std::endl;
            
        } 
    }
    
    

    // calculate the mean
    mean = calc_mean(chosen_data);
    // calculate the standard deviation
    standard_deviation = calc_std(chosen_data,mean);
    // calculate the standard deviation error
    std_error = standard_deviation/(pow(static_cast<double>(number_courses),0.5));

    
    // sorting the data
    bubble_sort(chosen_data,choice); // pass in a reference. Don't return anything just alter memory

    //print out data
    //using string stream
    std::ostringstream output_stream;

    for(int i{};i<chosen_data.size(); i++) {
        //std::cout << "PHYS" << chosen_data[i].unit_code << " " << chosen_data[i].title << std::endl;
        output_stream << "PHYS" << chosen_data[i].unit_code << " " << chosen_data[i].title;
        std::string output_entry{output_stream.str()};
        std::cout << output_entry << std::endl;
        output_stream.str("");
    }
    
    std::cout << std::setprecision(3) << "The mean for the full data set is: " << mean << std::endl;
    std::cout << std::setprecision(3) << "The standard deviation is: " << standard_deviation << " +- " << std_error <<std::endl;
    std::cout << std::endl;

    return 0;
}

