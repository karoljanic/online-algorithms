#ifndef RANDOM_MARKUP_CACHE_HPP
#define RANDOM_MARKUP_CACHE_HPP

#include "cache.hpp"

#include <set>

class RandomMarkupCache : public Cache {
public:
    RandomMarkupCache() = default;
    RandomMarkupCache(uint16_t size) : Cache{size}, generator{std::random_device{}()} {}

    RandomMarkupCache(const RandomMarkupCache&) = default;
    RandomMarkupCache(RandomMarkupCache&&) = default;

    RandomMarkupCache& operator=(const RandomMarkupCache&) = default;
    RandomMarkupCache& operator=(RandomMarkupCache&&) = default;

    ~RandomMarkupCache() override = default;

    size_t load(uint16_t index) override {
        auto it = std::find(cache.begin(), cache.end(), index);
        if (it != cache.end()) {        // already in cache
            marked.insert(index);
            return 0;
        }
        
        if (cache.size() < capacity) {  // cache not full
            cache.push_back(index);
            marked.insert(index);
            return 1;
        } 

        // cache is full - remove random unmarked page
        // if all pages are marked, clear the cache
        uint16_t unmarkedPages = 0;
        for (const auto& page : cache) {
            if (marked.find(page) == marked.end()) {
                unmarkedPages++;
            }
        }

        if(unmarkedPages == 0) {
            marked.clear();
            unmarkedPages = cache.size();
        }
        
        uint16_t randomIndex = std::uniform_int_distribution<uint16_t>(0, unmarkedPages - 1)(generator);
        uint16_t selectedPageIndex = 0;
        uint16_t pageIndex = 0;
        while(pageIndex < cache.size()) {
            if (marked.find(cache[pageIndex]) == marked.end()) {
                if (selectedPageIndex == randomIndex) {
                    break;
                }
                else {
                    selectedPageIndex++;
                }
            }

            pageIndex++;
        }
        
        cache[pageIndex] = index;
        marked.insert(index);

        return 1;
    }

    void reset() {
        Cache::reset();
        marked.clear();
    }

private:
    std::mt19937 generator;
    std::set<uint16_t> marked;
};

#endif // RANDOM_MARKUP_CACHE_HPP