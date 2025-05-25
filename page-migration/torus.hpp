#ifndef TORUS_HPP
#define TORUS_HPP

#include <algorithm>

#include "graph.hpp"

class Torus : public Graph {
public:
    Torus(uint16_t dimension, uint16_t size) : dimension_{dimension}, size_{size} {}

    Torus(const Torus&) = default;
    Torus(Torus&&) = default;

    Torus& operator=(const Torus&) = default;
    Torus& operator=(Torus&&) = default;

    size_t distance(uint16_t u, uint16_t v) override {
        size_t totalDistance = 0;
        for(uint16_t d = 0; d < dimension_; d++) {
            uint16_t uCoord = u % size_;
            uint16_t vCoord = v % size_;
            u /= size_;
            v /= size_;

            int32_t dist = std::abs(uCoord - vCoord);
            totalDistance += static_cast<size_t>(std::min(dist, size_ - dist));
        }

        return totalDistance;
    }

private:
    uint16_t dimension_;
    uint16_t size_;
};

#endif // TORUS_HPP