#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

void PrintArray(int nums[5]){
    for (int i=0; i < 5; ++i){
        std::cout << nums[i] << "\n";
    }
}

void PrintVector(std::vector<int> nums){
    for (int x : nums){
        std::cout << x << "\n";
    }    
}

void PrintMap(std::unordered_map<std::string, int> map){
    for (auto x : map){
        std::cout << x.first << " " << x.second << "\n";
    }
}

int main() {

    int nums[5] = {10,20,30,40, 50};
    PrintArray(nums);

    std::cout << "------------------------------------\n";

    std::vector<int> vec_nums = {60, 70, 80, 90, 100};
    PrintVector(vec_nums);
    vec_nums.push_back(200);

    std::cout << "------------------------------------\n";

    std::unordered_map<std::string, int> my_map = {
        {"Felipe", 20},
        {"Amy", 10},
        {"Peter", 100},
    };

    PrintMap(my_map);

    return 0;
}