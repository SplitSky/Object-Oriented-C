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
    friend std::ostream& operator<<(std::ostream &os, matrix &numbers);
    friend std::ifstream& operator>>(std::ifstream &os, matrix &numbers);
    
    private:
        int row;
        int col;
        double *data;

        double calc_det(int row, std::vector<double> matrix) {
            // takes in array, mxn
            if (row == 2) { // col must also be 2 because its a square
                return matrix[0]*matrix[3] - matrix[1]*matrix[2]; // base case
            } else {
                double determinant{0};
                for (int j{1}; j<=row; j++) {
                    determinant += pow(-1, 1+j) * matrix[j-1] * calc_det(row-1, splice_matrix(1,j,matrix));
                }
                return determinant;
            }
        }

        std::vector<double> splice_matrix(int i_pivot, int j_pivot, std::vector<double> matrix) {
            // no need to invlude row and column as it always returns a matrix one smaller in each dimension
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
        matrix() {
            this->data = nullptr;
            this->row = 0;
            this->col = 0;
        }
        // parameter constructor
        matrix(int row, int col, double data_in[]): row{row}, col{col} {
            this->data = new double[row*col];
            for (int i{0}; i<row*col; i++) {
                this->data[i] = data_in[i];
            }
        }
        // destructor
        ~matrix(){
            for (size_t i{0}; i< row*col ; i++) {std::cout << "The data: " << *(this->data+i) << std::endl;}
            //this->data = nullptr;
            this->data = nullptr;
            delete[] this->data;
        }

        int get_row(){return this->row;}
        int get_col(){return this->col;}

        void set_row(int row){this->row=row;}
        void set_col(int col){this->col=col;}
        void set_data(double* data_2, size_t size){
            this->data = new double[size];
            for (size_t i{0}; i< size; i++) {
                this->data[i] = data_2[i];
                // copies data from one pointer location to the other
            }
            return;        
        }

        matrix operator+(matrix &numbers) const {
            if ((this->row == numbers.row) && (this->col == numbers.col)) {
                matrix temp; // defines object

                std::vector<double> data_added;
                for (int i{0}; i<this->row*this->col ;i++) {
                    data_added.push_back(this->data[i] + numbers.data[i]);
                }

                
                double* data_assigned = new double[this->row*this->col];
                std::copy(data_added.begin(), data_added.end(), data_assigned);
                //matrix temp(this->row, this->col, data_assigned);
                //delete[] data_assigned;
                temp.set_col(numbers.get_col());
                temp.set_row(numbers.get_row());
                temp.set_data(data_assigned, data_added.size());
                delete[] data_assigned;
                return temp;
            } else {
                matrix temp;
                std::cout << "The dimensions don't match" << std::endl;
                return temp;
            }
        }

        matrix operator-(matrix &numbers) const {
            if ((this->row == numbers.row) && (this->col == numbers.col)) {
                matrix temp; // defines object

                std::vector<double> data_added;
                for (int i{0}; i<this->row*this->col ;i++) {
                    data_added.push_back(this->data[i] - numbers.data[i]);
                }

                
                double* data_assigned = new double[this->row*this->col];
                std::copy(data_added.begin(), data_added.end(), data_assigned);
                //matrix temp(this->row, this->col, data_assigned);
                //delete[] data_assigned;
                temp.set_col(numbers.get_col());
                temp.set_row(numbers.get_row());
                temp.set_data(data_assigned, data_added.size());
                delete[] data_assigned;
                return temp;
            } else {
                matrix temp;
                std::cout << "The dimensions don't match" << std::endl;
                return temp;
            }
        }

        matrix operator*(matrix &numbers) {
            if (this->row == numbers.col) {
                double sum{0};
                std::vector<double> data_multiplied;
                //double *data_multiplied = new double[this->row*numbers.col];

                for (int j{1}; j<=numbers.col;j++) {
                    for (int i{1}; i <= this->row; i++) {
                        sum = 0;
                        for (int k{1};k <= this->col; k++) {
                            sum += this->data[(k-1)+(i-1)*this->col] * numbers.data[(j-1)+(k-1)*numbers.col];
                        }
                        data_multiplied[(j-1)+this->row*(i-1)] = sum; // adds the entry to the result array
                    }
                }
                //matrix temp(this->row, numbers->col, data_multiplied);

                matrix temp;
                double* data_assigned = new double[this->row*this->col];
                std::copy(data_multiplied.begin(), data_multiplied.end(), data_assigned);
                //matrix temp(this->row, this->col, data_assigned);
                //delete[] data_assigned;
                temp.set_col(numbers.get_col());
                temp.set_row(this->get_row());
                temp.set_data(data_assigned, data_multiplied.size());
                delete[] data_assigned;
                return temp;

            } else {
                matrix temp;
                std::cout << "The dimensions don't match" << std::endl;
                return temp;
            }
        }

        matrix operator=(matrix &numbers) {
            if (&numbers == this) {return *this;} // no self assignment
            
            int row_2 = row;int col_2 = col;
            delete[] data; 
            data = nullptr;
            col = 0;row = 0;
            col = numbers.col;
            row = numbers.row;
            if (row*col>0) {
                data = new double[row*col];
                for (size_t i{}; i<col*row; i++) {data[i]=numbers.data[i];}
            }
            return *this;
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
            return this->calc_det(this->row, temp_vector); // use private function as a helper
        }
        
        void slice_matrix2(int i_pivot, int j_pivot) {
            std::vector<double> new_data;
            for (size_t i{0}; i<this->row*this->col; i++) {
                new_data.push_back(this->data[i]);
            }
            
            this->row = this->row - 1;
            this->col = this->col - 1;
            delete[] this->data;
            this->data = new double[this->row * this->col];
            // purges and resets the data variables

            new_data = this->splice_matrix(i_pivot, j_pivot, new_data); // uses the helper function to splice the vector
            std::copy(new_data.begin(), new_data.end(), this->data);// copies the data into the pointer location
            // copies the array into a memory location that doesn't disappear when it goes out of scope.
            return;
        }
};



