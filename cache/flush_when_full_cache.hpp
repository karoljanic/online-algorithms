#ifndef FLUSH_WHEN_FULL_CACHE_HPP
#define FLUSH_WHEN_FULL_CACHE_HPP

#include "cache.hpp"

class FlushWhenFullCache : public Cache {
public:
    FlushWhenFullCache() = default;
    FlushWhenFullCache(uint16_t size) : Cache{size} {}

    FlushWhenFullCache(const FlushWhenFullCache&) = default;
    FlushWhenFullCache(FlushWhenFullCache&&) = default;

    FlushWhenFullCache& operator=(const FlushWhenFullCache&) = default;
    FlushWhenFullCache& operator=(FlushWhenFullCache&&) = default;

    ~FlushWhenFullCache() override = default;

    size_t load(uint16_t index) override {
        auto it = std::find(cache.begin(), cache.end(), index);
        if (it != cache.end()) {        // already in cache
            return 0;
        }
        
        if (cache.size() < capacity) {  // cache not full
            cache.push_back(index);
            return 1;
        } 

        // cache is full, remove all elements
        reset();
        cache.push_back(index);

        return 1;
    }
};

#endif // FLUSH_WHEN_FULL_CACHE_HPP