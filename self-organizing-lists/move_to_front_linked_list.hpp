#ifndef MOVE_TO_FRONT_LINKED_LIST_HPP
#define MOVE_TO_FRONT_LINKED_LIST_HPP

#include "list.hpp"

class MoveToFrontLinkedList : public List {
public:
    MoveToFrontLinkedList() = default;
    MoveToFrontLinkedList(uint16_t size) : List{size} {}

    MoveToFrontLinkedList(const MoveToFrontLinkedList&) = default;
    MoveToFrontLinkedList(MoveToFrontLinkedList&&) = default;

    MoveToFrontLinkedList& operator=(const MoveToFrontLinkedList&) = default;
    MoveToFrontLinkedList& operator=(MoveToFrontLinkedList&&) = default;

    ~MoveToFrontLinkedList() = default;

    size_t access(uint16_t index) {
        size_t cost = 1;

        auto prev = list.before_begin();
        auto curr = list.begin();

        while(curr != list.end()) {
            cost++;

            if(*curr == index) {
                list.erase_after(prev);
                list.emplace_front(index);
                return cost;
            }

            prev++;
            curr++;
        }

        list.emplace_front(index);

        return cost;
    }
};

#endif // MOVE_TO_FRONT_LINKED_LIST_HPP
