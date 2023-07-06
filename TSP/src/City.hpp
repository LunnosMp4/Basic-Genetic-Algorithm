/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: City.hpp
*/

#pragma once

#include "TSP.h"

class City {
    public:
        City(float x, float y, int id) : _x(x), _y(y), _id(id) {}
        ~City() = default;

        float getX() { return _x; }
        float getY() { return _y; }
        int getId() { return _id; }
        float getDistance(City city) { return sqrt(pow(_x - city.getX(), 2) + pow(_y - city.getY(), 2)); }

    private:
        float _x;
        float _y;
        int _id;
};