#ifndef PAGE_MIGRATION_HPP
#define PAGE_MIGRATION_HPP

#include <cstdint>
#include <memory>

#include "graph.hpp"

class PageMigration {
public:
    PageMigration() = default;
    PageMigration(std::unique_ptr<Graph> graph, size_t dValue)
        : graph_{std::move(graph)}, resourceVertex_{1}, dValue_{dValue} { }

    PageMigration(const PageMigration&) = default;
    PageMigration(PageMigration&&) = default;

    PageMigration& operator=(const PageMigration&) = default;
    PageMigration& operator=(PageMigration&&) = default;

    virtual ~PageMigration() = default;

    size_t access(uint16_t target) {
        const size_t distanceCost = graph_->distance(resourceVertex_, target);
        const size_t migrateCost = migrate(target);

        return distanceCost + migrateCost;
    }

    virtual size_t migrate(uint16_t target) = 0;
    virtual void reset() = 0;

protected:
    std::unique_ptr<Graph> graph_;
    uint16_t resourceVertex_;
    size_t dValue_;
};

#endif // PAGE_MIGRATION_HPP
