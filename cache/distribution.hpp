#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include <array>
#include <random>

#include "distribution_i.hpp"

template<double(*Probability)(uint16_t, uint16_t)>
class Distribution : public DistributionI {
public:
    Distribution() : generator{std::random_device{}()}, probabilities{computeProbabilities()} {}
    Distribution(uint16_t param_n) : DistributionI{param_n}, generator{std::random_device{}()}, probabilities{computeProbabilities(param_n)} {}

    Distribution(const Distribution&) = default;
    Distribution(Distribution&&) = default;

    Distribution& operator=(const Distribution&) = default;
    Distribution& operator=(Distribution&&) = default;

    ~Distribution() = default;

    virtual uint16_t operator()() override{
        const double random = std::uniform_real_distribution<double>(0.0, 1.0)(generator);
        for (uint16_t i = 0; i < n; i++) {
            if (random < probabilities[i]) {
                return i;
            }
        }

        return n - 1;
    }

private:
    std::mt19937 generator;
    std::vector<double> probabilities;

    std::vector<double> computeProbabilities(uint16_t n) {
        std::vector<double> probs(n);
        double sum = 0.0;
        for (uint16_t i = 0; i < n; i++) {
            sum += Probability(n, i);
            probabilities[i] = sum;
        }

        return probs;
    }
};

#endif // DISTRIBUTION_HPP
