#ifndef CACHE_HPP
#define CACHE_HPP

#include <algorithm>
#include <cstdint>
#include <vector>

class Cache {
public:
    Cache() = default;
    Cache(uint16_t capacity) : capacity{capacity}, cache{} {}

    Cache(const Cache&) = default;
    Cache(Cache&&) = default;

    Cache& operator=(const Cache&) = default;
    Cache& operator=(Cache&&) = default;

    virtual ~Cache() = default;

    virtual size_t load(uint16_t index) = 0;

    void reset() {
        cache.clear();
    }

protected:
    uint16_t capacity;
    std::vector<uint16_t> cache;
};

#endif // CACHE_HPP