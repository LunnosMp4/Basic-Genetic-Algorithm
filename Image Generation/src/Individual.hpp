/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Individual.hpp
*/

#pragma once

#include "Color.hpp"

class Individual {
    public:
        Individual(int width, int height, int generation = 0);
        Individual(std::shared_ptr<Individual> other) : _generation(other->getGeneration() + 1), _chromosome(other->getChromosome()), _fitness(other->getFitness()) {}
        ~Individual() = default;

        void fitness(std::vector<Color> target);
        std::vector<std::shared_ptr<Individual>> crossover(std::shared_ptr<Individual> other);
        std::shared_ptr<Individual> mutation(float mutationRate);

        int getGeneration() { return _generation; }
        void setGeneration(int generation) { _generation = generation; }
        float getFitness() { return _fitness; }
        std::vector<Color> getChromosome() { return _chromosome; }
        void setChromosome(std::vector<Color> chromosome) { _chromosome = chromosome; }

    private:
        int _generation;
        std::vector<Color> _chromosome;
        float _fitness;
        int _width;
        int _height;
};
