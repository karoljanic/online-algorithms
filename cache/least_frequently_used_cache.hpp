#ifndef LEAST_FREQUENTLY_USED_CACHE_HPP
#define LEAST_FREQUENTLY_USED_CACHE_HPP

#include "cache.hpp"

#include <map>

class LeastFrequentlyUsedCache : public Cache {
public:
    LeastFrequentlyUsedCache() = default;
    LeastFrequentlyUsedCache(uint16_t size) : Cache{size} {}

    LeastFrequentlyUsedCache(const LeastFrequentlyUsedCache&) = default;
    LeastFrequentlyUsedCache(LeastFrequentlyUsedCache&&) = default;

    LeastFrequentlyUsedCache& operator=(const LeastFrequentlyUsedCache&) = default;
    LeastFrequentlyUsedCache& operator=(LeastFrequentlyUsedCache&&) = default;

    ~LeastFrequentlyUsedCache() override = default;

    size_t load(uint16_t index) override {
        auto it = std::find(cache.begin(), cache.end(), index);
        if (it != cache.end()) {        // already in cache
            incFrequency(index);
            return 0;
        }
        
        if (cache.size() < capacity) {  // cache not full
            cache.push_back(index);
            incFrequency(index);
            return 1;
        } 

        // cache is full, remove the least frequently used page
        size_t minIndex = 0;
        uint16_t minFrequency = frequencyMap[cache[minIndex]];
        for(size_t i = 0; i < cache.size(); i++) {
            if(frequencyMap[cache[i]] < minFrequency) {
                minIndex = i;
                minFrequency = frequencyMap[cache[i]];
            }
        }

        cache.erase(cache.begin() + minIndex);
        cache.push_back(index);
        incFrequency(index);

        return 1;
    }

    void reset() {
        Cache::reset();
        frequencyMap.clear();
    }

private:
    void incFrequency(uint16_t index) {
        auto it = frequencyMap.find(index);
        if (it != frequencyMap.end()) {
            it->second++;
        }
        else {
            frequencyMap[index] = 1;
        }
    }

    std::map<uint16_t, uint16_t> frequencyMap;
};

#endif // LEAST_FREQUENTLY_USED_CACHE_HPP