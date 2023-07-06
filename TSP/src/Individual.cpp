/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Individual.cpp
*/

#include "Individual.hpp"

Individual::Individual(std::vector<City> cities, int generation) : _cities(cities), _generation(generation) {
    for (int i = 0; i < Cast(int, _cities.size()); i++) {
        _chromosome.push_back(i);
    }

    _chromosome = randomizeVector(_chromosome);
}

void Individual::fitness() {
    float distance = 0;
    for (int i = 0; i < Cast(int, _chromosome.size()) - 1; i++) {
        distance += _cities[_chromosome[i]].getDistance(_cities[_chromosome[i + 1]]);
    }
    distance += _cities[_chromosome[_chromosome.size() - 1]].getDistance(_cities[_chromosome[0]]);
    _fitness = distance;
}

std::vector<std::shared_ptr<Individual>> Individual::crossover(std::shared_ptr<Individual> other) {
    int size = _chromosome.size();
    std::vector<int> child1(size, -1);
    std::vector<int> child2(size, -1);
    std::vector<int> otherChromosome = other->getChromosome();

    int startPos = getRandomInt(0, size - 1);
    int endPos = getRandomInt(0, size - 1);

    if (startPos > endPos)
        std::swap(startPos, endPos);

    for (int i = startPos; i <= endPos; i++) {
        child1[i] = _chromosome[i];
        child2[i] = otherChromosome[i];
    }

    int j = (endPos + 1) % size;
    int k = (endPos + 1) % size;
    for (int i = 0; i < size; i++) {
        if (i < startPos || i > endPos) {
            while (std::find(child1.begin(), child1.end(), otherChromosome[j]) != child1.end()) {
                j = (j + 1) % size;
            }
            child1[i] = otherChromosome[j];

            while (std::find(child2.begin(), child2.end(), _chromosome[k]) != child2.end()) {
                k = (k + 1) % size;
            }
            child2[i] = _chromosome[k];
        }
    }

    std::vector<std::shared_ptr<Individual>> children;
    children.push_back(std::make_shared<Individual>(_cities, _generation + 1));
    children.push_back(std::make_shared<Individual>(_cities, _generation + 1));
    children[0]->setChromosome(child1);
    children[1]->setChromosome(child2);
    return children;
}

std::shared_ptr<Individual> Individual::mutation(float mutationRate) {
    for (int i = 0; i < Cast(int, _chromosome.size()); i++) {
        float random = getRandomFloat(0, 1);
        if (random <= mutationRate) {
            int randomIndex = getRandomInt(0, _chromosome.size() - 1);
            int aux = _chromosome[i];
            _chromosome[i] = _chromosome[randomIndex];
            _chromosome[randomIndex] = aux;
        }
    }
    return std::make_shared<Individual>(*this);
}