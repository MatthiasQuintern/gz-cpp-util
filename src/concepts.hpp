#pragma once

#include <concepts>
#include <ranges>

namespace gz::util {
    /// Satisfied when T is in PackTypes
    template<typename T, typename... PackTypes>
    concept IsInPack = (std::same_as<T, PackTypes> || ...); 

    template<typename T>
    concept False = false;

    /// Forward range holding integers
    template<typename T>
    concept IntegralForwardRange = std::ranges::forward_range<T> and std::integral<std::ranges::range_value_t<T>>;
}

/**
 * @file
 * @brief Concepts that might be useful elsewhere
 */
