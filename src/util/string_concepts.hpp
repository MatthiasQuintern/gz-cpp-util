#pragma once

#include <concepts>
#include <string>
#include <string_view>

namespace gz::util {

//
// CONVERT TO STRING CONCEPTS
//
    // ELEMENTARY TYPES
    /// same as std::string
    template<typename T> 
    concept Stringy = std::same_as<T, std::string> || std::convertible_to<T, std::string_view>;

    /// can construct std::string from T
    template<typename T> 
    concept CanConstructString = !Stringy<T> && requires(const T& t) {
        { std::string(t) } -> std::same_as<std::string>;
    };

    /// has .to_string() const member
    template<typename T>
    concept HasToStringMember = !Stringy<T> && requires(const T& t) { { t.toString() }-> Stringy; };

    /// works with std::to_string(), except bool
    template<typename T>
    concept WorksWithStdToString = !std::same_as<T, bool> && !Stringy<T> && !HasToStringMember<T> && requires(const T& t) { { std::to_string(t) } -> Stringy; };

    template<typename T>
    concept _ElementaryTypeConvertibleToString = Stringy<T> || HasToStringMember<T> || WorksWithStdToString<T>;
    

    // CONTAINER
    /// Forward range having string-convertible elements
    template<typename T>
    concept ContainerConvertibleToString = !_ElementaryTypeConvertibleToString<T> and std::ranges::forward_range<T> and _ElementaryTypeConvertibleToString<std::ranges::range_reference_t<T>>;

    template<typename T>
    concept _ElementaryTypeOrForwardRangeConvertibleToString = _ElementaryTypeConvertibleToString<T> || ContainerConvertibleToString<T>;

    /// Pair having string-convertible elements
    template<typename T>
    concept PairConvertibleToString = !ContainerConvertibleToString<T> and requires(const T& p) { 
        requires _ElementaryTypeOrForwardRangeConvertibleToString<decltype(p.first)>;
        requires _ElementaryTypeOrForwardRangeConvertibleToString<decltype(p.second)>;
    };

    /// Container having string-convertible pairs
    template<typename T>
    concept MapConvertibleToString = !PairConvertibleToString<T> and !_ElementaryTypeOrForwardRangeConvertibleToString<T> and
        std::ranges::forward_range<T> and PairConvertibleToString<std::ranges::range_reference_t<T>>;

    template<typename T>
    concept _ContainerTypeConvertibleToString = PairConvertibleToString<T> || ContainerConvertibleToString<T> || MapConvertibleToString<T>;

    template<typename T>
    concept _ElementaryTypeOrContainerConvertibleToString = _ElementaryTypeConvertibleToString<T> || _ContainerTypeConvertibleToString<T>;

    // VECTOR
    /// Type having string-convertible x, y members
    template<typename T>
    concept Vector2ConvertibleToString = !_ElementaryTypeOrContainerConvertibleToString<T> && 
        requires(T t) { 
            { t.x } -> _ElementaryTypeOrContainerConvertibleToString; 
            { t.y } -> _ElementaryTypeOrContainerConvertibleToString; 
            requires sizeof(t.x) * 2 == sizeof(T);
        };
    /// Type having string-convertible x, y, z members
    template<typename T>
    concept Vector3ConvertibleToString = !_ElementaryTypeOrContainerConvertibleToString<T> && 
        requires(T t) { 
            { t.x } -> _ElementaryTypeOrContainerConvertibleToString; 
            { t.y } -> _ElementaryTypeOrContainerConvertibleToString; 
            { t.z } -> _ElementaryTypeOrContainerConvertibleToString; 
            requires sizeof(t.x) * 3 == sizeof(T);
        };
    /// Type having string-convertible x, y, z, w members
    template<typename T>
    concept Vector4ConvertibleToString = !_ElementaryTypeOrContainerConvertibleToString<T> && 
        requires(T t) { 
            { t.x } -> _ElementaryTypeOrContainerConvertibleToString; 
            { t.y } -> _ElementaryTypeOrContainerConvertibleToString; 
            { t.z } -> _ElementaryTypeOrContainerConvertibleToString; 
            { t.w } -> _ElementaryTypeOrContainerConvertibleToString; 
            requires sizeof(t.x) * 4 == sizeof(T);
        };

    // POINTER
    /// Everything from string-convertibleNoPtr but "behind" a pointer
    template<typename T>
    concept PointerConvertibleToString = !_ElementaryTypeOrContainerConvertibleToString<T> and 
        requires(const T t) { { *t } -> _ElementaryTypeOrContainerConvertibleToString; };

} // namespace gz::util


//
// CONVERT TO STRING
//
template<typename T>
concept False = false;
/**
 * @brief Declaration of fromString in global namespace, so that concepts can use it
 * @details
 *  This declaration only exists so that ::fromString can be used in concepts.
 */
template<False T>
T fromString(const std::string& s);
/**
 * @brief Declaration of toString in global namespace, so that concepts can use it
 *  This declaration only exists so that ::toString can be used in concepts.
 */
template<False T>
std::string toString(const T& s);

namespace gz::util {
    template<typename T>
    concept ConstructibleFromStringGlobal = requires(const std::string& s) {
        { ::fromString<T>(s) } -> std::same_as<T>;
    };
    template<typename T>
    concept ConvertibleToStringGlobal = requires(const T& t) { 
        { ::toString(t) } -> Stringy; 
    };

    /**
     * @brief toString is implemented for these types
     */
    template<typename T>
    concept GetTypeFromStringImplemented = 
        std::same_as<T, int> or
        std::same_as<T, long> or
        std::same_as<T, long long> or
        std::same_as<T, unsigned int> or
        std::same_as<T, unsigned long> or
        std::same_as<T, unsigned long long> or
        std::same_as<T, float> or
        std::same_as<T, double> or
        std::same_as<T, long double> or
        std::same_as<T, bool>;
}

/**
 * @file
 * @brief Concepts used for the to_string() functions
 * @details
 *  These concepts are used 
 */
