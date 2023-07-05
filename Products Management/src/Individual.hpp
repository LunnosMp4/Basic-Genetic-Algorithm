/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Individual.hpp
*/

#pragma once

#include "Product.hpp"

class Individual {
    public:
        Individual(std::vector<float> volumes, std::vector<float> prices, float maxVolume, int generation = 0);
        ~Individual() = default;

        void fitness();
		std::vector<std::shared_ptr<Individual>>  crossover(std::shared_ptr<Individual> other);
		std::shared_ptr<Individual> mutation(float mutationRate);

        std::vector<float> getVolumes() { return _volumes; }
        std::vector<float> getPrices() { return _prices; }
        float getMaxVolume() { return _maxVolume; }
        int getGeneration() { return _generation; }
        std::vector<int> getChromosome() { return _chromosome; }
		float getFitness() { return _fitness; }
		float getUsedVolume() { return _usedVolume; }
		void setChromosome(std::vector<int> chromosome) { _chromosome = chromosome; }

    private:
        std::vector<float> _volumes;
        std::vector<float> _prices;
        float _maxVolume;
        int _generation;
        std::vector<int> _chromosome;
        float _fitness;
        float _usedVolume;
};