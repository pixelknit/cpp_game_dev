#pragma once

#include <vector>

inline int Add(int a, int b){
    return a + b;
} 

inline float Mult(float a, float b){
    return a * b;
}

inline std::vector<float> MM(std::vector<float> &a, std::vector<float> &b){
    ///
    return {};
}

class MathLib{
    int id;
    float weight;
    public:
        MathLib();
        ~MathLib();
        void myTest(){};
};