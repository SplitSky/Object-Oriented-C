// PHYS 30762 Programming in C++
// Assignment 5 - skeleton code
// Tomasz Neska
// Class for complex numbers
#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>


class complex
{
    // Make function to overload operator<< a friend
    friend std::ostream & operator<<(std::ostream &os, const complex &z);
    private:
    double re,im;
    const double pi{M_PI};
    public:
    // Constructors & destructor
    complex(){re=im=0;}
    complex(double real_part, double im_part){re=real_part; im=im_part;}
    ~complex(){}

    // Return real component
    double real() {return this->re;}
    // Return imaginary component
    double imaginary() {return this->im;}

    // Return modulus
    double modulus() {return pow(this->re*this->re + this->im*this->im,0.5);}
    // Return argument
    double argument() {
        if (this->re == 0) {
            return this->pi;
        } else {
            return std::atan(this->im / this->re);
        }        
    }
    // Return complex conjugate
    complex conjugate() {
        complex conjugate{this->re, this->im};
        return conjugate;
    }
    // Overload + operator for addition 
    complex operator+(const complex &number) const {
        complex temp{number.re + this->re, number.im + this->im};
        return temp;
    }
    // Overload - operator for subtraction
    complex operator-(const complex &number) const {
        complex temp{number.re - this->re, number.im - this->im};
        return temp;
    }
    // Overload * operator for multiplication, z1*z2
    complex operator*(const complex &number) const {
        //complex temp{number.re*this->re - number.im*this->im, number.im - this->im};
        // 
        return temp;
    }
    // Overload / operator for division, z1/z2

};

// Function to overload << operator for complex numbers

int main()
{  
    std::cout.precision(3);

    // Create two complex numbers
    complex a{3,4};
    complex b{1,-2};

    // Get real and imaginary components, modulus and argument

    // Get conjugates

    // Get sum, difference, product and quotient of a and b

    // Print out results, also demonstrating use of overloaded operator<<

    // Show results of overloading arithmetic operators

    return 0;
}
