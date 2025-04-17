#ifndef FIFO_CACHE_HPP
#define FIFO_CACHE_HPP

#include "cache.hpp"

class FifoCache : public Cache {
public:
    FifoCache() = default;
    FifoCache(uint16_t size) : Cache{size} {}

    FifoCache(const FifoCache&) = default;
    FifoCache(FifoCache&&) = default;

    FifoCache& operator=(const FifoCache&) = default;
    FifoCache& operator=(FifoCache&&) = default;

    ~FifoCache() override = default;

    size_t load(uint16_t index) override {
        auto it = std::find(cache.begin(), cache.end(), index);
        if (it != cache.end()) {        // already in cache
            return 0;
        }
        
        if (cache.size() < capacity) {  // cache not full
            cache.push_back(index);
            return 1;
        } 

        // cache is full, remove the first element
        cache.erase(cache.begin());
        cache.push_back(index);

        return 1;
    }
};

#endif // FIFO_CACHE_HPP