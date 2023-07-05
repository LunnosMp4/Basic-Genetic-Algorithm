/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Individual.cpp
*/

#include "Individual.hpp"

Individual::Individual(std::vector<float> volumes, std::vector<float> prices, float maxVolume, int generation) : _volumes(volumes), _prices(prices), _maxVolume(maxVolume), _generation(generation) {
    for (int i = 0; i < Cast(int, volumes.size()); i++) {
        _chromosome.push_back(getRandomInt(0, 1));
    }
}

std::vector<std::shared_ptr<Individual>> Individual::crossover(std::shared_ptr<Individual> other) {
    int crossoverPoint = getRandomInt(0, _chromosome.size());
    std::vector<int> child1;
    std::vector<int> child2;
    std::vector<int> otherChromosome = other->getChromosome();
    std::vector<int> selfChromosome = _chromosome;

    child1.insert(child1.end(), otherChromosome.begin(), otherChromosome.begin() + crossoverPoint);
    child1.insert(child1.end(), selfChromosome.begin() + crossoverPoint, selfChromosome.end());
    child2.insert(child2.end(), selfChromosome.begin(), selfChromosome.begin() + crossoverPoint);
    child2.insert(child2.end(), otherChromosome.begin() + crossoverPoint, otherChromosome.end());

    std::vector<std::shared_ptr<Individual>> childrens;
    childrens.push_back(std::make_shared<Individual>(_volumes, _prices, _maxVolume, _generation + 1));
    childrens.push_back(std::make_shared<Individual>(_volumes, _prices, _maxVolume, _generation + 1));
    childrens[0]->setChromosome(child1);
    childrens[1]->setChromosome(child2);
    return childrens;
}

void Individual::fitness() {
    float fitness = 0;
    float volume = 0;
    for (int i = 0; i < Cast(int, _chromosome.size()); i++) {
        if (_chromosome[i] == 1) {
            fitness += _prices[i];
            volume += _volumes[i];
        }
    }
    if (volume > _maxVolume)
        fitness = 1;
    _fitness = fitness;
    _usedVolume = volume;
}

std::shared_ptr<Individual> Individual::mutation(float mutationRate) {
    for (int i = 0; i < Cast(int, _chromosome.size()); i++) {
        float random = getRandomFloat(0, 1);
        if (random <= mutationRate) {
            if (_chromosome[i] == 1)
                _chromosome[i] = 0;
            else
                _chromosome[i] = 1;
        }
    }
    return std::make_shared<Individual>(*this);
}