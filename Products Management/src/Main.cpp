/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Main.cpp
*/

#include "Population.hpp"

std::tuple<std::vector<float>, std::vector<float>> createProductList() {
    std::vector<Product> products_list = {
        {"Microwave U", 0.0424, 308.66},
        {"Refrigerator U", 0.751, 999.9},
        {"Notebook", 0.00350, 2499.90},
        {"Mocbook", 0.498, 1999.90},
        {"TV 2K Oled", 0.200, 2999.00},
        {"TV 4k", 0.290, 3999.90},
        {"TV 8k", 0.400, 4346.99},
        {"Notebook C", 0.527, 3999.00},
        {"OPhone", 0.0000899, 2199.12},
        {"Headphones", 0.00015, 149.99},
        {"Camera", 0.000250, 799.00},
        {"YBox", 0.0038, 499.99},
        {"Gamestation", 0.0040, 599.99},
        {"Bluetooth Speaker", 0.0005, 89.99},
        {"Coffee Machine", 0.025, 179.90},
        {"Smart Thermostat", 0.00035, 129.99},
        {"Portable Hard Drive", 0.001, 69.99},
        {"Wireless Mouse", 0.00008, 29.99},
        {"Electric Toothbrush", 0.00012, 89.99},
        {"Fitness Tracker", 0.00006, 149.99},
        {"Washing Machine", 0.900, 1499.00},
        {"Dishwasher", 0.650, 1199.99},
        {"Oven", 0.800, 1799.00},
        {"Air Conditioner", 1.500, 2499.99},
        {"Home Theater System", 0.350, 799.00},
        {"Smart TV", 0.850, 1299.99},
        {"Microwave X", 0.0544, 429.90},
        {"Refrigerator X", 0.950, 1999.00},
        {"Laptop Pro", 0.002, 2799.00},
        {"Gaming Chair", 0.120, 399.99},
        {"Vacuum Cleaner", 0.050, 199.00},
        {"Soundbar", 0.015, 299.99},
        {"Coffee Maker", 0.030, 89.99},
        {"Blender", 0.008, 49.99},
        {"Fitness Equipment Set", 0.450, 999.00},
        {"Home Security System", 0.250, 599.99},
        {"Tablet", 0.001, 499.00},
        {"Outdoor Grill", 0.200, 399.99},
        {"Projector", 0.150, 799.00},
        {"Massage Chair", 0.800, 1999.99},
        {"Smartwatch", 0.0025, 349.00},
        {"Robot Vacuum", 0.035, 499.99},
        {"Digital Camera", 0.005, 599.00},
        {"Bluetooth Headphones", 0.0003, 149.99},
        {"Desktop Computer", 0.030, 999.00},
        {"Drone", 0.002, 799.00},
        {"Portable Bluetooth Speaker", 0.002, 79.99},
        {"Smart Home Hub", 0.002, 149.99},
        {"Wireless Earbuds", 0.0001, 199.99},
        {"Electric Scooter", 0.020, 499.99},
        {"Ultrawide Monitor", 0.015, 699.00},
        {"Air Fryer", 0.010, 129.99},
        {"Power Bank", 0.0002, 49.99},
        {"Fitness Tracker", 0.0003, 79.99},
        {"Drill Set", 0.050, 149.99},
        {"Portable Charger", 0.00015, 39.99}
    };

    std::vector<float> volumes(products_list.size());
    std::vector<float> prices(products_list.size());
    std::transform(products_list.begin(), products_list.end(), volumes.begin(), [](Product product) { return product.getVolume(); });
    std::transform(products_list.begin(), products_list.end(), prices.begin(), [](Product product) { return product.getPrice(); });

    return std::make_tuple(volumes, prices);
}

void createPlot(int generations, Population population) {
    Gnuplot gp;
    std::vector<double> x_vals(generations + 1);
    std::vector<double> y_vals;
    
    for (int i = 0; i <= generations; i++) {
        x_vals[i] = i;
        y_vals.push_back(population.getSolutions()[i]);
    }
    
    gp << "set xrange [0:" << generations << "]\n";
    gp << "set yrange [0:]\n";
    gp << "plot '-' with linespoints title 'GA'\n";
    gp.send1d(boost::make_tuple(x_vals, y_vals));
    std::cout << "Press enter to exit." << std::endl;
    std::cin.get();
}

int main() {
    float maxVolume = 3;
    float mutationRate = 0.01;
    int populationSize = 20;
    int generations = 100;

    Population population(populationSize);
    population.run(generations, mutationRate, std::get<0>(createProductList()), std::get<1>(createProductList()), maxVolume);

    createPlot(generations, population);
    return 0;
}