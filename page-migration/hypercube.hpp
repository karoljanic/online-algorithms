#ifndef HYPERCUBE_HPP
#define HYPERCUBE_HPP

#include "graph.hpp"

class Hypercube : public Graph {
public:
    Hypercube(uint16_t dimension) : dimension_{dimension} { }

    Hypercube(const Hypercube&) = default;
    Hypercube(Hypercube&&) = default;

    Hypercube& operator=(const Hypercube&) = default;
    Hypercube& operator=(Hypercube&&) = default;

    virtual size_t distance(uint16_t u, uint16_t v) override {
        return __builtin_popcount(u ^ v);
    }

private:
    uint16_t dimension_;
};

#endif // HYPERCUBE_HPP