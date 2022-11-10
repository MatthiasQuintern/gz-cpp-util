#pragma once

/* #include "log.hpp" */
#include "../util.hpp"

#include <vector>
#include <iterator>
#include <algorithm>
#include <concepts>

namespace gz {
    /**
     * @brief A fixed size buffer that can store data continuously without needing to move data or reallocate memory
     * @details
     *  A buffer with size n will store the n newest elements that were inserted. If the number of inserted elements is < n, the buffers size will also be < n.
     *
     *  The buffer can be @ref RingBuffer::resize() "resized", which potentially leads to a reallocation of memory.
     *
     * @subsection ringbuffer_iteration Iteration
     *  The RingBuffer has its own bidirectional iterator. The normal direction is from newest to oldest element.
     *  @code
     *      RingBuffer<int> rb(4);
     *      for (int i = 0; i < 7; i++) { rb.push_back(i); }
     *      for (auto it = rb.begin(); it != rb.end(); it++) {
     *          std::cout << *it << " ";
     *      }
     *  @endcode
     *  will produce @code 6 5 4 3 @endcode
     *
     *  If the buffer is empty, all iterators point to the separator element (end() == rend() == begin() == rbegin()).
     *
     * @subsection ringbuffer_technical_details Technical Details
     *  A buffer with size n will store its objects in a std::vector with size n+1, where the additional element serves as a separator between the newest and the oldest element. 
     *  It is technically the real oldest element and could be accessed using end() or rend(), which will always point to this element (meaning end() == rend()), giving you a n+1 sized buffer.
     *  However, this element will be default initialized until n+1 elements have been inserted into the buffer, so it is not advisable to use this extra element.
     *
     *  The RingBuffer satisfies concept std::ranges::bidirectional_range and RingBuffer::Iterator satisfies std::bidirectional_iterator
     *
     *  The writeIndex will always point to the element that was last written.
     *
     */
    template<std::swappable T>
    class RingBuffer {
        public:
            RingBuffer(size_t size=10);

            /**
             * @brief Bidirectonal iterator for the RingBuffer
             * @todo make a const and non-const version, since const here is all over the place
             */
            struct Iterator {
                public:
                    Iterator(const RingBuffer<T>& b, size_t index) : b(b), ptr(const_cast<T*>(&b.buffer.at(index))) {}
                    Iterator(const Iterator& other) : b(other.b), ptr(other.ptr) {}
                // Needed for std::input_iterator
                    using value_type = T;
                    T& operator*() const { return *ptr; }
                    Iterator& operator=(const Iterator& other) {
                        b = other.b;
                        ptr = other.ptr;
                        return this;
                    }
                    Iterator& operator++() {
                        if (ptr == &*b.buffer.begin()) { ptr = const_cast<T*>(&*b.buffer.rbegin()); }
                        else { ptr--; }
                        return *this;
                    }
                    Iterator operator++(int) {
                        auto copy = *this;
                        if (ptr == &*b.buffer.begin()) { ptr = const_cast<T*>(&*b.buffer.rbegin()); }
                        else { ptr--; }
                        return copy;
                    }
                    friend int operator-(Iterator lhs, Iterator rhs) {
                        return lhs.getCurrentIndex() - rhs.getCurrentIndex();
                    }
                // Needed for std::forward_iterator
                    /// @warning Default constructor has to be defined for std::forward_iterator but can not be used, since reference to RingBuffer<T> can not be initialized! Your compiler should (hopefully) not allow it.
                    Iterator() : ptr(nullptr) {};
                    bool operator==(const Iterator& other) const {
                        return this->ptr == other.ptr;
                    }
                // Needed for std::bidirectional_iterator
                    Iterator& operator--() {
                        if (ptr == &*b.buffer.rbegin()) { ptr = const_cast<T*>(&*b.buffer.begin()); }
                        else { ptr++; }
                        return *this;
                    }
                    Iterator operator--(int) {
                        auto copy = *this;
                        if (ptr == &*b.buffer.rbegin()) { ptr = const_cast<T*>(&*b.buffer.begin()); }
                        else { ptr++; }
                        return copy;
                    }
                // Not needed )
                    /* friend Iterator operator+(Iterator lhs, int i) { */
                    /*     return Iterator(lhs.b, &lhs.b.buffer[lhs.getValidIndex(lhs.getCurrentIndex() + i)]); */
                    /* } */
                    /* friend Iterator operator-(Iterator lhs, int i) { */
                    /*     return Iterator(lhs.b, &lhs.b.buffer[lhs.getValidIndex(lhs.getCurrentIndex() - i)]); */
                    /* } */
                    /* friend Iterator operator+(int i, Iterator rhs) { */
                    /*     return Iterator(rhs.b, &rhs.b.buffer[rhs.getValidIndex(rhs.getCurrentIndex() + i)]); */
                    /* } */
                    /* Iterator& operator+=(int i) { */
                    /*     ptr = &b.buffer[getValidIndex(getCurrentIndex() + i)]; */
                    /*     return this; */
                    /* } */
                    /* Iterator& operator-=(int i) { */
                    /*     ptr = &b.buffer[getValidIndex(getCurrentIndex() - i)]; */
                    /*     return this; */

