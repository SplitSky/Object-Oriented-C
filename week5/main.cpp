// PHYS 30762 Programming in C++
// Assignment 5
// Tomasz Neska - ID: 10294857
// Matrix Determinants and inverses

#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<array>
#include<iterator>
#include<cstring>
// Things to do
// The class:
// 1. Contain no. of rows, no. of columns and a pointer to the matrix data (type double)
// 2. Constructor using dynamic memory allocation
// 3. Store data in a one dimensional array. For a matrix by m x n. The location is given by (j-1) + (i-1)*n
// 4. the destructor should delete dynamically allocated memory
// 5. Assignment operator and copy constructor functions would perform deep copies of data
// 6. Recursive calculation of a determinant:
// 7. 

class matrix {
private:
    int row;
    int col;
    double *data;
public:
    // constructor default
    matrix() {

    };
    // parameter constructor
    matrix(int row, int col, double data_in[]): row{row}, col{col} {
        this->data = new double[row*col];
        for (int i{0}; i<row*col; i++) {
            this->data[i] = data_in[i];
        }
    }
    // destructor
    ~matrix(){
        std::cout<<"bye"<<std::endl;
        delete data;
    }
    int get_row(){return this->row;} 
    int get_col(){return this->col;}

    void set_row(int row){this->row=row;}
    void set_col(int col){this->col=col;}
    void set_data(double data){this->data=&data;}

    matrix operator+(const matrix &numbers) const {
        if ((this->row == numbers.row) && (this->col == numbers.col)) {
            double *data_added {new double[this->row*this->col]};
            for (int i{0}; i<this->row*this->col ;i++) {
                data_added[i] = (this->data[i] + numbers.data[i]);
            }
            matrix temp(this->row, this->col, data_added);
            return temp;
        } else {
            matrix temp;
            std::cout << "The dimensions don't match" << std::endl;
            return temp;
        }
    }

    matrix operator-(const matrix &numbers) const {
        if ((this->row == numbers.row) && (this->col == numbers.col)) {
            double *data_added {new double[this->row*this->col]};
            for (int i{0}; i<this->row*this->col ;i++) {
                data_added[i] = (this->data[i] - numbers.data[i]);
            }
            matrix temp(this->row, this->col, data_added);
            return temp;
        } else {
            matrix temp;
            std::cout << "The dimensions don't match" << std::endl;
            return temp;
        }
    }

    matrix operator*(const matrix &numbers) const {
        // this = a
        // numbers = b
        if (this->row == numbers.col) {
            double sum;
            double *data_multiplied = new double[this->row*numbers.col];

            for (int j{0}; j<numbers.col;j++) {
                for (int i{0}; i < this->row; i++) {
                    sum = 0;
                    for (int k{0};k < this->col; k++) {
                        sum += this->data[(k-1)+(i-1)*this->col] * numbers.data[(j-1)+(k-1)*numbers.col];
                    }
                    data_multiplied[(j-1)+this->row*(i-1)] = sum; // adds the entry to the result array
                }
            }
            matrix temp(this->row, this->col, data_multiplied);
            return temp;
        } else {
            matrix temp;
            std::cout << "The dimensions don't match" << std::endl;
            return temp;
        }
    }

    std::string show_data() const {
        std::string temp[this->row];
        std::string temp_string;
        for (int i{1}; i <= this->row; i++) {
            temp_string += "[";
            for (int j{1}; j <= this->col; j++) {
                temp_string += " ";
                temp_string += std::to_string(this->data[(j-1)+this->col*(i-1)]) + ", ";
            }
            temp_string = temp_string.substr(0,temp_string.size()-2);
            temp_string += "], ";
        }
        temp_string = temp_string.substr(0,temp_string.size()-2);
    return temp_string;
    }
};



std::ostream& operator<<(std::ostream& os, const matrix &numbers) {
    // modify the temp string by using the matrix object
    os << "Printing the matrix:" << std::endl;
    os << numbers.show_data() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& os, matrix &numbers) {
    std::string input;
    os >> input;
    char char_array[input.size()-1];
    std::strcpy(char_array, input.c_str());
    

    numbers.set_row(stoi(char_array[0]));
    numbers.set_col(stoi(char_array[2]));
    std::vector<double> data;
    double temp_number;
    std::string temp_string;

    int i{5};
    bool number_start;

    while (i != input.length()) {
        number_start = true;
        temp_string = "";
        while (number_start) {
            // once its a number
            // convert it into a double
            // assing to some vector for storage
            
            temp_string += input[i]; // assign an entry in the string
            if (input[i]==',') {
                temp_number = stoi(temp_string);
                data.push_back(temp_number);
            } else  if (input[i] ==']') {number_start=false;}
            i++;
        }
    }

    // [134.322,2,3];[1,2,3];[1,2,3]

    return os;
}

int main() {
    //std::cout.precision(3);

    //int row{2};
    //int col{2};
    //double data[4] = {1,0,0,1};
    //double data2[4] = {2,0,0,2};
    //matrix a(row, col, data);
    //matrix b(row, col, data2);
    //matrix c = a+b; 

    std::string input = "3,1,{1,0,0,1,1,0}"; // the format is: row, column {data}
    // the maximum size is 9x9.
    //std::cout << "potato";

    matrix a;
    std::cin >> a;


    return 0;
}
