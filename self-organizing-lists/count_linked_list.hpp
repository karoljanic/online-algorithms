#ifndef COUNT_LINKED_LIST_HPP
#define COUNT_LINKED_LIST_HPP

#include <vector>
#include "list.hpp"

class CountLinkedList : public List {
public:
    CountLinkedList() = default;
    CountLinkedList(uint16_t size) : List{size} {
        count.resize(size, 0);
    }

    CountLinkedList(const CountLinkedList&) = default;
    CountLinkedList(CountLinkedList&&) = default;

    CountLinkedList& operator=(const CountLinkedList&) = default;
    CountLinkedList& operator=(CountLinkedList&&) = default;

    ~CountLinkedList() = default;

    size_t access(uint16_t index) {
        size_t cost = 1;

        auto prev = list.before_begin();
        auto curr = list.begin();
        while(curr != list.end()) {
            cost++;

            if(*curr == index) {
                count[index]++;          
                list.erase_after(prev);
                
                // Find the first element with a count less than the current element
                // and insert the current element before that element
                auto prev2 = list.before_begin();
                auto curr2 = list.begin();
                while(curr2 != list.end()) {
                    if(count[*curr2] < count[index]) {
                        break;
                    }
                    prev2++;
                    curr2++;
                }
                list.insert_after(prev2, index);

                return cost;
            }

            prev++;
            curr++;
        }

        count[index] = 1;
        list.insert_after(prev, index);

        return cost;
    }

    void reset() {
        List::reset();
        count.clear();
        count.assign(length, 0);
    }

private:
    std::vector<uint16_t> count;
};

#endif // COUNT_LINKED_LIST_HPP
