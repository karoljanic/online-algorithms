#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "list.hpp"

class LinkedList: public List {
public:
    LinkedList() = default;
    LinkedList(uint16_t size) : List{size} {}

    LinkedList(const LinkedList&) = default;
    LinkedList(LinkedList&&) = default;

    LinkedList& operator=(const LinkedList&) = default;
    LinkedList& operator=(LinkedList&&) = default;

    ~LinkedList() = default;

    size_t access(uint16_t index) {
        size_t cost = 1;

        auto prev = list.before_begin();
        auto curr = list.begin();
        while(curr != list.end()) {
            cost++;

            if(*curr == index) {
                return cost;
            }

            prev++;
            curr++;
        }

        list.insert_after(prev, index);
        
        return cost;
    }
};

#endif // LINKED_LIST_HPP
