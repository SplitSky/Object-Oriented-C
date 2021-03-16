// PHYS 30762 Programming in C++
// Assignment 5 - skeleton code
// Tomasz Neska
// Class for complex numbers

#include<iostream>
#include<cmath>

class complex
{
  // Make function to overload operator<< a friend
  friend ostream & operator<<(ostream &os, const complex &z);
private:
  double re,im;
public:
  // Constructors & destructor
  complex(){re=im=0;}
  complex(double real_part, double im_part){re=real_part; im=im_part;}
  ~complex(){}

  // Return real component

  // Return imaginary component

  // Return modulus

  // Return argument

  // Return complex conjugate

  // Overload + operator for addition 

  // Overload - operator for subtraction

  // Overload * operator for multiplication, z1*z2

  // Overload / operator for division, z1/z2

};

// Function to overload << operator for complex numbers

int main()
{  
  cout.precision(3);

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
