#ifndef NEXT_FIT_BIN_PACK_HPP
#define NEXT_FIT_BIN_PACK_HPP

#include "bin_pack.hpp"

class NextFitBinPack : public BinPack {
public:
    NextFitBinPack() : BinPack() {}
    NextFitBinPack(double capacity) : BinPack(capacity) {}

    NextFitBinPack(const NextFitBinPack&) = default;
    NextFitBinPack(NextFitBinPack&&) = default;

    NextFitBinPack& operator=(const NextFitBinPack&) = default;
    NextFitBinPack& operator=(NextFitBinPack&&) = default;

    ~NextFitBinPack() override = default;

    size_t pack(double itemSize) override {
        if (bins.empty() || bins.back() < itemSize) {
            bins.push_back(binCapacity - itemSize);
            return 1;
        } else {
            bins.back() -= itemSize;
        }

        return 0;
    }
};

#endif // NEXT_FIT_BIN_PACK_HPP