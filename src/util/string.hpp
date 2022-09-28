#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

namespace gz::util {
    template<typename T>
    concept SplitStringInVectorImplemented = std::same_as<T, std::string_view> || std::same_as<T, std::string>;

    /**
     * @brief Split a string at a separator into a vector
     * @details
     *  Splits a string at a separator.\n
     *  Two templates exist, one where the vector will hold std::string_views into s 
     *  and one where it will hold std::strings. 
     *  Behavior:
     *  - the elements of the returned vector will not contain the separator.
     *  - if the separator is not in s, the vector will contain s as only element.
     *  - empty elements will occur if:
     *    - separator is the first char
     *    - separator is the last char
     *    - two or more separator appear after each other\n
     *    You can turn this behaviour off by setting skipEmptyStrings to true
     * @note 
     *  The string_view variant has the advantage of being faster, however:\n
     *  The string_views will reference the original string, so it must not be changed or destroyed
     *  as long as the string_views are used!
     */
    template<SplitStringInVectorImplemented T>
    std::vector<T> splitStringInVector(const std::string_view& s, const std::string& separator, bool skipEmptyStrings=false);

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
    /**
     * @brief A unordered_map where you can use string_views to access elements
     * @details
     *  To retrieve an element using a string view, you need to do this:
     *  @code
     *   std::string_view sv = ...;
     *   gz::util::unordered_string_map<T> smap = { ... };
     *   ...
     *   if (smap.contains(sv)) {
     *       return smap.find(sv)->second;
     *   }
     *  @endcode
     *  The at() member and [] operator do not work with the string_view.
     */
    template<typename T>
    using unordered_string_map = std::unordered_map<std::string, T, util::string_hash, std::equal_to<>>;
    /**
     * @brief same as unordered_string_map, but using std::map instead of std::unordered_map
     */
    template<typename T>
    using string_map = std::map<std::string, T, util::string_hash, std::equal_to<>>;
    /**
     * @}
     */

} // namespace gz::util

/**
 * @file
 * @brief Contains utility for strings
 */
