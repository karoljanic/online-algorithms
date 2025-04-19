#ifndef RANDOM_FIT_BIN_PACK_HPP
#define RANDOM_FIT_BIN_PACK_HPP

#include "bin_pack.hpp"

#include <random>

class RandomFitBinPack : public BinPack {
public:
    RandomFitBinPack() : BinPack() {}
    RandomFitBinPack(double capacity) : BinPack(capacity) {}

    RandomFitBinPack(const RandomFitBinPack&) = default;
    RandomFitBinPack(RandomFitBinPack&&) = default;

    RandomFitBinPack& operator=(const RandomFitBinPack&) = default;
    RandomFitBinPack& operator=(RandomFitBinPack&&) = default;

    ~RandomFitBinPack() override = default;

    size_t pack(double itemSize) override {
        std::vector<size_t> availableBins;
        for (size_t i = 0; i < bins.size(); i++) {
            if (bins[i] >= itemSize) {
                availableBins.push_back(i);
            }
        }

        if(availableBins.empty()) {
            bins.push_back(binCapacity - itemSize);
            return 1;
        }

        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<size_t> dis(0, availableBins.size() - 1);

        size_t randomIndex = dis(gen);
        bins[availableBins[randomIndex]] -= itemSize;

        return 0;
    }
};

#endif // RANDOM_FIT_BIN_PACK_HPP