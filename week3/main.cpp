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
    std::vector<galaxy> satellites;

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
    void add_satellite(galaxy satellite) {
        satellites.push_back(satellite);
    }
};
// Print out an object's data
void galaxy::print_data() {
    std::cout << "The Hubble Type is: " << this->hubble_type << std::endl;
    std::cout << "The total mass is: " << this->total_mass << std::endl;
    std::cout << "The redshift is: " << this->redshift << std::endl;
    std::cout << "The stellar mass fraction is: " << this->stellar_mass_fraction << std::endl;
    std::cout << "The number of satellites is: " << this->satellites.size() << std::endl;
    if(this->satellites.size() > 0) {
        // define an iterator
        int i{1};
        std::vector<galaxy>::iterator vector_begin{this->satellites.begin()};
        std::vector<galaxy>::iterator vector_end{this->satellites.end()};
        std::vector<galaxy>::iterator vector_iterator;

        for (vector_iterator=vector_begin;vector_iterator<vector_end; ++vector_iterator) {
            std::cout << "The satellite no." << i << " has the following properties" << std::endl;
            vector_iterator->print_data();
            i++;
        }
        std::cout << std::endl; // a line break ofr better readibiltiy
    }
}
// End of class and associated member functions

// Main program
int main() {
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
    g2.add_satellite(g1);
    // Print out the data again with satellite
    g2.print_data();

    hubble_type = "E0"; //E0, E7, S0, Sa, Sb, Sc, SBa, SBb, SBc, Irr
    redshift = 5; // range 0-10
    total_mass = 10e9; // 10^7 - 10^12
    stellar_mass_fraction = 0.03; // 0 - 0.05 

    galaxy g3(redshift, total_mass, stellar_mass_fraction, hubble_type);
    
    galaxy g4;
    galaxy g5;
    g3.add_satellite(g4);
    g3.add_satellite(g5);
    g3.print_data();



    return 0;
}

