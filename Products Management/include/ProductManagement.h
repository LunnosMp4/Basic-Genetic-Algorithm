/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: ProductManagement.h
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>
#include "gnuplot-iostream.h"

#define Cast(type, value) static_cast<type>(value)

int getRandomInt(int min, int max);
float getRandomFloat(float min, float max);