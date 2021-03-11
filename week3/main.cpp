
// PHYS 30762 Programming in C++
// Tomasz Neska
// Assignment 4
// Simple demonstration of a C++ class
//
// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]
#include<iostream>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
private:
    std::string hubble_type;
    double redshift;
    double total_mass;
    double stellar_mass_fraction;


public:
    // Constructors
    galaxy() = default;
    // Parameter Constructor
    galaxy(double redshift, double total_mass, double stellar_mass_fraction, std::string hubble_type) : redshift{redshift}, total_mass{total_mass}, stellar_mass_fraction{stellar_mass_fraction}, hubble_type{hubble_type} {}
    // Destructor
    ~galaxy(){std::cout<<"Destroying Galaxy" << std::endl;}
    // Return stellar mass (M_* = f_* x M_tot)
    double stellar_mass() {return stellar_mass_fraction * total_mass;}
    // Change galaxy's Hubble type
    void change_type(std::string new_type) {
        this->hubble_type = new_type;
    }
    // Prototype for function to print out an object's data
    void print_data();
    // Add satellite galaxy
    void add_galaxy() {
        
    }
};
// Print out an object's data
void galaxy::print_data() {
    std::cout << "The Hubble Type is: " << this->hubble_type << std::endl;
    std::cout << "The total mass is: " << this->total_mass << std::endl;
    std::cout << "The redshift is: " << this->redshift << std::endl;
    std::cout << "The stellar mass fraction is: " << this->stellar_mass_fraction << std::endl;:wq
}
// End of class and associated member functions

// Main program
int main()
{
    std::string hubble_type = "Irr"; //E0, E7, S0, Sa, Sb, Sc, SBa, SBb, SBc, Irr
    double redshift = 2; // range 0-10
    double total_mass = 10e8; // 10^7 - 10^12
    double stellar_mass_fraction = 0.025; // 0 - 0.05
    
    // Example using default constructor
    galaxy g1; 

    // Example using parameterised constructor
    galaxy g2(redshift,total_mass,stellar_mass_fraction,hubble_type);
    // print out data
    g2.print_data();
    // Get and print out stellar mass
    g2.stellar_mass();
    // Change Hubble type from Irr to S0
    g2.change_type("S0");
    // Add satellite galaxies


    return 0;
}

