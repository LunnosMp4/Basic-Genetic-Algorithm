/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Individual.hpp
*/

#pragma once

#include "City.hpp"

class Individual {
    public:
        Individual(std::vector<City> cities, int generation = 0);
        ~Individual() = default;

        void fitness();
        std::vector<std::shared_ptr<Individual>> crossover(std::shared_ptr<Individual> other);
        std::shared_ptr<Individual> mutation(float mutationRate);

        std::vector<City> getCities() { return _cities; }
        int getGeneration() { return _generation; }
        float getFitness() { return _fitness; }
        std::vector<int> getChromosome() { return _chromosome; }
        void setChromosome(std::vector<int> chromosome) { _chromosome = chromosome; }

    private:
        std::vector<City> _cities;
        int _generation;
        std::vector<int> _chromosome;
        float _fitness;
};