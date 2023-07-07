/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Individual.cpp
*/

#include "Individual.hpp"

std::vector<Color> generateRandomColors(int numColors) {
    std::vector<Color> colors;
    colors.reserve(numColors);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);

    for (int i = 0; i < numColors; i++) {
        colors.push_back(Color(dist(gen), dist(gen), dist(gen)));
    }

    return colors;
}

Individual::Individual(int width, int height, int generation) : _width(width), _height(height), _generation(generation) {
    _chromosome = generateRandomColors(width * height);
}

void Individual::fitness(std::vector<Color> target) {
    float sumSquaredDiff = 0.0;
    for (int i = 0; i < _chromosome.size(); i++) {
        float diffR = _chromosome[i].getR() - target[i].getR();
        float diffG = _chromosome[i].getG() - target[i].getG();
        float diffB = _chromosome[i].getB() - target[i].getB();
        sumSquaredDiff += (diffR * diffR) + (diffG * diffG) + (diffB * diffB);
    }

    _fitness = sqrt(sumSquaredDiff);
}

std::vector<std::shared_ptr<Individual>> Individual::crossover(std::shared_ptr<Individual> other) {
    int crossoverPoint = getRandomInt(0, _chromosome.size());

    std::vector<Color> child1;
    std::vector<Color> child2;

    child1.reserve(_chromosome.size());
    child2.reserve(_chromosome.size());

    // Copy the genes from parents to children
    child1.insert(child1.end(), _chromosome.begin(), _chromosome.begin() + crossoverPoint);
    child1.insert(child1.end(), other->_chromosome.begin() + crossoverPoint, other->_chromosome.end());

    child2.insert(child2.end(), other->_chromosome.begin(), other->_chromosome.begin() + crossoverPoint);
    child2.insert(child2.end(), _chromosome.begin() + crossoverPoint, _chromosome.end());

    std::vector<std::shared_ptr<Individual>> children;
    children.push_back(std::make_shared<Individual>(_width, _height, _generation + 1));
    children.push_back(std::make_shared<Individual>(_width, _height, _generation + 1));

    children[0]->setChromosome(child1);
    children[1]->setChromosome(child2);

    return children;
}

std::shared_ptr<Individual> Individual::mutation(float mutationRate) {
    std::shared_ptr<Individual> mutatedIndividual = std::make_shared<Individual>(*this);
    std::vector<Color>& mutatedChromosome = mutatedIndividual->_chromosome;

    std::vector<std::thread> threads;
    unsigned int numThreads = std::thread::hardware_concurrency();
    unsigned int genesPerThread = _chromosome.size() / numThreads;

    auto mutateGenes = [&](unsigned int start, unsigned int end) {
        for (unsigned int i = start; i < end; i++) {
            if (getRandomFloat(0, 1) < mutationRate) {
                mutatedChromosome[i].setR(getRandomInt(0, 255));
                mutatedChromosome[i].setG(getRandomInt(0, 255));
                mutatedChromosome[i].setB(getRandomInt(0, 255));
            }
        }
    };

    for (unsigned int i = 0; i < numThreads; i++) {
        unsigned int start = i * genesPerThread;
        unsigned int end = (i == numThreads - 1) ? _chromosome.size() : (i + 1) * genesPerThread;
        threads.emplace_back(mutateGenes, start, end);
    }

    for (auto& thread : threads)
        thread.join();

    return mutatedIndividual;
}