                    /* } */
                    /* bool operator!=(const Iterator& other) const { */
                    /*     return this->ptr != other.ptr; */
                    /* } */
                    /// Get the index of the vector that ptr points to
                    std::string to_string() const {
                        return "Element: " + std::to_string(*ptr) + ", Index: " + std::to_string(getCurrentIndex()) + ", Pointer: " + std::to_string(reinterpret_cast<long>(ptr));
                    }
                private:
                    size_t getCurrentIndex() const {
                        return reinterpret_cast<long>(ptr - &*b.buffer.begin());
                    }
                    T* ptr;
                    const RingBuffer<T>& b;
            };
            void push_back(T& t);
            void push_back(T&& t) { push_back(t); };
            void emplace_back(T&& t);

            /**
             * @brief Return an iterator pointing to the newest object
             */
            const Iterator cbegin() const { return Iterator(*this, writeIndex); }
            /**
             * @brief Return an iterator poiting to the element preceeding the oldest element
             */
            const Iterator cend() const { return Iterator(*this, util::getIncrementedIndex(writeIndex, buffer.size())); }
             /**
             * @brief Return an iterator pointing to the oldest object
             */
            const Iterator crbegin() const { return Iterator(*this, util::getIncrementedIndex(writeIndex + 1, buffer.size())); }
            /**
             * @brief Return an iterator pointing to the element following the newest element
             */
            const Iterator crend() const { return Iterator(*this, util::getIncrementedIndex(writeIndex, buffer.size())); }

            const Iterator begin() { return Iterator(*this, writeIndex); }
            const Iterator end() { return Iterator(*this, util::getIncrementedIndex(writeIndex, buffer.size())); }
            const Iterator rbegin() { return Iterator(*this, util::getIncrementedIndex(writeIndex + 1, buffer.size())); }
            const Iterator rend() { return Iterator(*this, util::getIncrementedIndex(writeIndex, buffer.size())); }

            /**
             * @brief Resize the buffer to contain max size elements
             * @details
             *  If the current size is greater than size, the buffer is reduced to the newest elements that fit size. \n
             *  If the current size is smaller than size, the buffer size remains but it will be able to grow during element insertion until size is reached.
             */
            void resize(const size_t size);

            size_t capacity() const { return vectorCapacity - 1; }
            size_t size() const { return buffer.size() - 1; }

        private:
            size_t writeIndex;  ///< Points to the element that was last written
            std::vector<T> buffer;
            size_t vectorCapacity;
    };

    template<std::swappable T>
    RingBuffer<T>::RingBuffer(size_t capacity) {
        buffer.reserve(capacity + 1);
        buffer.resize(1);
        vectorCapacity = capacity + 1;

        writeIndex = 0;
    }

    template<std::swappable T>
    void RingBuffer<T>::resize(size_t size) {
        if (size + 1 > buffer.capacity()) {  // when growing
            // point writeIndex to separator
            util::incrementIndex(writeIndex, buffer.size());
            // separator element becomes first element -> vector grows while inserting elements
            std::rotate(buffer.begin(), buffer.begin() + writeIndex, buffer.end());
            buffer.reserve(size + 1);
            writeIndex = buffer.size() - 1;
        } 
        else if (size + 1 < buffer.size()) {  // when shrinking
            // point writeIndex to separator
            util::incrementIndex(writeIndex, buffer.size());
            // separator becomes last element in smaller vector -> resize cuts oldest elements
            std::rotate(buffer.begin(), buffer.begin() + util::getValidIndex(static_cast<int>(writeIndex - size), buffer.size()), buffer.end());
            buffer.resize(size + 1);
            writeIndex = util::getValidIndex(static_cast<int>(buffer.size() - 2), buffer.size());
        }
        vectorCapacity = size + 1;

    }

    template<std::swappable T>
    void RingBuffer<T>::push_back(T& t) {
        util::incrementIndex(writeIndex, vectorCapacity);
        if (buffer.size() < vectorCapacity) {
            buffer.push_back(t); 
        }
        else {
            buffer[writeIndex] = t;
        }
    }
    template<std::swappable T>
    void RingBuffer<T>::emplace_back(T&& t) {
        util::incrementIndex(writeIndex, vectorCapacity);
        if (buffer.size() < vectorCapacity) {
            buffer.emplace_back(std::move(t)); 
        }
        else {
            buffer[writeIndex] = std::move(t);
        }
    }
}
