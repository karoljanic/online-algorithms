#ifndef OFFLINE_BIN_PACKING_HPP
#define OFFLINE_BIN_PACKING_HPP

#include <vector>
#include <algorithm>

class OfflineBinPacking {
public:
    OfflineBinPacking() : binCapacity{1.0} {}
    OfflineBinPacking(double capacity) : binCapacity{capacity} {}

    OfflineBinPacking(const OfflineBinPacking&) = default;
    OfflineBinPacking(OfflineBinPacking&&) = default;

    OfflineBinPacking& operator=(const OfflineBinPacking&) = default;
    OfflineBinPacking& operator=(OfflineBinPacking&&) = default;

    size_t pack(std::vector<double>& items) {
        std::vector<double> binCapacities;
        std::sort(items.begin(), items.end(), std::greater<double>());

        for (const auto& item : items) {
            bool placed = false;
            for (auto& bin : binCapacities) {
                if (bin >= item) {
                    bin -= item;
                    placed = true;
                    break;
                }
            }
            if (!placed) {
                binCapacities.push_back(binCapacity - item);
            }
        }

        return binCapacities.size();
    }

private:
    double binCapacity;
};

#endif // OFFLINE_BIN_PACKING_HPP