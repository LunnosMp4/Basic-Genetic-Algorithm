/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: TSP.h
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>
#include <set>
#include "gnuplot-iostream.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <thread>

#define Cast(type, value) static_cast<type>(value)

float getRandomFloat(float min, float max);
int getRandomInt(int min, int max);
std::vector<int> randomizeVector(std::vector<int> vector);