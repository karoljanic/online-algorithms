#include <iostream>
#include <memory>

#include "page_migration.hpp"
#include "page_migration_move_to_min.hpp"
#include "page_migration_coin_flip.hpp"
#include "hypercube.hpp"
#include "torus.hpp"
#include "distribution.hpp"

constexpr uint16_t TORUS_DIMENSION = 8;
constexpr uint16_t HYPERCUBE_DIMENSION = 6;

constexpr size_t REQUESTS_NUMBER = 64;

constexpr double harmonicNumber(uint16_t index, uint16_t power) {
    double sum = 0.0;
    for(uint16_t i = 1; i <= index; i++) {
        sum += 1.0 / std::pow(i, power);
    }

    return sum;
}

constexpr double uniformDistributionProbability(uint16_t /*index*/) {
    return 1.0 / REQUESTS_NUMBER;
}

constexpr double geometricDistributionProbability(uint16_t index) {
    if(index < (REQUESTS_NUMBER - 1)) {
        return 1.0 / std::pow(2, index + 1);
    }
    else {
        return 1.0 / std::pow(2, REQUESTS_NUMBER - 1);
    }
}

constexpr double harmonicDistributionProbability(uint16_t index) {
    return 1.0 / ((index + 1) * harmonicNumber(REQUESTS_NUMBER, 1));
}

constexpr double biharmonicDistributionProbability(uint16_t index) {
    return 1.0 / (std::pow(index + 1, 2) * harmonicNumber(REQUESTS_NUMBER, 2));
}


int main(int argc, char* argv[]) {
    if(argc != 7) {
        std::cerr << "Usage: " << argv[0] << " <graph_type> <strategy> <distribution> <d_value> <requests_number> <repetitions>" << std::endl;
        return -1;
    }

    std::string graphType = argv[1];
    std::string strategy = argv[2];
    std::string dist = argv[3];
    size_t dValue = std::stoul(argv[4]);
    size_t totalRequestsNumber = std::stoul(argv[5]);
    size_t repetitions = std::stoul(argv[6]);

    std::unique_ptr<Graph> graph;
    if(graphType == "torus") {
        graph = std::make_unique<Torus>(TORUS_DIMENSION);
    } else if(graphType == "hypercube") {
        graph = std::make_unique<Hypercube>(HYPERCUBE_DIMENSION);
    } else {
        std::cerr << "Invalid graph type: " << graphType << std::endl;
        return -1;
    }

    std::unique_ptr<PageMigration> pageMigration;
    if(strategy == "move-to-min") {
        pageMigration = std::make_unique<PageMigrationMoveToMin>(std::move(graph), dValue);
    } else if(strategy == "coin-flip") {
        pageMigration = std::make_unique<PageMigrationCoinFlip>(std::move(graph), dValue);
    } else {
        std::cerr << "Invalid strategy: " << strategy << std::endl;
        return -1;
    }

    std::unique_ptr<DistributionI> distribution;
    if(dist == "uniform") {
        distribution = std::make_unique<Distribution<REQUESTS_NUMBER, uniformDistributionProbability>>();
    } else if(dist == "geometric") {
        distribution = std::make_unique<Distribution<REQUESTS_NUMBER, geometricDistributionProbability>>();
    } else if(dist == "harmonic") {
        distribution = std::make_unique<Distribution<REQUESTS_NUMBER, harmonicDistributionProbability>>();
    } else if(dist == "biharmonic") {
        distribution = std::make_unique<Distribution<REQUESTS_NUMBER, biharmonicDistributionProbability>>();
    } else {
        std::cerr << "Invalid distribution: " << dist << std::endl;
        return -1;
    }

    size_t cost = 0;
    for(size_t rep = 0; rep < repetitions; rep++) {
        pageMigration->reset();
        for(size_t reqNum = 0; reqNum < totalRequestsNumber; reqNum++) {
            cost += pageMigration->access((*distribution)());
        }
    }
    
    if(repetitions * totalRequestsNumber == 0) {
        std::cout << 0 << std::endl;
    }
    else {
        std::cout << static_cast<double>(cost) / static_cast<double>(repetitions * totalRequestsNumber) << std::endl;
    }

    return 0;
}