#include <iostream>
#include <vector>
//using namespace std;
 
int main() {
    
    double numsArr[] = {2, 5, 1, 8, 4, 3, 6};
    double* num_point = numsArr;

    std::cout << "pointer " << num_point << std::endl;
    std::cout << "value at pointer " << *num_point << std::endl;
    std::cout << "value of arr " << *numsArr << std::endl;
    std::cout << "the reference of pointer " << &num_point << std::endl;
    std::cout << "adwnjhadwnlk" << std::endl;
    int a = 20;
    *(num_point) = 20;
    std::cout << "pointer 1: " << *num_point << ", " << *(num_point+1) << " end" << std::endl;
}
