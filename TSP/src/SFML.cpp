/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: SFML.cpp
*/

#include "TSP.h"
#include "Individual.hpp"

void updateWindow(std::shared_ptr<Individual> bestCurrent, std::shared_ptr<Individual> bestOAT, sf::RenderWindow& window, std::vector<City> cities) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) 
            window.close();
    }
    
    window.clear(sf::Color::White);

    sf::Text text;
    sf::Font font;
    font.loadFromFile("resources/Roboto.ttf");
    text.setFont(font);
    text.setString("Best current: " + std::to_string(bestCurrent->getFitness()) + "\nBest overall: " + std::to_string(bestOAT->getFitness()) + "\nGeneration: " + std::to_string(bestCurrent->getGeneration()));
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    text.setPosition(0, 0);
    window.draw(text);

    std::vector<sf::CircleShape> cityShapes;
    for (auto city : cities) {
        sf::CircleShape shape(5);
        shape.setPosition(city.getX() - 5, city.getY() - 5);
        shape.setFillColor(sf::Color::Red);
        cityShapes.push_back(shape);
    }
    for (auto shape : cityShapes) {
        window.draw(shape);
    }

    std::vector<int> chromosome = bestCurrent->getChromosome();
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
