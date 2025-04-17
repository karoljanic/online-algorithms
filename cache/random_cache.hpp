#ifndef RANDOM_CACHE_HPP
#define RANDOM_CACHE_HPP

#include "cache.hpp"

#include <random>

class RandomCache : public Cache {
public:
    RandomCache() = default;
    RandomCache(uint16_t size) : Cache{size}, generator{std::random_device{}()} {}

    RandomCache(const RandomCache&) = default;
    RandomCache(RandomCache&&) = default;

    RandomCache& operator=(const RandomCache&) = default;
    RandomCache& operator=(RandomCache&&) = default;

    ~RandomCache() override = default;

    size_t load(uint16_t index) override {
        auto it = std::find(cache.begin(), cache.end(), index);
        if (it != cache.end()) {        // already in cache
            return 0;
        }
        
        if (cache.size() < capacity) {  // cache not full
            cache.push_back(index);
            return 1;
        } 

        // cache full, replace a random page
        cache.erase(cache.begin() + std::uniform_int_distribution<uint16_t>(0, cache.size() - 1)(generator));
        cache.push_back(index);

        return 1;
    }

private:
    std::mt19937 generator;
};

#endif // RANDOM_CACHE_HPP