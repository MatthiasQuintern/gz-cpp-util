#pragma once

#include <concepts>


namespace gz::util {
//
// INDEX UTILITY
//
    /**
     * @brief Increment an index. Up to containerSize, then restart at 0
     */
    template<std::unsigned_integral I, std::unsigned_integral S>
    inline void incrementIndex(I& i, const S containerSize) {
        if (i < containerSize - 1) { i++; }
        else { i = 0; }
    }
    /**
     * @brief Decrement an index. Down to 0, then restart at containerSize - 1
     */
    template<std::unsigned_integral I, std::unsigned_integral S>
    inline void decrementIndex(I& i, const S containerSize) {
        if (i > 0) { i--; }
        else { i = containerSize - 1; }
    }
    /**
     * @brief Like incrementIndex, but returns a new number
     */
    template<std::unsigned_integral I, std::unsigned_integral S>
    inline I getIncrementedIndex(const I i, const S containerSize) {
        if (i < containerSize - 1) { return i + 1; }
        else { return 0; }
    }
    /**
     * @brief Like decrementIndex, but returns a new number
     */
    template<std::unsigned_integral I, std::unsigned_integral S>
    inline I getDecrementedIndex(const I i, const S containerSize) {
        if (i > 0) { return i - 1; }
        else { return containerSize - 1; }
    }

    /**
     * @brief Wrap an index around, to make it valid
     * @details
     *  Example:
     *  - i = containerSize + 2 -> return 2
     *  - i = -2 -> return (containerSize - 1) - 2
     */
    template<std::integral I, std::unsigned_integral S>
    std::size_t getValidIndex(const I i, const S containerSize) {
        if (i < 0) { 
            return (containerSize - 1) - (-i) % containerSize;
        }
        else if (i >= static_cast<int>(containerSize)) {
            return i % containerSize;
        }
        return i;
    }


} // namespace gz::util

/**
 * @file 
 * @brief Various utilites
 */
