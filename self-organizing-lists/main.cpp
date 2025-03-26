#include <iostream>
#include <memory>

#include "linked_list.hpp"
#include "move_to_front_linked_list.hpp"
#include "transpose_linked_list.hpp"
#include "count_linked_list.hpp"
#include "distribution.hpp"

constexpr uint16_t ArraySize = 100;

constexpr double harmonicNumber(uint16_t index, uint16_t power) {
    double sum = 0.0;
    for(uint16_t i = 1; i <= index; i++) {
        sum += 1.0 / std::pow(i, power);
    }

    return sum;
}

constexpr double uniformDistributionProbability(uint16_t /*index*/) {
    return 1.0 / ArraySize;
}

constexpr double geometricDistributionProbability(uint16_t index) {
    if(index < (ArraySize - 1)) {
        return 1.0 / std::pow(2, index + 1);
    }
    else {
        return 1.0 / std::pow(2, ArraySize - 1);
    }
}

constexpr double harmonicDistributionProbability(uint16_t index) {
    return 1.0 / ((index + 1) * harmonicNumber(ArraySize, 1));
}

constexpr double biharmonicDistributionProbability(uint16_t index) {
    return 1.0 / (std::pow(index + 1, 2) * harmonicNumber(ArraySize, 2));
}


int main(int argc, char* argv[]) {
    if(argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <strategy> <distribution> <operations_number> <repetitions>" << std::endl;
        return -1;
    }

    std::string strategy = argv[1];
    std::string dist = argv[2];
    size_t operationsNumber = std::stoul(argv[3]);
    size_t repetitions = std::stoul(argv[4]);

    std::unique_ptr<List> list;
    if(strategy == "none") {
        list = std::make_unique<LinkedList>(ArraySize);
    } else if(strategy == "move-to-front") {
        list = std::make_unique<MoveToFrontLinkedList>(ArraySize);
    } else if(strategy == "transpose") {
        list = std::make_unique<TransposeLinkedList>(ArraySize);
    } else if(strategy == "count") {
        list = std::make_unique<CountLinkedList>(ArraySize);
    } else {
        std::cerr << "Invalid strategy: " << strategy << std::endl;
        return -1;
    }

    std::unique_ptr<DistributionI> distribution;
    if(dist == "uniform") {
        distribution = std::make_unique<Distribution<ArraySize, uniformDistributionProbability>>();
    } else if(dist == "geometric") {
        distribution = std::make_unique<Distribution<ArraySize, geometricDistributionProbability>>();
    } else if(dist == "harmonic") {
        distribution = std::make_unique<Distribution<ArraySize, harmonicDistributionProbability>>();
    } else if(dist == "biharmonic") {
        distribution = std::make_unique<Distribution<ArraySize, biharmonicDistributionProbability>>();
    } else {
        std::cerr << "Invalid distribution: " << dist << std::endl;
        return -1;
    }

    size_t cost = 0;
    for(size_t rep = 0; rep < repetitions; rep++) {
        list->reset();
        for(size_t opNum = 0; opNum < operationsNumber; opNum++) {
            cost += list->access((*distribution)());
        }
    }
    
    if(repetitions * operationsNumber == 0) {
        std::cout << 0 << std::endl;
    }
    else {
        std::cout << static_cast<double>(cost) / static_cast<double>(repetitions * operationsNumber) << std::endl;
    }

    return 0;
}