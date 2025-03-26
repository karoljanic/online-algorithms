#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include <array>
#include <random>

#include "distribution_i.hpp"

template<uint16_t N, double(*Probability)(uint16_t)>
class Distribution : public DistributionI {
public:
    Distribution() : generator{std::random_device{}()}, probabilities{computeProbabilities()} {}

    Distribution(const Distribution&) = default;
    Distribution(Distribution&&) = default;

    Distribution& operator=(const Distribution&) = default;
    Distribution& operator=(Distribution&&) = default;

    ~Distribution() = default;

    virtual uint16_t operator()() override{
        const double random = std::uniform_real_distribution<double>(0.0, 1.0)(generator);
        for (uint16_t i = 0; i < N; ++i) {
            if (random < probabilities[i]) {
                return i;
            }
        }

        return N - 1;
    }

private:
    std::mt19937 generator;
    std::array<double, N> probabilities;

    constexpr std::array<double, N> computeProbabilities() {
        std::array<double, N> probs = {};
        double sum = 0.0;
        for (uint16_t i = 0; i < N; ++i) {
            sum += Probability(i);
            probabilities[i] = sum;
        }

        return probs;
    }
};

#endif // DISTRIBUTION_HPP