std::ostream& operator<<(std::ostream& os, matrix &numbers) {
    os << "Printing the matrix:" << std::endl;
    std::string temp[numbers.get_row()];
    std::string temp_string;
    for (int i{1}; i <= numbers.get_row(); i++) {
        temp_string += "[";
        for (int j{1}; j <= numbers.get_col(); j++) {
            temp_string += " ";
            temp_string += std::to_string(numbers.data[(j-1)+numbers.get_col()*(i-1)]) + ", ";
        }
        temp_string = temp_string.substr(0,temp_string.size()-2);
        temp_string += "]";
        os << temp_string << std::endl;
        temp_string = "";
    }
    //temp_string = temp_string.substr(0,temp_string.size()-2);
    //os << numbers.show_data() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& os, matrix &numbers) {
    //std::string input = "2,2,{1,0,0,1}";
    std::cout << "Enter the number of rows: " << std::endl;
    std::string input;
    os >> input; // gets the input
    numbers.set_row(std::stoi(input));
    
    input = "";
    std::cout << "Enter the number of columns: " << std::endl;
    os >> input;
    numbers.set_col(std::stoi(input));
    
    std::cout << "Enter the matrix in form: {a,b...}: " << std::endl;
    input = "";
    os >> input;
    std::vector<double> data;
    double temp_number;
    std::string temp_string;
    int i{1};
    std::cout << "the input: " << input << std::endl; 

    bool number_start;
    while (i != input.length()) {
        number_start = true;
        temp_string = "";
        while (number_start) {
            if (input[i]==',') {
                temp_number = std::stod(temp_string);
                data.push_back(temp_number);
                i++;
                break;
            } else if (input[i] =='}') {
                number_start=false;
                temp_number = stold(temp_string);
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
    numbers.set_data(&new_data[0],data.size()); // assigns the data onto the matrix
    return os;
}


int main() {
    int row{2};
    int col{2};
    double data[4] = {1,2,3,4};
    double data2[4] = {2,3,4,5};
    matrix matrix1(row, col, data);
    matrix matrix2(row, col, data2);
    matrix matrix3 = matrix1+matrix2;

    //matrix matrix4 = matrix1-matrix2;
    //matrix matrix5 = matrix1*matrix2;
    //double data3[9] = {1,8,7,1,5,3,1,8,4}; // the determinant is 9
    //double data4[36] = {1,2,5,4,8,15,4,5,2,6,4,2,3,8,7,4,5,6,2,1,5,5,5,5,4,8,8,7,5,4,2,1,5,6,3,4}; // determinant is 1464
    //matrix matrix6{3,3,data3};
    //matrix matrix7{6,6,data4};

    //std::cout << "Attempting to multiply the matrices with incorrect sizes" << std::endl;
    //matrix matrix8 = matrix6*matrix7;

    //double det_a{matrix1.find_determinant()};
    //double det_b{matrix6.find_determinant()};
    //double det_c{matrix7.find_determinant()};

    //matrix matrix9;
    //std::cin >> matrix9; // the input testing

    //printing all the matrices
    std::cout << "matrix A: " << matrix1 << std::endl;
    std::cout << "matrix B: " << matrix2 << std::endl;
    std::cout << "matrix C=A+B: " << matrix3 << std::endl;
    
    //matrix1 = matrix2; // modifies the original matrix
    //std::cout << "matrix C after A was overwritten with B: " << matrix3;
    //std::cout << "matrix A: " <<matrix1 << std::endl;
    //std::cout << "matrix B: " << matrix2 << std::endl;

    
    //std::cout << "matric D=A-B: " << matrix4 << std::endl;
    //std::cout << "matrix E=A*B: " << matrix5 << std::endl;
    //std::cout << "3x3 matrix: " << matrix6 << std::endl;
    //std::cout << "6x6 matrix: " << matrix7 << std::endl;
    //std::cout << "the input matrix: " << matrix9 << std::endl;
    //std::cout << "Det 2x2: " << det_a << std::endl;
    //std::cout << "Det 3x3: " << det_b << std::endl;
    //std::cout << "Det 4x4: " << det_c << std::endl; 

    // the demonstration of the "member function that returns a matrix with ith and jth row deleted"
    // is a part of the determinant calculation
    // This function is modified and repeated under a name slice_matrix2.
    // Operation is demonstrated below
    //matrix6.slice_matrix2(1,1);
    //std::cout << "Slice the 3x3 matrix by removing 1st column and 1st row." << std::endl;
    //std::cout << "Printing the sliced matrix: "<< matrix6 << std::endl;

    // showing memory assignment is correct
    //matrix1 = matrix2;
    //std::cout << "Matrix A overwritten by B: " << matrix1 << std::endl;
    //std::cout << "Matrix B: " << matrix2 << std::endl;
    //std::cout << "Matrix C is unchanged: " << matrix3 << std::endl;


    return 0;
}
