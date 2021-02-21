#include <iostream>
#include <string>

int main() {
    std::string str = "123.4123";
    float num_float = std::stof(str);
    double num_double = std::stod(str);

    std::cout << num_double << std::endl;
    std::cout << num_float << std::endl;

}
