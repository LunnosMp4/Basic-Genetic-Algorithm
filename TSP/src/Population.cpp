/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Population.cpp
*/

#include "Population.hpp"

void updateWindow(std::shared_ptr<Individual> bestIndividual, std::shared_ptr<Individual> bestOAT, sf::RenderWindow& window, std::vector<City> cities);

Population::Population(int populationSize) : _populationSize(populationSize) {
    if (_populationSize <= 0)
        throw std::invalid_argument("Population size must be greater than 0");
    if (_populationSize % 2 != 0)
        throw std::invalid_argument("Population size must be even");
}

void Population::initializePopulation(std::vector<City> cities) {
    for (int i = 0; i < _populationSize; i++) {
        std::shared_ptr<Individual> individual = std::make_shared<Individual>(cities);
        _population.push_back(individual);
    }
    _bestIndividual = _population[0];
}

void Population::orderPopulation() {
    std::sort(_population.begin(), _population.end(), [](std::shared_ptr<Individual> a, std::shared_ptr<Individual> b) {
        return a->getFitness() < b->getFitness();
    });
}

void Population::bestIndividual(std::shared_ptr<Individual> individual) {
    if (individual->getFitness() < _bestIndividual->getFitness())
        _bestIndividual = individual;
}

float Population::fitnessTotal() {
    float fitnessTotal = 0;
    for (int i = 0; i < _populationSize; i++)
        fitnessTotal += _population[i]->getFitness();
    return fitnessTotal;
}

std::shared_ptr<Individual> Population::selection(float fitnessTotal) {
    std::vector<float> selectionProbabilities;
    for (int i = 0; i < _populationSize; i++) {
        float probability = static_cast<float>(i + 1) / _populationSize;
        selectionProbabilities.push_back(probability);
    }

    float random = getRandomFloat(0, fitnessTotal);
    float accumulatedProbability = 0;

    for (int i = 0; i < _populationSize; i++) {
        accumulatedProbability += selectionProbabilities[i];
        if (accumulatedProbability >= random) {
            return _population[i];
        }
    }
    return _population[0];
}

void Population::updatePopulation() {
    for (int i = 0; i < _populationSize; i++)
        _population[i]->fitness();
    orderPopulation();

    for (int i = _populationSize - Cast(int, _populationSize * 0.05); i < _populationSize; i++) {
        std::shared_ptr<Individual> last = _population[i]->mutation(1);
        _population[i] = last;
        _population[i]->fitness();
    }
    orderPopulation();

    bestIndividual(_population[0]);
    _solutions.push_back(_bestIndividual->getFitness());
    printGeneration();
}

bool Population::run(int generations, float mutationRate, std::vector<City> cities, sf::RenderWindow& window) {
    initializePopulation(cities);
    updatePopulation();

    for (int i = 0; i < generations; i++) {
        std::vector<std::shared_ptr<Individual>> newPopulation;
        float totalFitness = fitnessTotal();

        for (int i = 0; i < _populationSize; i += 2) {
            std::shared_ptr<Individual> parent1 = selection(totalFitness);
            std::shared_ptr<Individual> parent2 = selection(totalFitness);
            std::vector<std::shared_ptr<Individual>> childrens = parent1->crossover(parent2);
            newPopulation.push_back(childrens[0]->mutation(mutationRate));
            newPopulation.push_back(childrens[1]->mutation(mutationRate));
        }


        Individual elite(_population[0]);
        _population = newPopulation;
        _population.at(0) = std::make_shared<Individual>(elite);
        updatePopulation();
        updateWindow(_population[0], _bestIndividual, window, cities);
    }

    std::cout << "**************************" << std::endl;
    std::cout << "Best individual find in generation : " << _bestIndividual->getGeneration() << std::endl;
    std::cout << "Fitness: " << _bestIndividual->getFitness() << std::endl;
    return true;
}

void Population::printGeneration() {
    std::shared_ptr<Individual> current = _population[0];
    std::cout << "Generation: " << current->getGeneration() << " | Best Individual: " << current->getFitness() << std::endl;
}
