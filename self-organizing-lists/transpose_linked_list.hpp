#ifndef TRANSPOSE_LINKED_LIST_HPP
#define TRANSPOSE_LINKED_LIST_HPP

#include "list.hpp"

class TransposeLinkedList : public List {
public:
    TransposeLinkedList() = default;
    TransposeLinkedList(uint16_t size) : List{size} {}

    TransposeLinkedList(const TransposeLinkedList&) = default;
    TransposeLinkedList(TransposeLinkedList&&) = default;

    TransposeLinkedList& operator=(const TransposeLinkedList&) = default;
    TransposeLinkedList& operator=(TransposeLinkedList&&) = default;

    ~TransposeLinkedList() = default;

    size_t access(uint16_t index) {
        size_t cost = 1;

        auto prev = list.before_begin();
        auto curr = list.begin();
        auto prev_prev = list.before_begin();
        while(curr != list.end()) {
            cost++;
            
            if(*curr == index) {
                if(prev != list.before_begin()) {
                    list.splice_after(prev_prev, list, prev);
                }
                return cost;
            }

            prev_prev = prev;
            prev++;
            curr++;
        }

        list.insert_after(prev, index);
        
        return cost;
    }
};

#endif // TRANSPOSE_LINKED_LIST_HPP
