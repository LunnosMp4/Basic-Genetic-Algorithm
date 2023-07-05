/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Product.hpp
*/

#pragma once

#include "ProductManagement.h"

class Product {
    public:
        Product(std::string name, float volume, float price) : _name(name), _volume(volume), _price(price) {}
        ~Product() {}
    
        std::string getName() { return _name; }
        float getVolume() { return _volume; }
        float getPrice() { return _price; }

    private:
        std::string _name;
        float _volume;
        float _price;
};
