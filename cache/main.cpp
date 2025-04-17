#include <iostream>
#include <memory>

#include "fifo_cache.hpp"
#include "flush_when_full_cache.hpp"
#include "least_frequently_used_cache.hpp"
#include "least_recently_used_cache.hpp"
#include "random_cache.hpp"
#include "random_markup_cache.hpp"
#include "distribution.hpp"


constexpr double harmonicNumber(uint16_t index, uint16_t power) {
    double sum = 0.0;
    for(uint16_t i = 1; i <= index; i++) {
        sum += 1.0 / std::pow(i, power);
    }

    return sum;
}

constexpr double uniformDistributionProbability(uint16_t n, uint16_t /*index*/) {
    return 1.0 / n;
}

constexpr double geometricDistributionProbability(uint16_t n, uint16_t index) {
    if(index < (n - 1)) {
        return 1.0 / std::pow(2, index + 1);
    }
    else {
        return 1.0 / std::pow(2, n - 1);
    }
}

constexpr double harmonicDistributionProbability(uint16_t n, uint16_t index) {
    return 1.0 / ((index + 1) * harmonicNumber(n, 1));
}

constexpr double biharmonicDistributionProbability(uint16_t n, uint16_t index) {
    return 1.0 / (std::pow(index + 1, 2) * harmonicNumber(n, 2));
}


int main(int argc, char* argv[]) {
    if(argc != 7) {
        std::cerr << "Usage: " << argv[0] << " <strategy> <distribution> <capacity> <pages_number> <queries_number> <repetitions>" << std::endl;
        return -1;
    }

    std::string strategy = argv[1];
    std::string dist = argv[2];
    size_t capacity = std::stoul(argv[3]);
    size_t pages_number = std::stoul(argv[4]);
    size_t queries_number = std::stoul(argv[5]);
    size_t repetitions = std::stoul(argv[6]);

    std::unique_ptr<Cache> cache;
    if(strategy == "fifo") {
        cache = std::make_unique<FifoCache>(capacity);
    } else if(strategy == "flush-when-full") {
        cache = std::make_unique<FlushWhenFullCache>(capacity);
    } else if(strategy == "least-frequently-used") {
        cache = std::make_unique<LeastFrequentlyUsedCache>(capacity);
    } else if(strategy == "least-recently-used") {
        cache = std::make_unique<LeastRecentlyUsedCache>(capacity);
    } else if(strategy == "random") {
        cache = std::make_unique<RandomCache>(capacity);
    } else if(strategy == "random-markup") {
        cache = std::make_unique<RandomMarkupCache>(capacity);
    } else {
        std::cerr << "Invalid strategy: " << strategy << std::endl;
        return -1;
    }

    std::unique_ptr<DistributionI> distribution;
    if(dist == "uniform") {
        distribution = std::make_unique<Distribution<uniformDistributionProbability>>(pages_number);
    } else if(dist == "geometric") {
        distribution = std::make_unique<Distribution<geometricDistributionProbability>>(pages_number);
    } else if(dist == "harmonic") {
        distribution = std::make_unique<Distribution<harmonicDistributionProbability>>(pages_number);
    } else if(dist == "biharmonic") {
        distribution = std::make_unique<Distribution<biharmonicDistributionProbability>>(pages_number);
    } else {
        std::cerr << "Invalid distribution: " << dist << std::endl;
        return -1;
    }

    size_t cost = 0;
    for(size_t rep = 0; rep < repetitions; rep++) {
        cache->reset();
        for(size_t qNum = 0; qNum < queries_number; qNum++) {
            cost += cache->load((*distribution)());
        }
    }
    
    if(repetitions * pages_number == 0) {
        std::cout << 0 << std::endl;
    }
    else {
        std::cout << static_cast<double>(cost) / static_cast<double>(repetitions * queries_number) << std::endl;
    }

    return 0;
}