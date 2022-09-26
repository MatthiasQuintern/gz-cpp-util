#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace gz::util {

    /**
     * @todo document
     */
    std::vector<std::string> splitStringInVector(std::string& s, char separator = ',');

    /**
     * @name Map with string type as key, works with strings, string_view and char*
     * @{
     */
    struct string_hash
    {
        using hash_type = std::hash<std::string_view>;
        using is_transparent = void;

        size_t operator()(const char* str) const        { return hash_type{}(str); }
        size_t operator()(std::string_view str) const   { return hash_type{}(str); }
        size_t operator()(std::string const& str) const { return hash_type{}(str); }
    };
    template<typename T>
    using unordered_string_map = std::unordered_map<std::string, T, util::string_hash, std::equal_to<>>;
    /**
     * @}
     */

} // namespace gz::util

/**
 * @file
 * @brief Contains utility for strings
 */
