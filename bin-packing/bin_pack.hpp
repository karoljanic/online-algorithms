#ifndef BIN_PACK_HPP
#define BIN_PACK_HPP

#include <cstdint>
#include <vector>

class BinPack {
public:
    BinPack() : binCapacity{1.0} {}
    BinPack(double capacity) : binCapacity{capacity} {}

    BinPack(const BinPack&) = default;
    BinPack(BinPack&&) = default;

    BinPack& operator=(const BinPack&) = default;
    BinPack& operator=(BinPack&&) = default;

    virtual ~BinPack() = default;

    virtual size_t pack(double itemSize) = 0;
    
    void reset() {
        bins.clear();
    }

protected:
    double binCapacity;
    std::vector<double> bins;
};

#endif // BIN_PACK_HPP
