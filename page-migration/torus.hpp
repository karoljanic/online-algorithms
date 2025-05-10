#ifndef TORUS_HPP
#define TORUS_HPP

#include <algorithm>

#include "graph.hpp"

class Torus : public Graph {
public:
    Torus(uint16_t dimension) : dimension_{dimension} { }

    Torus(const Torus&) = default;
    Torus(Torus&&) = default;

    Torus& operator=(const Torus&) = default;
    Torus& operator=(Torus&&) = default;

    size_t distance(uint16_t u, uint16_t v) override {
        int32_t x1 = u % dimension_;
        int32_t y1 = u / dimension_;
        int32_t x2 = v % dimension_;
        int32_t y2 = v / dimension_;

        int32_t dx = std::abs(x1 - x2);
        int32_t dy = std::abs(y1 - y2);

        return static_cast<size_t>(std::min(dx, dimension_ - dx) + std::min(dy, dimension_ - dy));
    }

private:
    uint16_t dimension_;
};

#endif // TORUS_HPP