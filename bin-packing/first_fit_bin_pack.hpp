#ifndef FIRST_FIT_BIN_PACK_HPP
#define FIRST_FIT_BIN_PACK_HPP

#include "bin_pack.hpp"

class FirstFitBinPack : public BinPack {
public:
    FirstFitBinPack() : BinPack() {}
    FirstFitBinPack(double capacity) : BinPack(capacity) {}

    FirstFitBinPack(const FirstFitBinPack&) = default;
    FirstFitBinPack(FirstFitBinPack&&) = default;

    FirstFitBinPack& operator=(const FirstFitBinPack&) = default;
    FirstFitBinPack& operator=(FirstFitBinPack&&) = default;

    ~FirstFitBinPack() override = default;

    size_t pack(double itemSize) override {
        for (size_t i = 0; i < bins.size(); i++) {
            if (bins[i] >= itemSize) {
                bins[i] -= itemSize;
                return 0;
            }
        }
        bins.push_back(binCapacity - itemSize);
        return 1;
    }
};

#endif // FIRST_FIT_BIN_PACK_HPP