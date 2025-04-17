#ifndef LEAST_RECENTLY_USED_CACHE_HPP
#define LEAST_RECENTLY_USED_CACHE_HPP

#include "cache.hpp"

#include <map>

class LeastRecentlyUsedCache : public Cache {
public:
    LeastRecentlyUsedCache() = default;
    LeastRecentlyUsedCache(uint16_t size) : Cache{size}, timeStamp{0} {}

    LeastRecentlyUsedCache(const LeastRecentlyUsedCache&) = default;
    LeastRecentlyUsedCache(LeastRecentlyUsedCache&&) = default;

    LeastRecentlyUsedCache& operator=(const LeastRecentlyUsedCache&) = default;
    LeastRecentlyUsedCache& operator=(LeastRecentlyUsedCache&&) = default;

    ~LeastRecentlyUsedCache() override = default;

    size_t load(uint16_t index) override {
        auto it = std::find(cache.begin(), cache.end(), index);
        if (it != cache.end()) {        // already in cache
            setTimeStamp(index);
            return 0;
        }
        
        if (cache.size() < capacity) {  // cache not full
            cache.push_back(index);
            setTimeStamp(index);
            return 1;
        }

        // cache is full, remove the least recently used page
        size_t minIndex = 0;
        uint16_t minTimeStamp = timeStamps[cache[minIndex]];
        for(size_t i = 0; i < cache.size(); ++i) {
            if(timeStamps[cache[i]] < minTimeStamp) {
                minIndex = i;
                minTimeStamp = timeStamps[cache[i]];
            }
        }
        
        cache.erase(cache.begin() + minIndex);
        cache.push_back(index);
        setTimeStamp(index);
        
        // update the timestamp
        timeStamp++;

        return 1;
    }

    void reset() {
        Cache::reset();
        timeStamp = 0;
        timeStamps.clear();
    }

private:
    void setTimeStamp(uint16_t index) {
        auto it = timeStamps.find(index);
        if (it != timeStamps.end()) {
            it->second = timeStamp;
        }
        else {
            timeStamps[index] = timeStamp;
        }
    }

    uint16_t timeStamp;
    std::map<uint16_t, uint16_t> timeStamps;
};

#endif // LEAST_RECENTLY_USED_CACHE_HPP