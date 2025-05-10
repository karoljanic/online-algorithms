#ifndef PAGE_MIGRATION_COIN_FLIP_HPP
#define PAGE_MIGRATION_COIN_FLIP_HPP

#include <random>

#include "page_migration.hpp"

class PageMigrationCoinFlip : public PageMigration {
public:
    PageMigrationCoinFlip() = default;
    PageMigrationCoinFlip(std::unique_ptr<Graph> graph, size_t dValue)
        : PageMigration{std::move(graph), dValue}, gen(std::random_device{}()) { }

    PageMigrationCoinFlip(const PageMigrationCoinFlip&) = default;
    PageMigrationCoinFlip(PageMigrationCoinFlip&&) = default;

    PageMigrationCoinFlip& operator=(const PageMigrationCoinFlip&) = default;
    PageMigrationCoinFlip& operator=(PageMigrationCoinFlip&&) = default;

    ~PageMigrationCoinFlip() override = default;

    virtual size_t migrate(uint16_t target) {
        std::uniform_int_distribution<uint16_t> dist(0, 2 * dValue_ - 1);
        uint16_t coin = dist(gen);

        if(coin > 0) {
            return 0;
        }
        
        const size_t distance = graph_->distance(resourceVertex_, target);

        resourceVertex_ = target;

        return dValue_ * distance;
    }

    virtual void reset() {
        resourceVertex_ = 1;
    }

private:
    std::mt19937 gen;
};

#endif // PAGE_MIGRATION_COIN_FLIP_HPP