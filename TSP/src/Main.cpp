/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Main.cpp
*/

#include "Population.hpp"

void updateWindow(std::shared_ptr<Individual> bestCurrent, std::shared_ptr<Individual> bestOAT, sf::RenderWindow& window, std::vector<City> cities);

void createPlot(int generations, std::shared_ptr<Population> population) {
    Gnuplot gp;
    std::vector<double> x_vals(generations + 1);
    std::vector<double> y_vals;
    
    for (int i = 0; i <= generations; i++) {
        x_vals[i] = i;
        y_vals.push_back(population->getSolutions()[i]);
    }
    
    gp << "set xrange [0:" << generations << "]\n";
    gp << "set yrange [0:]\n";
    gp << "plot '-' with linespoints title 'GA'\n";
    gp.send1d(boost::make_tuple(x_vals, y_vals));
    std::cout << "Press enter to exit." << std::endl;
    std::cin.get();
}

std::vector<City> createCities(int nbCities) {
    std::vector<City> cities;

    int xMin = 20;
    int xMax = 380;
    int yMin = 60;
    int yMax = 380;

    for (int i = 0; i < nbCities; ++i) {
        int x = getRandomInt(xMin, xMax);
        int y = getRandomInt(yMin, yMax);
        cities.push_back(City(x, y, i));
    }
    return cities;
}

int main(int ac, char **av) {
    float mutationRate = 0.001;
    int populationSize = 50;
    int generations = 500;
    int nbCities = 20;

    if (ac == 5) {
        generations = std::stoi(av[1]);
        populationSize = std::stoi(av[2]);
        mutationRate = std::stof(av[3]);
        nbCities = std::stoi(av[4]);
    } else if (ac != 1) {
        std::cerr << "Usage: ./TSP [generations] [populationSize] [mutationRate] [nbCities]" << std::endl;
        std::cerr << "Example: ./TSP 500 50 0.001 20" << std::endl;
        std::cerr << "No arguments will use default values list above" << std::endl;
        return 84;
    }

    std::vector<City> cities = createCities(nbCities);


    std::shared_ptr<Population> population = std::make_shared<Population>(populationSize);
    sf::RenderWindow window(sf::VideoMode(400, 400), "TSP");

    while (window.isOpen()) {
        if (population->run(generations, mutationRate, cities, window) == true)
            break;
    }

    while (window.isOpen()) {
        updateWindow(population->getBestIndividual(), population->getBestIndividual(), window, cities);
    }

    createPlot(generations, population);

    return 0;
}