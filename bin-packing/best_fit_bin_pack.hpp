#ifndef BEST_FIT_BIN_PACK_HPP
#define BEST_FIT_BIN_PACK_HPP

#include "bin_pack.hpp"

class BestFitBinPack : public BinPack {
public:
    BestFitBinPack() : BinPack() {}
    BestFitBinPack(double capacity) : BinPack(capacity) {}

    BestFitBinPack(const BestFitBinPack&) = default;
    BestFitBinPack(BestFitBinPack&&) = default;

    BestFitBinPack& operator=(const BestFitBinPack&) = default;
    BestFitBinPack& operator=(BestFitBinPack&&) = default;

    ~BestFitBinPack() override = default;

    size_t pack(double itemSize) override {
        double minSpaceLeft = 2 * binCapacity;
        size_t bestBinIndex = 0;

        for (size_t i = 0; i < bins.size(); i++) {
            double spaceLeft = bins[i] - itemSize;
            if (spaceLeft >= 0 && spaceLeft < minSpaceLeft) {
                minSpaceLeft = spaceLeft;
                bestBinIndex = i;
            }
        }

        if (minSpaceLeft <= binCapacity) {
            bins[bestBinIndex] -= itemSize;
        } else {
            bins.push_back(binCapacity - itemSize);
            return 1;
        }

        return 0;
    }
};

#endif // BEST_FIT_BIN_PACK_HPP