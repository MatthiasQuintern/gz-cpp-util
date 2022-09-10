#pragma once

namespace gz {

/**
 * @brief A generic iterator that satisfies std::forward_iterator
 */
template<typename T>
struct Iterator {
    public:
        using value_type = T;
        Iterator() : ptr(nullptr) {};
        Iterator(T* ptr) : ptr(ptr) {};
        T& operator*() const { return *ptr; };
        Iterator& operator=(const Iterator& other) {
            ptr = other.ptr;
            return *this;
        };
        Iterator& operator++() { ptr += sizeof(T); return *this; };
        Iterator operator++(int) { auto copy = *this; ptr += sizeof(T); return copy; };
        friend int operator-(Iterator lhs, Iterator rhs) {
            return lhs.ptr - rhs.ptr;
        };
        bool operator==(const Iterator& other) const { return ptr == other.ptr; };
        // bool operator!=(const Iterator& other) const { return ptr != other.ptr; };
    private:
        T* ptr;
}; // Iterator

/* static_assert(std::forward_iterator<Iterator<int>>, "Iterator not a forward range."); */
} // namespace gz
