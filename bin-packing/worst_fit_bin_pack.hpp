#ifndef WORST_FIT_BIN_PACK_HPP
#define WORST_FIT_BIN_PACK_HPP

class WorstFitBinPack : public BinPack {
public:
    WorstFitBinPack() : BinPack() {}
    WorstFitBinPack(double capacity) : BinPack(capacity) {}

    WorstFitBinPack(const WorstFitBinPack&) = default;
    WorstFitBinPack(WorstFitBinPack&&) = default;

    WorstFitBinPack& operator=(const WorstFitBinPack&) = default;
    WorstFitBinPack& operator=(WorstFitBinPack&&) = default;

    ~WorstFitBinPack() override = default;

    size_t pack(double itemSize) override {
        double maxSpaceLeft = -binCapacity;
        size_t worstBinIndex = 0;

        for (size_t i = 0; i < bins.size(); i++) {
            double spaceLeft = bins[i] - itemSize;
            if (spaceLeft >= 0 && spaceLeft > maxSpaceLeft) {
                maxSpaceLeft = spaceLeft;
                worstBinIndex = i;
            }
        }

        if (maxSpaceLeft >= 0) {
            bins[worstBinIndex] -= itemSize;
        } else {
            bins.push_back(binCapacity - itemSize);
            return 1;
        }

        return 0;
    }
};

#endif // WORST_FIT_BIN_PACK_HPP