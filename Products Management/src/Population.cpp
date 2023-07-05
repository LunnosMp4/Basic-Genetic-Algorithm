/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Population.cpp
*/

#include "Population.hpp"

Population::Population(int populationSize) : _populationSize(populationSize) {
    if (_populationSize <= 0)
        throw std::invalid_argument("Population size must be greater than 0");
}

void Population::initializePopulation(std::vector<float> volumes, std::vector<float> prices, float maxVolume) {
    for (int i = 0; i < _populationSize; i++) {
        std::shared_ptr<Individual> individual = std::make_shared<Individual>(volumes, prices, maxVolume);
        _population.push_back(individual);
    }
    _bestIndividual = _population[0];
}

void Population::orderPopulation() {
    std::sort(_population.begin(), _population.end(), [](std::shared_ptr<Individual> a, std::shared_ptr<Individual> b) {
        return a->getFitness() > b->getFitness();
    });
}

void Population::bestIndividual(std::shared_ptr<Individual> individual) {
    if (individual->getFitness() > _bestIndividual->getFitness())
        _bestIndividual = individual;
}

float Population::fitnessTotal() {
    float fitnessTotal = 0;
    for (int i = 0; i < _populationSize; i++)
        fitnessTotal += _population[i]->getFitness();
    return fitnessTotal;
}

std::shared_ptr<Individual> Population::selection(float fitnessTotal) {
    float random = getRandomFloat(0, fitnessTotal);
    float sum = 0;
    for (int i = 0; i < _populationSize; i++) {
        sum += _population[i]->getFitness();
        if (sum >= random)
            return _population[i];
    }
    return _population[0];
}

void Population::updatePopulation() {
    for (int i = 0; i < _populationSize; i++)
        _population[i]->fitness();
    orderPopulation();
    bestIndividual(_population[0]);
    printGeneration();
}

void Population::run(int generations, float mutationRate, std::vector<float> volumes, std::vector<float> prices, float maxVolume) {
    initializePopulation(volumes, prices, maxVolume);
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

        _population = newPopulation;
        updatePopulation();
    }

    std::cout << "**************************" << std::endl;
    std::cout << "Best individual find in generation : " << _bestIndividual->getGeneration() << std::endl;
    std::cout << "Fitness: " << _bestIndividual->getFitness() << std::endl;
    std::cout << "Used volume: " << _bestIndividual->getUsedVolume() << std::endl;
    std::cout << "Chromosome: [";
    for (int i = 0; i < Cast(int, _bestIndividual->getChromosome().size()); i++)
        std::cout << _bestIndividual->getChromosome()[i];
    std::cout << "]" << std::endl;
}

void Population::printGeneration() {
    std::shared_ptr<Individual> current = _population[0];
    std::cout << "Generation: " << current->getGeneration() << std::endl;
    std::cout << "Best individual: " << std::endl;
    std::cout << "Fitness: " << current->getFitness() << std::endl;
    std::cout << "Used volume: " << current->getUsedVolume() << std::endl;
    std::cout << "Chromosome: [";
    for (int i = 0; i < Cast(int, current->getChromosome().size()); i++)
        std::cout << current->getChromosome()[i];
    std::cout << "]" << std::endl;
    std::cout << std::endl;
}