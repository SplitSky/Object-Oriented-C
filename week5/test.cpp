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

double* glue_matrix(int i_pivot, int j_pivot, double* matrix, int row, int col) {
    double* new_matrix = new double[matrix.size()];
    std::copy(matrix.begin(), matrix.end(), new_matrix); 
    // make sure that matrix is a double array pointer
}

double calc_det(double* matrix, int i_min, int i_max, int j_min, int j_max) {
    // doesn't validate that the matrix is square.
    if ((j_max - j_min == 1) && (i_max - i_min == 1)) {
        // the matrix is a 2x2 hence calculate the determinant;
        return matrix[0] * matrix[3] - matrix[1] * matrix[2];
    } else {
        // it's not a 2x2 matrix
        double determinant;
        int i{1};
        for (int j{j_min}; j<j_max; j++) {
            determinant += pow(-1,i+j) * matrix[(i-1)*(i_max-i_min) + (j-1)] * calc_det(matrix, i_min+1, i_max, )
        }
    }
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
    double mat = {1,2,3,4};


    std::string = "3,1,{1,0,0,1,1,0}"; // the format is: row, column {data}
    // the maximum size is 9x9.


    matrix a;
    std::cin >> a;


    return 0;
}
