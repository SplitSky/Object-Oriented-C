#include <iostream>
#include <vector>
//using namespace std;
 
int main() {
    
    int numsArr[] = {2, 5, 1, 8, 4, 3, 6};
    int* num_point = numsArr;
    std::vector<int> nums(std::begin(*num_point), std::end(*num_point));
 
    for (int i = 0; i < nums.size(); i++) {
        std::cout << nums[i] << std::endl;
    }     
}
