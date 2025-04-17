#ifndef DISTRIBUTION_I_HPP
#define DISTRIBUTION_I_HPP

#include <cstdint>

class DistributionI {
public:
    DistributionI() = default;
    DistributionI(uint16_t param_n) : n{param_n} {}

    DistributionI(const DistributionI&) = default;
    DistributionI(DistributionI&&) = default;

    DistributionI& operator=(const DistributionI&) = default;
    DistributionI& operator=(DistributionI&&) = default;

    virtual ~DistributionI() = default;

    virtual uint16_t operator()() = 0;

protected:
    uint16_t n;
};

#endif // DISTRIBUTION_I_HPP