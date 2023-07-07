/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Population.hpp
*/

#pragma once

#include "Individual.hpp"

class Population {
    public:
        Population(int populationSize);
        ~Population() = default;

        void initializePopulation(int width, int height);
        void updatePopulation();
        void orderPopulation();
        void bestIndividual(std::shared_ptr<Individual> individual);
        float fitnessTotal();
        std::shared_ptr<Individual> selection(float fitnessTotal);

        bool run(int generations, float mutationRate, int width, int height, std::vector<Color>, sf::RenderWindow& window);
        void printGeneration();

        std::vector<float> getSolutions() { return _solutions; }
        std::shared_ptr<Individual> getBestIndividual() { return _bestIndividual; }

    private:
        int _populationSize;
        std::vector<std::shared_ptr<Individual>> _population;
        std::shared_ptr<Individual> _bestIndividual;
        std::vector<float> _solutions;
        std::vector<Color> _target;
};