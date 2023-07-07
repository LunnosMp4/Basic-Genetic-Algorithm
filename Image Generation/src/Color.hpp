/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Color.hpp
*/

#pragma once

#include "ImageGeneration.h"

class Color {
    public:
        Color(int r, int g, int b) : _r(r), _g(g), _b(b) {}
        Color(const sf::Color& color) : _r(color.r), _g(color.g), _b(color.b) {}
        ~Color() = default;

        int getR() const { return _r;}
        int getG() const { return _g;}
        int getB() const { return _b;}

        void setR(int r) { _r = r;}
        void setG(int g) { _g = g;}
        void setB(int b) { _b = b;}

        void setRGB(int r, int g, int b) { _r = r; _g = g; _b = b;}

        void setRandomColor() { _r = getRandomInt(0, 255); _g = getRandomInt(0, 255); _b = getRandomInt(0, 255);}

        void printColor() const { std::cout << "R: " << _r << " G: " << _g << " B: " << _b << std::endl;}

        sf::Color toSfColor() const { return sf::Color(_r, _g, _b);}

        bool operator==(const Color& color) const { return (_r == color.getR() && _g == color.getG() && _b == color.getB());}
        bool operator!=(const Color& color) const { return !(*this == color);}

    private:
        int _r;
        int _g;
        int _b;
};