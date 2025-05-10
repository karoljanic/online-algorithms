#ifndef PAGE_MIGRATION_MOVE_TO_MIN_HPP
#define PAGE_MIGRATION_MOVE_TO_MIN_HPP

#include "page_migration.hpp"

class PageMigrationMoveToMin : public PageMigration {
public:
    PageMigrationMoveToMin() = default;
    PageMigrationMoveToMin(std::unique_ptr<Graph> graph, size_t dValue)
        : PageMigration{std::move(graph), dValue} { }

    PageMigrationMoveToMin(const PageMigrationMoveToMin&) = default;
    PageMigrationMoveToMin(PageMigrationMoveToMin&&) = default;

    PageMigrationMoveToMin& operator=(const PageMigrationMoveToMin&) = default;
    PageMigrationMoveToMin& operator=(PageMigrationMoveToMin&&) = default;

    ~PageMigrationMoveToMin() override = default;

    virtual size_t migrate(uint16_t target) {
        lastRequests_.push_back(target);
        if(lastRequests_.size() < dValue_) {
            return 0;
        }

        uint16_t minVertex = lastRequests_[0];
        uint16_t minDistance = distanceToAllLastRequests(minVertex);
        for(size_t i = 1; i < dValue_; ++i) {
            const uint16_t vertex = lastRequests_[i];
            const uint16_t distance = distanceToAllLastRequests(vertex);
            if(distance < minDistance) {
                minDistance = distance;
                minVertex = vertex;
            }
        }

        const size_t distance = graph_->distance(resourceVertex_, minVertex);

        resourceVertex_ = minVertex;
        lastRequests_.clear();

        return dValue_ * distance;
    }

    virtual void reset() {
        resourceVertex_ = 1;
        lastRequests_.clear();
    }

private:
    std::vector<uint16_t> lastRequests_;

    size_t distanceToAllLastRequests(uint16_t target) const {
        size_t distance = 0;
        for(const auto& vertex : lastRequests_) {
            distance += graph_->distance(target, vertex);
        }
        return distance;
    }
};

#endif // PAGE_MIGRATION_MOVE_TO_MIN_HPP