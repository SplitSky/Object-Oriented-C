// PHYS 30762 Programming in C++
// Assignment 5
// Tomasz Neska - ID: 10294857
// Matrix Determinants and inverses

#include<iostream>
#include<cmath>
#include<vector>
#include<string>

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
    std::vector<double> data;
public:
    // constructor default
    matrix() = default;
    // parameter constructor
    matrix(int row, int col, std::vector<double> data): row{row}, col{col}, data{data} {}
    // destructor
    ~matrix(){
        std::cout<<"bye"<<std::endl;
        delete data;
    }
    int get_row(){return this->row;} 
    int get_col(){return this->col;}

    matrix operator+(const matrix &numbers) const {
        if ((this->row == numbers.row) && (this->col == numbers.col)) {
            std::vector<double> data_added;
            for (int i{0}; i<this->row*this->col ;i++) {
                data_added.push_back(this->data[i] + numbers.data[i]);
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
            std::vector<double> data_added;
            for (int i{0}; i<this->row*this->col ;i++) {
                data_added.push_back(this->data[i] - numbers.data[i]);
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

        if (this->row == numbers.col) {
            double sum;
            std::vector<double> data_multiplied;
            for (int j{0}; j<numbers.row;j++) {
                for (int i{0}; i < this->col; i++) {
                    sum = 0;
                    for (int k{0};k < this->row; k++) {
                        sum += this->data[(k-1)+(j-1)*this->col] * numbers.data[(i-1)+(k-1)*numbers.col];
                    }
                    data_multiplied.push_back(sum); // adds the entry to the result array
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

};

std::ostream& operator<<(std::ostream& os, const matrix &numbers) {
    std::string temp;

    // modify the temp string by using the matrix object
    
    os << temp;
    return os;
}

std::istream& operator>>(std::istream& os, matrix &number) {
    std::string input;
    os >> input;
    std::string data;
}

int main() {
    std::cout.precision(3);

    int row{2};
    int col{2};
    std::vector<std::vector<int>> data = {{1,0},{0,1}};

    matrix a(row, col, data);
    
    

    return 0;
}
