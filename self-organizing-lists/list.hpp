#ifndef LIST_HPP
#define LIST_HPP

#include <cstdint>
#include <forward_list>

class List {
public:
    List() = default;
    List(uint16_t size) : length{size}, list(size) {}

    List(const List&) = default;
    List(List&&) = default;

    List& operator=(const List&) = default;
    List& operator=(List&&) = default;

    virtual ~List() = default;

    virtual size_t access(uint16_t index) = 0;

    void reset() {
        list.clear();
    }

protected:
    uint16_t length;
    std::forward_list<uint16_t> list;
};

#endif // LIST_HPP