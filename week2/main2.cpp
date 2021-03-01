
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

// structures
struct list_node {
    double mark;
    int unit_code;
    std::string title;
    int rank;
};

// other functions
bool compare_two_nodes_title(list_node a, list_node b) {
    return a.title > b.title;
}

bool compare_two_nodes_code(list_node a, list_node b) {
    return a.unit_code > b.unit_code;
}

void compute_ranks(list_node a[], int n, int data_size,bool type) {
    if (type) {
        std::sort(a, a + data_size, compare_two_nodes_title);    
    } else {
        std::sort(a, a + data_size, compare_two_nodes_code);
    }

    for (int i{0}; i<n; i++) {
        a[i].rank = i + 1;
    }
    return; // be weary of using the variable or pointer array
}



double calc_mean(std::vector<double> data_array,int N) {
    double sum{0};
    for (int i{0};i<=N;i++) {
        sum += data_array[i];
    }
    return sum/static_cast<double>(N);
}

double calc_std(std::vector<double> data_array, int N, double mean) {
    double sum{0};
    for (int i{0}; i<=N; i++) {
        sum += pow(data_array[i]-mean,2);
    }
    return pow(sum/static_cast<double>(N), 0.5);
}

// Main function
int main() {
    double calc_mean(std::vector<double> data_array, int N);
    double calc_std(std::vector<double> data_array, int N, double mean);

    std::string data_file_name;
    int number_courses{0};
    std::string file_line;
    // Ask user to enter filename
    //std::cout<<"Enter data filename: ";
    //std::cin>>data_file_name;
    data_file_name = "courselist.dat";
    // Open file and check if successful
    std::ifstream course_stream(data_file_name);
    if (!course_stream.good()) {
       std::cout << "The file couldn't be loaded. Try again."<<std::endl;
       return -1;
    }
    // Allocate memory for data 
    //std::string *full_data{new std::vector<std::string>(number_courses)};
    std::vector<std::string> full_data; // the unit titles
    std::vector<double> scores; //just the numerical scores
    // declares the data array

    while(!course_stream.eof()) {
        getline(course_stream,file_line); // counts only non empty lines
        if(file_line.length() != 0) {
            full_data.push_back(file_line.substr(5,file_line.length()));
            scores.push_back(std::stod(file_line.substr(0,4)));
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

    std::cout << "The data from the second array: " << std::endl;
    std::vector<double>::iterator vector_begin2{scores.begin()};
    std::vector<double>::iterator vector_end2{scores.end()};
    std::vector<double>::iterator vector_iterator2;

    for (vector_iterator2=vector_begin2; vector_iterator2<vector_end2; ++vector_iterator2){
        std::cout << *vector_iterator2 << std::endl;
    }

    //double sum{0};
    //for(int i{0};i<=number_courses;i++) {
    //    sum += scores[i];
    //}
    double mean = calc_mean(scores, number_courses);
    //double mean = 1/static_cast<double>(number_courses) * sum;
    //sum = 0;
    //for(int i{0};i<=number_courses;i++) {
    //    sum += pow(scores[i] - mean, 2);
    //}
    //double standard_deviation{pow(1/static_cast<double>(number_courses) * sum,0.5)};
    double standard_deviation{calc_std(scores,number_courses,mean)};
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

    while (year != '1' || year !='2' || year !='3' || year !='4') {
        std::cout << "Error 2: The number if incorrect";
        std::cin.clear();
        std::cin.ignore();
        std::cin >> year;
    }

    // assign a new array
    std::vector<std::string> sliced_scores;
    std::string temp;
    for(int i{};i<=number_courses;i++) {
        // test = std::to_string(score[i])[0]
        //if(full_data[i][0]==year) {
            // scrape the data you want
        //    temp = std::to_string(scores[i]) + " " + full_data[i];
        //    sliced_scores.push_back(temp); /// make sure you develop a nested system {[score, code, title] ,[score, code, title] ,[etc] } then
            // sort the rest of it using the algorithm from above
        std::cout << full_data[i][0] << std::endl;
        //}
    }

    return 0;

    // things to do
    // use the iterator with the printing of all information
    // print out mean and all other calculations for the selection
    // sort the list by the title or course code
    // keep 3 differnt components as differnt arrays
    // when you are about to print out concatenate the strings together into a single array and use an iterator.
}

