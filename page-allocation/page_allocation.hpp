#ifndef PAGE_ALLOCATION_HPP
#define PAGE_ALLOCATION_HPP

#include <algorithm>
#include <cstdint>
#include <vector>

class PageAllocation {
public:    
    PageAllocation() = default;
    PageAllocation(uint16_t nodesNumber, const std::vector<uint16_t>& nodesWithResource, size_t dValue) 
        : nodesNumber_{nodesNumber}, copiesNumber_{nodesWithResource.size()}, dValue_{dValue} {
        counters_.resize(nodesNumber, {State::INCREASE, 0, false});
        for(uint16_t node: nodesWithResource) {
            counters_[node].state = State::WAIT;
            counters_[node].value = 0;
            counters_[node].hasCopy = true;
        }
    }

    PageAllocation(const PageAllocation&) = default;
    PageAllocation(PageAllocation&&) = default;

    PageAllocation& operator=(const PageAllocation&) = default;
    PageAllocation& operator=(PageAllocation&&) = default;

    ~PageAllocation() = default;

    size_t write(uint16_t target) {
        const size_t writeCost = counters_[target].hasCopy ? copiesNumber_ - 1 : copiesNumber_;
        return writeCost + updateState(target, Request::WRITE);
    }

    size_t read(uint16_t target) {
        const size_t readCost = counters_[target].hasCopy ? 0 : 1;
        return readCost + updateState(target, Request::READ);
    }

    size_t getCopiesNumber() const { return copiesNumber_; }

private:
    enum class State {WAIT, INCREASE, DECREASE};
    enum class Request {WRITE, READ};

    struct Counter {State state; size_t value; bool hasCopy;};

    uint16_t nodesNumber_;
    std::vector<Counter> counters_;
    size_t copiesNumber_;
    size_t dValue_;

    size_t updateState(uint16_t target, Request request) {
        size_t updateCost = 0;

        for(uint16_t node = 0; node < nodesNumber_; node++) {
            Counter& counter = counters_[node];
            if(counter.state == State::INCREASE) {
                if (node == target && (request == Request::READ || (request == Request::WRITE && isWating()))) {
                    counter.value++;
                    if (counter.value == dValue_) {
                        counter.state = State::DECREASE;
                        counter.hasCopy = true;
                        copiesNumber_++;
                        updateCost += dValue_;
                    }
                }
            }
            else if(counter.state == State::DECREASE) {
                if (node != target && request == Request::WRITE && counter.value > 0) {
                    counter.value--;
                    if (counter.value == 0) {
                        counter.state = State::WAIT;
                    }
                }
            }
            else if(counter.state == State::WAIT) {
                if (copiesNumber_ > 1) {
                    copiesNumber_--;
                    counter.state = State::INCREASE;
                    counter.value = 0;
                    counter.hasCopy = false;
                }
            }
        }

        return updateCost;
    }

    bool isWating() {
        return (copiesNumber_ == 1) && std::any_of(counters_.begin(), counters_.end(), [](const Counter& c) {
            return c.hasCopy && c.state == State::WAIT;
        });
    }
};

#endif // PAGE_ALLOCATION