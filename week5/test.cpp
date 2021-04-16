#include <iostream>
#include <vector>
//using namespace std;
 
int main() {
    
    int numsArr[] = {2, 5, 1, 8, 4, 3, 6};
    std::vector<int> nums(std::begin(numsArr), std::end(numsArr));
 
    for (int i = 0; i < nums.size(); i++) {
        std::cout << nums[i] << std::endl;
    }     
}
