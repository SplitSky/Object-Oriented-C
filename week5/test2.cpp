// PHYS 30762 Programming in C++
// Assignment 5
// Tomasz Neska - ID: 10294857
// Matrix Determinants and inverses

#include <fstream>
#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<array>
#include<iterator>
#include<cstring>

class matrix {
    friend std::ostream& operator<<(std::ostream &os, const matrix &numbers);
    friend std::ifstream& operator>>(std::ifstream &os, matrix &numbers);
    
    private:
        int row;
        int col;
        double *data;

        double calc_det(int row, std::vector<double> matrix) {
            // takes in array, mxn
            if (row == 2) { // col must also be 2 because its a square
                return matrix[0]*matrix[3] - matrix[1]*matrix[2]; // returns the base case of 2x2 determinant
            } else {
                double determinant{0};
                for (int j{1}; j<=row; j++) {
                    determinant += pow(-1, 1+j) * matrix[j-1] * calc_det(row-1, splice_matrix(1,j,matrix)); // recursive calculation of minors
                }
                return determinant;
            }
        }

        std::vector<double> splice_matrix(int i_pivot, int j_pivot, std::vector<double> matrix) {
            // this function slices the matrix into a smaller one
            std::vector<double> new_matrix = {};
            int col = pow(matrix.size(), 0.5);
            for (int i{1}; i<=col; i++) {
                for (int j{1}; j<=col; j++) {
                    if ((i != i_pivot) && (j != j_pivot)) {
                        new_matrix.push_back(matrix[(i-1)*col + (j-1)]);
                    }
                }
            }

            return new_matrix;
        }

    public:
        // constructor default
        matrix() = default;
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
            // add the deletion of the dynamical data.
       }

        int get_row(){return this->row;}
        int get_col(){return this->col;}

        void set_row(int row){this->row=row;}
        void set_col(int col){this->col=col;}
        void set_data(double* data){this->data=data;}

        matrix operator+(const matrix &numbers) const {
            if ((this->row == numbers.row) && (this->col == numbers.col)) {
                std::vector<double> data_added;
                for (int i{0}; i<this->row*this->col ;i++) {
                    data_added.push_back(this->data[i] + numbers.data[i]);
                }
                double* data_assigned = new double[this->row*this->col];
                std::copy(data_added.begin(), data_added.end(), data_assigned);
                matrix temp(this->row, this->col, data_assigned);
                
                delete[] data_assigned;

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
                double* data_assigned = new double[this->row*this->col];
                std::copy(data_added.begin(), data_added.end(), data_assigned);
                matrix temp(this->row, this->col, data_assigned);
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
                double *data_multiplied = new double[this->row*numbers.col];

                for (int j{1}; j<=numbers.col;j++) {
                    for (int i{1}; i <= this->row; i++) {
                        sum = 0;
                        for (int k{1};k <= this->col; k++) {
                            sum += this->data[(k-1)+(i-1)*this->col] * numbers.data[(j-1)+(k-1)*numbers.col];
                            std::cout << "i=" << i << " j=" << j << " k=" << k << std::endl;
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

        double find_determinant() {
            std::vector<double> temp_vector;
            temp_vector.assign(this->data, this->data+(this->row*this->col));// assigns an array to a vector

            std::cout << "Printing the initial matrix" << std::endl;
            std::cout << this->show_data() << std::endl;
            return this->calc_det(this->row, temp_vector); // use private function as a helper
        }


};

std::ostream& operator<<(std::ostream& os, const matrix &numbers) {
    os << "Printing the matrix:" << std::endl;
    os << numbers.show_data() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& os, matrix &numbers) {
    std::string input;
    os >> input;

    numbers.set_row(int(input[0])); // may be ASCII
    std::cout << "The value may be ASCII: " << numbers.get_row() << std::endl;
    numbers.set_col(int(input[2]));
    std::vector<double> data;
    double temp_number;
    std::string temp_string;
    int i{5};
    

    bool number_start;
    while (i != input.length()) {
        number_start = true;
        temp_string = "";
        while (number_start) {
            if (input[i]==',') {
                temp_number = stod(temp_string);
                data.push_back(temp_number);
                i++;
                break;
            } else if (input[i] ==']') {
                number_start=false;
                temp_number = stod(temp_string);
                data.push_back(temp_number);
            } else {
                temp_string += input[i];
            }
            i++;
        }
    }
    
    double* new_data = new double[data.size()];
    std::copy(data.begin(), data.end(), new_data); 
    // copies the array into a memory location that doesn't disappear when it goes out of scope.
    
    // convert a vector into double array
    numbers.set_data(&new_data[0]); // make sure this actually holds the data
    return os;
}


int main() {
    std::cout.precision(3);

    int row{2};
    int col{2};
    double data[4] = {1,2,3,4};
    double data2[4] = {2,3,4,5};
    matrix a(row, col, data);
    matrix b(row, col, data2);

    //double data3[9] = {1,8,7,1,5,3,1,8,4};
    //double data4[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    double data5[36] = {14,7,6,9,23,6,7,9,2,4,8,9,4,5,2,4,6,2,2,2,2,4,5,6,78,8,9,9,65,4,2,4,5,6,2,3};
    matrix f{6,6,data5};
    //matrix g{4,4,data4};

    //double det_a{a.find_determinant()};
    double det_b{f.find_determinant()};
    //double det_c{g.find_determinant()};


    // printing all the matrices
    //std::cout << "matrix A: " << a << std::endl;
    //std::cout << "matrix B: " << b << std::endl;
    //std::cout << "matrix C: " << c << std::endl;
    //std::cout << "matric D: " << d << std::endl;
    //std::cout << "matrix E: " << e << std::endl;
    //std::cout << "Det A " << det_a << std::endl;
    std::cout << "Det 6x6 " << det_b << std::endl;
    //std::cout << "Det 4x4 " << det_c << std::endl; 


    //std::string input = "3,1,{1,0,0,1,1,0}"; // the format is: row, column {data}
    // the maximum size is 9x9.
    //std::cout << "potato";

    //matrix a;
    //std::cin >> a;


    return 0;
}
