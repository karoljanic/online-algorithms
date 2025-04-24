#include <iostream>
#include <memory>

#include "bin_pack.hpp"
#include "offline_bin_packing.hpp"
#include "best_fit_bin_pack.hpp"
#include "first_fit_bin_pack.hpp"
#include "next_fit_bin_pack.hpp"
#include "random_fit_bin_pack.hpp"
#include "worst_fit_bin_pack.hpp"
#include "distribution.hpp"

constexpr uint16_t MaxElementsNumberPerTry = 10;

constexpr double harmonicNumber(uint16_t index, uint16_t power) {
    double sum = 0.0;
    for(uint16_t i = 1; i <= index; i++) {
        sum += 1.0 / std::pow(i, power);
    }

    return sum;
}

constexpr double uniformDistributionProbability(uint16_t /*index*/) {
    return 1.0 / MaxElementsNumberPerTry;
}

constexpr double geometricDistributionProbability(uint16_t index) {
    if(index < MaxElementsNumberPerTry) {
        return 1.0 / std::pow(2, index);
    }
    else {
        return 1.0 / std::pow(2, MaxElementsNumberPerTry - 1);
    }
}

constexpr double harmonicDistributionProbability(uint16_t index) {
    return 1.0 / (index * harmonicNumber(MaxElementsNumberPerTry, 1));
}

constexpr double biharmonicDistributionProbability(uint16_t index) {
    return 1.0 / (std::pow(index, 2) * harmonicNumber(MaxElementsNumberPerTry, 2));
}


int main(int argc, char* argv[]) {
    if(argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <strategy> <distribution> <elements_number> <repetitions>" << std::endl;
        return -1;
    }

    std::string strategy = argv[1];
    std::string dist = argv[2];
    size_t elementsNumber = std::stoul(argv[3]);
    size_t repetitions = std::stoul(argv[4]);

    std::unique_ptr<BinPack> binPack;
    if(strategy == "next-fit") {
        binPack = std::make_unique<NextFitBinPack>(1.0);
    } else if(strategy == "random-fit") {
        binPack = std::make_unique<RandomFitBinPack>(1.0);
    } else if(strategy == "first-fit") {
        binPack = std::make_unique<FirstFitBinPack>(1.0);
    } else if(strategy == "best-fit") {
        binPack = std::make_unique<BestFitBinPack>(1.0);
    } else if(strategy == "worst-fit") {
        binPack = std::make_unique<WorstFitBinPack>(1.0);
    } else {
        std::cerr << "Invalid strategy: " << strategy << std::endl;
        return -1;
    }

    std::unique_ptr<DistributionI> distribution;
    if(dist == "uniform") {
        distribution = std::make_unique<Distribution<MaxElementsNumberPerTry, uniformDistributionProbability>>();
    } else if(dist == "geometric") {
        distribution = std::make_unique<Distribution<MaxElementsNumberPerTry, geometricDistributionProbability>>();
    } else if(dist == "harmonic") {
        distribution = std::make_unique<Distribution<MaxElementsNumberPerTry, harmonicDistributionProbability>>();
    } else if(dist == "biharmonic") {
        distribution = std::make_unique<Distribution<MaxElementsNumberPerTry, biharmonicDistributionProbability>>();
    } else {
        std::cerr << "Invalid distribution: " << dist << std::endl;
        return -1;
    }

    OfflineBinPacking binPackOffline{1.0};

    std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distributionSize(0.0, 1.0);

    size_t sumOfBinsNumber = 0;
    size_t sumOfBinsNumberLowerBound = 0;
    for(size_t rep = 0; rep < repetitions; rep++) {
        binPack->reset();
        size_t binsNumber = 0;
        std::vector<double> elementSizes;
        
        size_t elementsCounter = 0;
        while(elementsCounter < elementsNumber) {
            const double elementSize = distributionSize(generator);
            const size_t elementsToAdd = (*distribution)();
            for(size_t i = 0; i < elementsToAdd; i++) {
                if(elementsCounter >= elementsNumber) {
                    break;
                }
                binsNumber += binPack->pack(elementSize);
                elementSizes.push_back(elementSize);
                elementsCounter++;
            }
        }

        sumOfBinsNumber += binsNumber;
        sumOfBinsNumberLowerBound += binPackOffline.pack(elementSizes);
    }
    
    if(repetitions == 0) {
        std::cout << 0 << " " << 0 << std::endl;
    }
    else {
        std::cout << static_cast<double>(sumOfBinsNumber) / static_cast<double>(repetitions) << " " << static_cast<double>(sumOfBinsNumber) / static_cast<double>(sumOfBinsNumberLowerBound) << std::endl;
    }

    return 0;
}