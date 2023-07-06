/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Utils.cpp
*/

#include "TSP.h"

std::vector<int> randomizeVector(std::vector<int> vector) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, Cast(int, vector.size()) - 1);
    std::shuffle(vector.begin(), vector.end(), gen);
    return vector;
}

float getRandomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}

int getRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}