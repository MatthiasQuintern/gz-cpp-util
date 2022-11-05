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

    /// Forward range holding ValueType
	template<typename T, typename ValueType>
	concept ForwardRange = std::ranges::forward_range<T> and std::same_as<std::ranges::range_value_t<T>, ValueType>;

    /// Contiguous range holding ValueType
	template<typename T, typename ValueType>
	concept ContiguousRange = std::ranges::contiguous_range<T> and std::same_as<std::ranges::range_value_t<T>, ValueType>;

 
}

/**
 * @file
 * @brief Concepts that might be useful elsewhere
 */
