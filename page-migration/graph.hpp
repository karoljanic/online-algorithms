#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>
#include <cstdint>

class Graph {
public:
    Graph() = default;

    Graph(const Graph&) = default;
    Graph(Graph&&) = default;

    Graph& operator=(const Graph&) = default;
    Graph& operator=(Graph&&) = default;

    ~Graph() = default;

    virtual size_t distance(uint16_t u, uint16_t v) = 0;
};

#endif // GRAPH_HPP