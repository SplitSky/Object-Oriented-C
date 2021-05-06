// Object oriented C++ - Project main
//
// Tomasz Neska
// 05/05/2021
#include<fstream>
#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<array>
#include<iterator>
#include<cstring>
#include "classes.h"

#define _USE_MATH_DEFINES
// abstract class
class model {
    protected:
        std::vector<double> position;
        std::string name;
        int weapon_skill;
        int ballistic_skill;
        int toughness;
        int strength;
        int current_wound;
        int max_wound;
    public:
        model() = default;
        model(std::vector<double> init_pos, std::string init_name) : position{init_pos}, name{init_name} {}
        virtual ~model() {}

        std::string show_name() {
            return this->name;
        }

        void remove_wounds(int damage) {
            current_wound -= damage;
            std::cout << name << " took " << damage << " wounds!" << std::endl;
        }
};

using namespace std;
int main() {
    int gd = DETECT, gm;
    initgraph(-gd, -gm, "C:\\TC\\BGI");
    rectangle(100,100,200,200);
    getch();
    closegraph();
    return 0;
    
}
