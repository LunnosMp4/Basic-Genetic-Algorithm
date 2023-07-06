/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Main.cpp
*/

#include "Population.hpp"
#include "gnuplot-iostream.h"
#include <SFML/Graphics.hpp>


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

void drawCities(std::shared_ptr<Population> population, std::vector<City> cities) {
    sf::RenderWindow window(sf::VideoMode(400, 400), "TSP", sf::Style::Close);
    window.setFramerateLimit(60);
    std::vector<sf::CircleShape> cityShapes;
    for (auto city : cities) {
        sf::CircleShape shape(5);
        shape.setPosition(city.getX() - 5, city.getY() - 5);
        shape.setFillColor(sf::Color::Red);
        cityShapes.push_back(shape);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color::White);

        for (auto shape : cityShapes)
            window.draw(shape);

        std::vector<int> chromosome = population->getBestIndividual()->getChromosome();
        for (int i = 0; i < Cast(int, chromosome.size()) - 1; i++) {
            int city1 = chromosome[i];
            int city2 = chromosome[i + 1];
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(cities[city1].getX(), cities[city1].getY()), sf::Color::Black),
                sf::Vertex(sf::Vector2f(cities[city2].getX(), cities[city2].getY()), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
        }
        int lastCity = chromosome[chromosome.size() - 1];
        int firstCity = chromosome[0];
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(cities[lastCity].getX(), cities[lastCity].getY()), sf::Color::Black),
            sf::Vertex(sf::Vector2f(cities[firstCity].getX(), cities[firstCity].getY()), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);

        window.display();
    }
}

int main() {
    std::vector<City> cities;
    cities.push_back(City(60, 200, 0));
    cities.push_back(City(180, 200, 1));
    cities.push_back(City(80, 180, 2));
    cities.push_back(City(140, 180, 3));
    cities.push_back(City(20, 160, 4));
    cities.push_back(City(100, 160, 5));
    cities.push_back(City(200, 160, 6));
    cities.push_back(City(140, 140, 7));
    cities.push_back(City(40, 120, 8));
    cities.push_back(City(100, 120, 9));
    cities.push_back(City(180, 100, 10));
    cities.push_back(City(60, 80, 11));

    float mutationRate = 0.1;
    int populationSize = 20;
    int generations = 100;

    std::shared_ptr<Population> population = std::make_shared<Population>(populationSize);
    population->run(generations, mutationRate, cities);

    drawCities(population, cities);
    createPlot(generations, population);

    return 0;
}